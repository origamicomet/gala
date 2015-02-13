#if 0

//===-- gala/backend_d3d9_win32.c -------------------------------*- C++ -*-===//
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

#include "gala/backend_d3d9_win32.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

gala_error_t gala_backend_initialize_d3d9(
  gala_backend_t **backend_,
  const gala_error_details_t **error_details)
{
  // BUG(mike): Memory leaks on failure...
  // TODO(mike): Use a user-specified allocator.
  gala_backend_d3d9_t *backend =
    (gala_backend_d3d9_t *)calloc(sizeof(gala_backend_d3d9_t), 1);

  backend->__backend__.type = GALA_BACKEND_D3D9;
  backend->__backend__.shutdown = &gala_backend_shutdown_d3d9;
  backend->__backend__.create_context = &gala_backend_create_context_d3d9;

  backend->hDll = LoadLibraryA("d3d9.dll");
#ifndef GALA_DISABLE_ERROR_CHECKS
  if (backend->hDll == NULL) {
    free((void *)backend);
    if (error_details) {
      *error_details = gala_error_details_create_unformatted(
        GALA_ERROR_UNKNOWN,
        "Unable to load the Direct3D9 runtime.");
    }
    return GALA_ERROR_UNKNOWN;
  }
#endif // !GALA_DISABLE_ERROR_CHECKS

  // TODO(mike): Try Direct3DCreate9Ex?
  typedef IDirect3D9 *(WINAPI *Direct3DCreate9_fn)(UINT);
  Direct3DCreate9_fn Direct3DCreate9_ = (Direct3DCreate9_fn)GetProcAddress(backend->hDll,
                                                                           "Direct3DCreate9");
#ifndef GALA_DISABLE_ERROR_CHECKS
  if (Direct3DCreate9_ == NULL) {
    FreeLibrary(backend->hDll);
    free((void *)backend);
    if (error_details) {
      *error_details = gala_error_details_create_unformatted(
        GALA_ERROR_UNKNOWN,
        "Unable to initialize the Direct3D9 runtime.");
    }
    return GALA_ERROR_UNKNOWN;
  }
#endif // !GALA_DISABLE_ERROR_CHECKS

  backend->D3D9 = Direct3DCreate9_(D3D_SDK_VERSION);
#ifndef GALA_DISABLE_ERROR_CHECKS
  if (backend->D3D9 == NULL) {
    FreeLibrary(backend->hDll);
    free((void *)backend);
    if (error_details) {
      *error_details = gala_error_details_create_unformatted(
        GALA_ERROR_UNKNOWN,
        "Unable to initialize the Direct3D9 runtime.");
    }
    return GALA_ERROR_UNKNOWN;
  }
#endif // !GALA_DISABLE_ERROR_CHECKS

  const UINT uiAdapterCount = backend->D3D9->GetAdapterCount();
  backend->__backend__.num_adapters = (size_t)uiAdapterCount;
  gala_adapter_d3d9_t *adapters = (gala_adapter_d3d9_t *)calloc((size_t)uiAdapterCount,
                                                                sizeof(gala_adapter_d3d9_t));
  const gala_adapter_t **adapters_ = (const gala_adapter_t **)calloc((size_t)uiAdapterCount,
                                                                     sizeof(gala_adapter_t *));
  backend->__backend__.adapters = adapters_;
#ifndef GALA_DISABLE_ERROR_CHECKS
  if ((adapters == NULL) || (adapters_ == NULL)) {
    if (adapters)
      free((void *)adapters);
    if (adapters_)
      free((void *)adapters_);
    FreeLibrary(backend->hDll);
    free((void *)backend);
    if (error_details) {
      *error_details = gala_error_details_create_unformatted(
        GALA_ERROR_OUT_OF_MEMORY,
        "Ran out of memory when querying adapters.");
    }
    return GALA_ERROR_OUT_OF_MEMORY;
  }
#endif // !GALA_DISABLE_ERROR_CHECKS

  for (UINT uiAdapter = 0; uiAdapter < uiAdapterCount; ++uiAdapter) {
    adapters_[uiAdapter] = (const gala_adapter_t *)&adapters[uiAdapter];
    // TODO(mike): Stop assuming the adapter is hardware accelerated.
    adapters[uiAdapter].__adapter__.type = GALA_ADAPTER_HARDWARE;
    adapters[uiAdapter].__adapter__._backend = (gala_backend_t *)backend;
    adapters[uiAdapter].uiAdapter = uiAdapter;

    /* adapters[uiAdapter].Identifier = */ {
      const HRESULT Result = backend->D3D9->GetAdapterIdentifier(uiAdapter, 0, &adapters[uiAdapter].Identifier);
    #ifndef GALA_DISABLE_ERROR_CHECKS
      if (FAILED(Result)) {
        free((void *)adapters);
        free((void *)adapters_);
        FreeLibrary(backend->hDll);
        free((void *)backend);
        if (error_details) {
          *error_details = gala_error_details_create_unformatted(
            GALA_ERROR_UNKNOWN,
            "Failed to query an adapter's identifier.");
        }
        return GALA_ERROR_UNKNOWN;
      }
    #endif // !GALA_DISABLE_ERROR_CHECKS
    }

    memcpy((void *)adapters[uiAdapter].__adapter__.desc,
           (const void *)adapters[uiAdapter].Identifier.Description,
           sizeof(adapters[uiAdapter].__adapter__.desc)-1);
    adapters[uiAdapter].__adapter__.desc[sizeof(adapters[uiAdapter].__adapter__.desc)-1] = '\0';

    if (strstr(adapters[uiAdapter].Identifier.Description, "PerfHUD") != NULL)
      adapters[uiAdapter].__adapter__.type = GALA_ADAPTER_PROXY;

    adapters[uiAdapter].__adapter__.num_outputs = 1;
    gala_output_d3d9_t *outputs = (gala_output_d3d9_t *)calloc(1, sizeof(gala_output_d3d9_t));
    gala_output_t **outputs_ = (gala_output_t **)calloc(1, sizeof(gala_output_t *));
    adapters[uiAdapter].__adapter__.outputs = (gala_output_t * const *)outputs_;

  #ifndef GALA_DISABLE_ERROR_CHECKS
    if ((outputs == NULL) || (outputs_ == NULL)) {
      if (outputs)
        free((void *)outputs);
      if (outputs_)
        free((void *)outputs_);
      free((void *)adapters);
      free((void *)adapters_);
      FreeLibrary(backend->hDll);
      free((void *)backend);
      if (error_details) {
        *error_details = gala_error_details_create_unformatted(
          GALA_ERROR_OUT_OF_MEMORY,
          "Ran out of memory when querying an adapter's outputs.");
      }
      return GALA_ERROR_OUT_OF_MEMORY;
    }
  #endif // !GALA_DISABLE_ERROR_CHECKS

    outputs_[0] = (gala_output_t *)&outputs[0];

    outputs[0].hMonitor = backend->D3D9->GetAdapterMonitor(uiAdapter);

    MONITORINFOEX MonitorInfo;
    ZeroMemory((void *)&MonitorInfo, sizeof(MONITORINFOEX));
    MonitorInfo.cbSize = sizeof(MONITORINFOEX);
    const BOOL bHaveMonitorInfo = GetMonitorInfo(outputs[0].hMonitor, &MonitorInfo);

    DEVMODE DevMode;
    const BOOL bHaveDisplaySettings = EnumDisplaySettings(MonitorInfo.szDevice, ENUM_CURRENT_SETTINGS, &DevMode);

  #ifndef GALA_DISABLE_ERROR_CHECKS
    if ((outputs[0].hMonitor == NULL) || !bHaveMonitorInfo || !bHaveDisplaySettings) {
      free((void *)adapters[uiAdapter].__adapter__.outputs[0]);
      free((void *)adapters[uiAdapter].__adapter__.outputs);
      free((void *)adapters);
      free((void *)adapters_);
      FreeLibrary(backend->hDll);
      free((void *)backend);
      if (error_details) {
        *error_details = gala_error_details_create_unformatted(
          GALA_ERROR_UNKNOWN,
          "Failed to query an adapter's output's monitor and/or display settings.");
      }
      return GALA_ERROR_UNKNOWN;
    }
  #endif // !GALA_DISABLE_ERROR_CHECKS

    outputs[0].__output__.primary = (uiAdapter == D3DADAPTER_DEFAULT);
    // NOTE: That uiAdapter == D3DADAPTER_DEFAULT should be true, if outputs[0].__output__.primary is.
    outputs[0].__output__.primary = (MonitorInfo.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY;
    outputs[0].__output__.bounds.top = MonitorInfo.rcMonitor.top;
    outputs[0].__output__.bounds.left = MonitorInfo.rcMonitor.left;
    outputs[0].__output__.bounds.bottom = MonitorInfo.rcMonitor.bottom;
    outputs[0].__output__.bounds.right = MonitorInfo.rcMonitor.right;
    outputs[0].ModeCount.uiA8R8G8B8 = backend->D3D9->GetAdapterModeCount(uiAdapter, D3DFMT_A8R8G8B8);
    outputs[0].ModeCount.uiX8R8G8B8 = backend->D3D9->GetAdapterModeCount(uiAdapter, D3DFMT_X8R8G8B8);

    outputs[0].__output__.num_modes = outputs[0].ModeCount.uiA8R8G8B8 + outputs[0].ModeCount.uiX8R8G8B8;
    gala_output_mode_d3d9_t *output_modes = (gala_output_mode_d3d9_t *)calloc((size_t)outputs[0].__output__.num_modes,
                                                                              sizeof(gala_output_mode_d3d9_t));
    gala_output_mode_t **output_modes_ = (gala_output_mode_t **)calloc((size_t)outputs[0].__output__.num_modes,
                                                                       sizeof(gala_output_mode_t *));
    outputs[0].__output__.modes = (const gala_output_mode_t * const *)output_modes_;

  #ifndef GALA_DISABLE_ERROR_CHECKS
    if ((output_modes == NULL) || (output_modes_ == NULL)) {
      free((void *)output_modes);
      free((void *)output_modes_);
      free((void *)adapters[uiAdapter].__adapter__.outputs[0]);
      free((void *)adapters[uiAdapter].__adapter__.outputs);
      free((void *)adapters);
      free((void *)adapters_);
      FreeLibrary(backend->hDll);
      free((void *)backend);
      if (error_details) {
        *error_details = gala_error_details_create_unformatted(
          GALA_ERROR_UNKNOWN,
          "Failed to query an adapter's output's display modes.");
      }
      return GALA_ERROR_UNKNOWN;
    }
  #endif // !GALA_DISABLE_ERROR_CHECKS

    for (UINT uiMode = 0; uiMode < outputs[0].ModeCount.uiA8R8G8B8; ++uiMode) {
      output_modes_[uiMode] = (gala_output_mode_t *)&output_modes[uiMode];
      D3DDISPLAYMODE DisplayMode;
      if (FAILED(backend->D3D9->EnumAdapterModes(uiAdapter, D3DFMT_A8R8G8B8, uiMode, &DisplayMode))) {
        // TODO(mike): Free memory.
        if (error_details)
          *error_details = NULL;
        return GALA_ERROR_UNKNOWN;
      }
      output_modes[uiMode].uiMode = uiMode;
      output_modes[uiMode].__output_mode__.format = GALA_PIXEL_FORMAT_R8G8B8A8;
      output_modes[uiMode].__output_mode__.width = DisplayMode.Width;
      output_modes[uiMode].__output_mode__.height = DisplayMode.Height;
      if (DisplayMode.RefreshRate == 0) {
        // Default to the monitor's refresh rate. This might not be strictly
        // correct but it appears to be fine on AMD/nVidia.
        output_modes[uiMode].__output_mode__.refresh_rate.numer = DevMode.dmDisplayFrequency;
        output_modes[uiMode].__output_mode__.refresh_rate.denom = 1;
      } else {
        output_modes[uiMode].__output_mode__.refresh_rate.numer = DisplayMode.RefreshRate;
        output_modes[uiMode].__output_mode__.refresh_rate.denom = 1;
      }
    }

    for (UINT uiMode = 0; uiMode < outputs[0].ModeCount.uiX8R8G8B8; ++uiMode) {
      const UINT uiAdjustedMode = uiMode + outputs[0].ModeCount.uiA8R8G8B8;
      output_modes_[uiAdjustedMode] = (gala_output_mode_t *)&output_modes[uiAdjustedMode];
      D3DDISPLAYMODE DisplayMode;
      if (FAILED(backend->D3D9->EnumAdapterModes(uiAdapter, D3DFMT_X8R8G8B8, uiMode, &DisplayMode))) {
        // TODO(mike): Free memory.
        if (error_details)
          *error_details = NULL;
        return GALA_ERROR_UNKNOWN;
      }
      output_modes[uiAdjustedMode].uiMode = uiMode;
      output_modes[uiAdjustedMode].__output_mode__.format = GALA_PIXEL_FORMAT_R8G8B8;
      output_modes[uiAdjustedMode].__output_mode__.width = DisplayMode.Width;
      output_modes[uiAdjustedMode].__output_mode__.height = DisplayMode.Height;
      if (DisplayMode.RefreshRate == 0) {
        // Default to the monitor's refresh rate. This might not be strictly
        // correct but it appears to be fine on AMD/nVidia.
        output_modes[uiAdjustedMode].__output_mode__.refresh_rate.numer = DevMode.dmDisplayFrequency;
        output_modes[uiAdjustedMode].__output_mode__.refresh_rate.denom = 1;
      } else {
        output_modes[uiAdjustedMode].__output_mode__.refresh_rate.numer = DisplayMode.RefreshRate;
        output_modes[uiAdjustedMode].__output_mode__.refresh_rate.denom = 1;
      }
    }
  }

  *backend_ = (gala_backend_t *)backend;
  if (error_details)
    *error_details = NULL;
  return GALA_ERROR_NONE;
}

//===----------------------------------------------------------------------===//

gala_error_t gala_backend_shutdown_d3d9(
  gala_backend_t *backend_,
  const gala_error_details_t **error_details)
{
#ifndef GALA_DISABLE_ARGUMENT_CHECKS
  if (backend_->type != GALA_BACKEND_D3D9) {
    if (error_details) {
      *error_details = gala_error_details_create_unformatted(
        GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS,
        "Expected a backend of type `GALA_BACKEND_D3D9'.");
    }
    return GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS;
  }
#endif // !GALA_DISABLE_ARGUMENT_CHECKS
  gala_backend_d3d9_t *backend = (gala_backend_d3d9_t *)backend_;
  backend->D3D9->Release();
  FreeLibrary(backend->hDll);
  const gala_adapter_d3d9_t **adapters =
    ((const gala_adapter_d3d9_t **)backend->__backend__.adapters);
  for (UINT uiAdapter = 0; uiAdapter < backend->__backend__.num_adapters; ++uiAdapter) {
    CloseHandle(((const gala_output_d3d9_t **)adapters[uiAdapter]->__adapter__.outputs)[0]->hMonitor);
    free((void *)adapters[uiAdapter]->__adapter__.outputs[0]);
    free((void *)adapters[uiAdapter]->__adapter__.outputs);
  }
  free((void *)backend->__backend__.adapters[0]);
  free((void *)backend->__backend__.adapters);
  free((void *)backend);
  if (error_details)
    *error_details = NULL;
  return GALA_ERROR_NONE;
}

//===----------------------------------------------------------------------===//

static LRESULT WINAPI _FocusWindowProcW(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  gala_context_d3d9_t *context =
    (gala_context_d3d9_t *)GetPropA(hWnd, "gala_context_d3d9_t");

  switch (uMsg) {
    case WM_NCCREATE: {
    } break;

    case WM_CREATE: {
    } break;

    case WM_DESTROY: {
    } break;

    case WM_NCDESTROY: {
      // According to MSDN, all entries in the property list of a window must
      // be removed (via RemoveProp) before it is destroyed. In practice, this
      // doesn't make any material difference--perhaps a (small) memory leak.
      RemovePropA(hWnd, "gala_context_d3d9_t");
    } return TRUE;

    case WM_ACTIVATEAPP: {
      // TODO(mike): Toggle rendering based on this.
    } break;

    case WM_SHOWWINDOW: {
      // TODO(mike): Toggle rendering based on this.
    } break;

    case WM_CLOSE: {
      // Destruction is inevitable!
      DestroyWindow(hWnd);
    } return TRUE;
  }

  return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

gala_error_t gala_backend_create_context_d3d9(
  gala_backend_t *backend_,
  const size_t adapter_,
  gala_context_t **context_,
  const gala_error_details_t **error_details)
{
#ifndef GALA_DISABLE_ARGUMENT_CHECKS
  if (backend_->type != GALA_BACKEND_D3D9) {
    if (error_details) {
      *error_details = gala_error_details_create_unformatted(
        GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS,
        "Expected a backend of type `GALA_BACKEND_D3D9'.");
    }
    return GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS;
  }
  if ((adapter_ >= backend_->num_adapters)) {
    if (error_details) {
      *error_details = gala_error_details_create_unformatted(
        GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS,
        "Expected `adapter' to be between [0, backend->num_adatpers).");
    }
    return GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS;
  }
  if (context_ == NULL) {
    if (error_details) {
      *error_details = gala_error_details_create_unformatted(
        GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS,
        "Expected `context' to be non-NULL.");
    }
    return GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS;
  }
#endif // !GALA_DISABLE_ARGUMENT_CHECKS
  gala_backend_d3d9_t *backend = (gala_backend_d3d9_t *)backend_;
  gala_adapter_d3d9_t *adapter =
    ((gala_adapter_d3d9_t **)backend->__backend__.adapters)[adapter_];

  gala_context_d3d9_t *context = (gala_context_d3d9_t *)calloc(sizeof(gala_context_d3d9_t), 1);
  gala_assertf(context != NULL, "Ran out of memory.");
  context->__context__._backend = backend_;

  char szUUID[37];
  bitbyte_foundation_uuid_t uuid;
  bitbyte_foundation_uuid_generate(&uuid);
  bitbyte_foundation_uuid_to_s(&uuid, szUUID);

  WCHAR szClassName[37];
  if (!MultiByteToWideChar(CP_UTF8, 0, szUUID, -1, szClassName, 37))
    gala_assertf_always("Generated class name for focus window exceeds buffer size!");

  WNDCLASSEXW wcx;
  memset(&wcx, 0, sizeof(WNDCLASSEX));
  wcx.cbSize        = sizeof(WNDCLASSEX);
  wcx.style         = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
  wcx.lpfnWndProc   = &_FocusWindowProcW;
  wcx.hInstance     = GetModuleHandle(NULL);
  wcx.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wcx.hIcon         = LoadIconW(wcx.hInstance, MAKEINTRESOURCEW(IDI_APPLICATION));
  wcx.hIconSm       = LoadIconW(wcx.hInstance, MAKEINTRESOURCEW(IDI_APPLICATION));
  wcx.lpszClassName = szClassName;

  const BOOL bRegisteredClass = (RegisterClassExW(&wcx) != 0);
  gala_assertf(bRegisteredClass,
               "Unable to create focus window at RegisterClassExW! (%d)",
               GetLastError());

  const DWORD dwStyles = WS_DISABLED;
  const DWORD dwExStyles = WS_EX_NOACTIVATE;

  RECT rClientArea = { 0, 0, 1, 1 };
  AdjustWindowRectEx(&rClientArea, dwStyles, FALSE, dwExStyles);
  const DWORD dwAdjustedWidth = rClientArea.right - rClientArea.left;
  const DWORD dwAdjustedHeight = rClientArea.bottom - rClientArea.top;

  context->hFocusWindow = CreateWindowExW(dwExStyles, szClassName, L"", dwStyles,
                                          0, 0, dwAdjustedWidth, dwAdjustedHeight, NULL,
                                          NULL, GetModuleHandle(NULL), NULL);

  gala_assertf(context->hFocusWindow != NULL,
               "Unable to create focus window at CreateWindowExW! (%d)",
               GetLastError());

  const BOOL bInsertedReferenceToInstance =
    SetPropA(context->hFocusWindow, "gala_context_t", (HANDLE)context);
  gala_assertf(bInsertedReferenceToInstance,
               "Unable to create focus window at SetPropA! (%d)",
               GetLastError());

  static const DWORD dwBehaviourFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING |
                                        D3DCREATE_MULTITHREADED |
                                        D3DCREATE_PUREDEVICE
                                        /* D3DCREATE_FPU_PRESERVE */;

  D3DPRESENT_PARAMETERS PresentParameters;
  PresentParameters.BackBufferWidth = 0;
  PresentParameters.BackBufferHeight = 0;
  PresentParameters.BackBufferFormat = D3DFMT_UNKNOWN;
  PresentParameters.BackBufferCount = 0;
  PresentParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
  PresentParameters.MultiSampleQuality = 0;
  PresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
  PresentParameters.hDeviceWindow = NULL;
  PresentParameters.Windowed = TRUE;
  PresentParameters.EnableAutoDepthStencil = FALSE;
  PresentParameters.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
  PresentParameters.Flags = 0;
  PresentParameters.FullScreen_RefreshRateInHz = 0;
  PresentParameters.PresentationInterval = 0;

  const HRESULT hrCreateDevice = backend->D3D9->CreateDevice(adapter->uiAdapter,
                                                             D3DDEVTYPE_HAL,
                                                             context->hFocusWindow,
                                                             dwBehaviourFlags,
                                                             &PresentParameters,
                                                             &context->Direct3DDevice9);

  gala_assertf(hrCreateDevice == D3D_OK, "Unable to create device. (hresult=%x)", hrCreateDevice);

  *context_ = (gala_context_t *)context;
  if (error_details)
    *error_details = NULL;
  return GALA_ERROR_NONE;
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#endif
