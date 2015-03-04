//===-- gala/d3d9.c ---------------------------------------------*- C++ -*-===//
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

#include "gala/d3d9.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

struct gala_backend_d3d9 {
  gala_backend_t __backend__;
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  HMODULE dll;
#endif
  IDirect3D9 *d3d9;
};

//===----------------------------------------------------------------------===//

gala_backend_d3d9_t *
gala_backend_d3d9_init(void)
{
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  bitbyte_foundation_tier4_allocator_t *heap = bitbyte_foundation_tier4_heap();
  gala_backend_d3d9_t *backend = (gala_backend_d3d9_t *)heap->alloc(heap,
                                                                    sizeof(gala_backend_d3d9_t),
                                                                    _Alignof(gala_backend_d3d9_t));

  gala_backend_init(&backend->__backend__);

  backend->dll = LoadLibraryA("d3d9.dll");
  gala_assertf(backend->dll != NULL, "Unable to load Direct3D 9 runtime!");

  // TODO(mtwilliams): Try Direct3DCreate9Ex.
  typedef IDirect3D9 *(WINAPI *Direct3DCreate9_fn)(UINT);
  Direct3DCreate9_fn Direct3DCreate9_ = (Direct3DCreate9_fn)GetProcAddress(backend->dll, "Direct3DCreate9");
  gala_assertf(Direct3DCreate9_ != NULL, "Unable to initialize Direct3D 9 runtime!");
  backend->d3d9 = Direct3DCreate9_(D3D_SDK_VERSION);

  return backend;
#endif
}

//===----------------------------------------------------------------------===//

void
gala_backend_d3d9_shutdown(
  gala_backend_d3d9_t *backend)
{
  gala_assert_debug(backend != NULL);
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  gala_assertf(backend->d3d9->Release() == 0, "Unable to shutdown Direct3D 9 runtime!");
  FreeLibrary(backend->dll);
#endif
}

//===----------------------------------------------------------------------===//

int
gala_backend_d3d9_to_s(
  const gala_backend_d3d9_t *backend,
  char buf[],
  const int buf_sz)
{
  gala_assert_debug(backend != NULL);
  // TODO(mike): Include gala_backend_d3d9_t::d3d9 (as d3d9).
  return snprintf(buf, buf_sz, "#<gala_backend_d3d9_t:%.16" PRIxPTR ">", backend);
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//
