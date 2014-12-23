//===-- gala/backend_d3d9.c -------------------------------------*- C++ -*-===//
//
//  Gala
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//    * Michael Williams <mike@origamicomet.com>
//
//===----------------------------------------------------------------------===//

#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__

//============================================================================//

#include "gala/backend_d3d9.h"

//===----------------------------------------------------------------------===//

#include "gala/adapter_d3d9.h"
#include "gala/output_d3d9.h"

//===----------------------------------------------------------------------===//

#define _WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d9.h>

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

static BOOL gala_d3d9_initialized_ = FALSE;
static HMODULE gala_d3d9_dll_ = NULL;
static IDirect3D9 *gala_d3d9_ = NULL;

//===----------------------------------------------------------------------===//

static size_t gala_d3d9_num_adapters_ = 0;
static gala_adapter_d3d9_t **gala_d3d9_adapters_ = NULL;

//===----------------------------------------------------------------------===//

typedef IDirect3D9 * (WINAPI *Direct3DCreate9_fn)(
  /* _In_ */  UINT SDKVersion);
static Direct3DCreate9_fn Direct3DCreate9_ = NULL;

//===----------------------------------------------------------------------===//

bool gala_backend_init_d3d9(void)
{
  if (gala_d3d9_initialized_ != FALSE)
    // Already initialized.
    return false;

  gala_d3d9_dll_ = LoadLibraryA("d3d9.dll");
  if (gala_d3d9_dll_ == NULL)
    // Could not find or failed to load 'd3d9.dll'.
    return false;

  // TODO(mike): Try Direct3DCreate9Ex?
  Direct3DCreate9_ = (Direct3DCreate9_fn)GetProcAddress(gala_d3d9_dll_,
                                                        "Direct3DCreate9");
  if (Direct3DCreate9_ == NULL)
    return false;

  // TODO(mike): Use the C-style interface.
  gala_d3d9_ = Direct3DCreate9_(D3D_SDK_VERSION);

  gala_d3d9_num_adapters_ = gala_d3d9_->GetAdapterCount();
  gala_d3d9_adapters_ =
    (gala_adapter_d3d9_t **)foundation_heap()->alloc(
      foundation_heap(),
      gala_d3d9_num_adapters_ * sizeof(gala_adapter_d3d9_t *),
      alignof(gala_adapter_d3d9_t *));

  for (size_t adapter = 0; adapter < gala_d3d9_num_adapters_; ++adapter) {
    gala_d3d9_adapters_[adapter] =
      (gala_adapter_d3d9_t *)foundation_heap()->alloc(
        foundation_heap(),
        sizeof(gala_adapter_d3d9_t),
        alignof(gala_adapter_d3d9_t));

    // TODO(mike): Stop assuming the adapter is hardware accelerated.
    gala_d3d9_adapters_[adapter]->__adapter__.type = GALA_ADAPTER_HARDWARE;

    if (FAILED(gala_d3d9_->GetAdapterIdentifier(adapter, 0, &gala_d3d9_adapters_[adapter]->identifier)))
      // TODO(mike): Free memory.
      return false;
    if (strstr(gala_d3d9_adapters_[adapter]->identifier.Description, "PerfHUD") != 0)
      gala_d3d9_adapters_[adapter]->__adapter__.type = GALA_ADAPTER_PROXY;

    gala_output_d3d9_t **outputs =
      (gala_output_d3d9_t **)foundation_heap()->alloc(
        foundation_heap(),
        1 * sizeof(gala_output_d3d9_t *),
        alignof(gala_output_d3d9_t *));
    gala_d3d9_adapters_[adapter]->__adapter__.num_outputs = 1;
    gala_d3d9_adapters_[adapter]->__adapter__.outputs = (const gala_output_t **)outputs;

    outputs[0] =
      (gala_output_d3d9_t *)foundation_heap()->alloc(
        foundation_heap(),
        sizeof(gala_output_d3d9_t),
        alignof(gala_output_d3d9_t));

    outputs[0]->monitor = gala_d3d9_->GetAdapterMonitor(adapter);

    MONITORINFOEX MonitorInfo;
    ZeroMemory((void *)&MonitorInfo, sizeof(MONITORINFOEX));
    MonitorInfo.cbSize = sizeof(MONITORINFOEX);
    if (GetMonitorInfo(outputs[0]->monitor, &MonitorInfo) == 0)
      // TODO(mike): Free memory.
      return false;

    DEVMODE DevMode;
    if (EnumDisplaySettings(MonitorInfo.szDevice, ENUM_CURRENT_SETTINGS, &DevMode) == 0)
      // TODO(mike): Free memory.
      return false;

    outputs[0]->__output__.primary = (MonitorInfo.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY;
    outputs[0]->__output__.bounds.top = MonitorInfo.rcMonitor.top;
    outputs[0]->__output__.bounds.left = MonitorInfo.rcMonitor.left;
    outputs[0]->__output__.bounds.bottom = MonitorInfo.rcMonitor.bottom;
    outputs[0]->__output__.bounds.right = MonitorInfo.rcMonitor.right;

    const size_t num_output_modes[2] = {
      gala_d3d9_->GetAdapterModeCount(adapter, D3DFMT_X8R8G8B8),
      gala_d3d9_->GetAdapterModeCount(adapter, D3DFMT_A8R8G8B8)
    };

    gala_output_mode_d3d9_t **output_modes =
      (gala_output_mode_d3d9_t **)foundation_heap()->alloc(
        foundation_heap(),
        (num_output_modes[0] + num_output_modes[1]) * sizeof(gala_output_mode_d3d9_t *),
        alignof(gala_output_mode_d3d9_t *));

    outputs[0]->__output__.num_modes = num_output_modes[0] + num_output_modes[1];
    outputs[0]->__output__.modes = (const gala_output_mode_t **)output_modes;

    // TODO(mike): Determine which output mode is the current one.

    for (size_t i = 0; i < num_output_modes[0]; ++i) {
      D3DDISPLAYMODE DisplayMode;
      if (FAILED(gala_d3d9_->EnumAdapterModes(adapter, D3DFMT_X8R8G8B8, i, &DisplayMode)))
        // TODO(mike): Free memory.
        return false;
      gala_output_mode_d3d9_t *output_mode =
        (gala_output_mode_d3d9_t *)foundation_heap()->alloc(
          foundation_heap(),
          sizeof(gala_output_mode_d3d9_t),
          alignof(gala_output_mode_d3d9_t));
      output_modes[i] = output_mode;
      output_mode->mode = i;
      output_mode->__output_mode__.width = DisplayMode.Width;
      output_mode->__output_mode__.height = DisplayMode.Height;
      if (DisplayMode.RefreshRate == 0) {
        output_mode->__output_mode__.refresh_rate.numer = DevMode.dmDisplayFrequency;
        output_mode->__output_mode__.refresh_rate.denom = 1;
      } else {
        output_mode->__output_mode__.refresh_rate.numer = DisplayMode.RefreshRate;
        output_mode->__output_mode__.refresh_rate.denom = 1;
      }
      // output_mode->__output_mode__.format = GALA_PIXEL_FORMAT_X8R8G8B8;
    }

    for (size_t i = 0; i < num_output_modes[1]; ++i) {
      D3DDISPLAYMODE DisplayMode;
      if (FAILED(gala_d3d9_->EnumAdapterModes(adapter, D3DFMT_A8R8G8B8, i, &DisplayMode)))
        // TODO(mike): Free memory.
        return false;
      gala_output_mode_d3d9_t *output_mode =
        (gala_output_mode_d3d9_t *)foundation_heap()->alloc(
          foundation_heap(),
          sizeof(gala_output_mode_d3d9_t),
          alignof(gala_output_mode_d3d9_t));
      output_modes[i + num_output_modes[0]] = output_mode;
      output_mode->mode = i;
      output_mode->__output_mode__.width = DisplayMode.Width;
      output_mode->__output_mode__.height = DisplayMode.Height;
      if (DisplayMode.RefreshRate == 0) {
        output_mode->__output_mode__.refresh_rate.numer = DevMode.dmDisplayFrequency;
        output_mode->__output_mode__.refresh_rate.denom = 1;
      } else {
        output_mode->__output_mode__.refresh_rate.numer = DisplayMode.RefreshRate;
        output_mode->__output_mode__.refresh_rate.denom = 1;
      }
      // output_mode->__output_mode__.format = GALA_PIXEL_FORMAT_A8R8G8B8;
    }
  }

  // wcscmp(adapter->GetDesc(&...).Description, L"NVIDIA PerfHUD") != 0;
  // D3D10_DRIVER_TYPE_REFERENCE;

  gala_d3d9_initialized_ = true;
  return true;
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#else // BITBYTE_FOUNDATION_TIER0_SYSTEM != __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

bool gala_backend_init_d3d9(void)
{
  // TODO(mike): Provide details.
  return false;
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#endif

//===----------------------------------------------------------------------===//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace gala {

//===----------------------------------------------------------------------===//

namespace backend {

template <>
bool init<gala::backends::D3D9>(void) {
  return ::gala_backend_init_d3d9();
}

} // backend

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
