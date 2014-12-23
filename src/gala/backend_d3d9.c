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
///
/// \file
/// \brief
///
//===----------------------------------------------------------------------===//

#include "gala/backend_d3d9.h"

//===----------------------------------------------------------------------===//

#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  #define _WIN32_LEAN_AND_MEAN
  #include <windows.h>
  #include <d3d9.h>
#endif

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

static BOOL gala_d3d9_initialized_ = FALSE;
static HMODULE gala_d3d9_dll_ = NULL;
static IDirect3D9 *gala_d3d9_ = NULL;

//===----------------------------------------------------------------------===//

typedef IDirect3D9 * (WINAPI *Direct3DCreate9_fn)(
  /* _In_ */  UINT SDKVersion);
static Direct3DCreate9_fn Direct3DCreate9_ = NULL;

//===----------------------------------------------------------------------===//

bool gala_backend_init_d3d9(void)
{
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
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
  gala_d3d9_ = Direct3DCreate9_(D3D_SDK_VERSION);
  return true;
#else // != BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  // TODO(mike): Provide details.
  return false;
#endif
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

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
