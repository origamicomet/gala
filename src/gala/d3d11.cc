//===-- gala/d3d11.cc -----------------------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//

#include "gala/d3d11.h"

#if GALA_ENABLE_D3D11

#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  #include <windows.h>
  #include <dxgi.h>
  #include <d3d11.h>
#endif

GALA_BEGIN_EXTERN_C

static struct {
#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  IDXGIFactory *dxgi;

  struct {
    HMODULE dxgi;
    HMODULE d3d11;
  } libs;
#endif
} B;

void gala_d3d11_init(void)
{
#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  B.libs.dxgi = ::LoadLibraryA("dxgi.dll");
  gala_assert(B.libs.dxgi != NULL);

  B.libs.d3d11 = ::LoadLibraryA("d3d11.dll");
  gala_assert(B.libs.d3d11 != NULL);

  // TODO(mtwilliams): Use CreateDXGIFactory1 or CreateDXGIFactory2?
  // TODO(mtwilliams): Get debug interfaces with DXGIGetDebugInterface?

  /* B.dxgi = */ {
    typedef HRESULT (WINAPI *CreateDXGIFactory_fn)(REFIID, void **);
    CreateDXGIFactory_fn CreateDXGIFactory_ =
      (CreateDXGIFactory_fn)GetProcAddress(B.libs.dxgi, "CreateDXGIFactory");
    gala_assertf(CreateDXGIFactory_ != NULL, "Unable to initialize Direct3D 11 runtime because CreateDXGIFactory could not be found.");

    const HRESULT hr = CreateDXGIFactory_(__uuidof(IDXGIFactory), (void **)&B.dxgi);
    gala_assertf(hr == S_OK, "Unable to initialize Direct3D 11 runtime because CreateDXGIFactory failed.");
  }
#endif
}

void gala_d3d11_shutdown(void) {
#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
#endif
}

GALA_END_EXTERN_C

#endif // GALA_ENABLE_D3D11
