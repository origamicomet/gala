//===-- gala/d3d9/backend.c -------------------------------------*- C++ -*-===//
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

#include "gala/d3d9/backend.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

void
gala_backend_d3d9_init(
  gala_backend_d3d9_t **backend)
{
  gala_assert_debug(backend != NULL);

  bitbyte_foundation_tier4_allocator_t *heap = bitbyte_foundation_tier4_heap();
  *backend = (gala_backend_d3d9_t *)heap->alloc(heap, sizeof(gala_backend_d3d9_t), _Alignof(gala_backend_d3d9_t));
  gala_backend_init(&(*backend)->__backend__);

#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  (*backend)->_hDll = LoadLibraryA("d3d9.dll");
  gala_assertf((*backend)->_hDll != NULL, "Unable to load Direct3D9 runtime.");

  // TODO(mtwilliams): Try Direct3DCreate9Ex?
  typedef IDirect3D9 *(WINAPI *Direct3DCreate9_fn)(UINT);
  Direct3DCreate9_fn Direct3DCreate9_ = (Direct3DCreate9_fn)GetProcAddress((*backend)->_hDll, "Direct3DCreate9");
  gala_assertf(Direct3DCreate9_ != NULL, "Unable to initialize Direct3D9 runtime.");

  (*backend)->_D3D9 = Direct3DCreate9_(D3D_SDK_VERSION);
  gala_assertf((*backend)->_D3D9 != NULL, "Unable to initialize Direct3D9 runtime.");

  // TODO(mtwilliams): Query adapters, outputs, and display modes? Or provide
  // a standard interface to query?
#endif
}

//===----------------------------------------------------------------------===//

void
gala_backend_d3d9_shutdown(
  gala_backend_d3d9_t *backend)
{
  gala_assert_debug(backend != NULL);

#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  backend->_D3D9->Release();
  FreeLibrary(backend->_hDll);
  #if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
    backend->_D3D9 = (IDirect3D9 *)NULL;
    backend->_hDll = (HMODULE)NULL;
  #endif
#endif

  bitbyte_foundation_tier4_allocator_t *heap = bitbyte_foundation_tier4_heap();
  gala_backend_shutdown(&backend->__backend__);
  heap->free(heap, (void *)backend);
}

//===----------------------------------------------------------------------===//

int gala_backend_d3d9_to_s(
  const gala_backend_d3d9_t *backend,
  char buf[], const int buf_sz)
{
  gala_assert_debug(backend != NULL);
  char backend_as_str[256];
  gala_backend_to_s(&backend->__backend__, backend_as_str, sizeof(backend_as_str));
  return snprintf(buf, buf_sz, "#<gala_backend_d3d9_t:%.16" PRIxPTR " [%s] _D3D9=%.16" PRIxPTR ">",
                  backend, backend_as_str, backend->_D3D9);
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//
