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

//===----------------------------------------------------------------------===//

#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  #define WIN32_LEAN_AND_MEAN
  #define WIN32_EXTRA_LEAN

  #include <windows.h>
  #include <d3d9.h>

  #undef WIN32_EXTRA_LEAN
  #undef WIN32_LEAN_AND_MEAN

  #undef NEAR
  #undef FAR
  #undef near
  #undef far
  #undef NO_ERROR
  #undef ERROR
  #undef MK_SHIFT
  #undef MK_ALT
  #undef min
  #undef max
  #undef rad1
#else
  #error ("Direct3D 9 is unavailable or unsupported on this platform!")
#endif

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

struct gala_d3d9_backend {
  gala_backend_t __backend__;
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  HMODULE dll;
  IDirect3D9 *d3d9;
#endif
};

//===----------------------------------------------------------------------===//

void
gala_d3d9_backend_init(
  gala_d3d9_backend_t **backend_)
{
  gala_assert_debug(backend_ != NULL);
  bitbyte_foundation_tier4_allocator_t *heap = bitbyte_foundation_tier4_heap();
  *backend_ = (gala_d3d9_backend_t *)heap->alloc(heap,
                                                sizeof(gala_d3d9_backend_t),
                                                _Alignof(gala_d3d9_backend_t));
  gala_backend_init(&(*backend_)->__backend__);
  gala_d3d9_backend_t *backend = *backend_;
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  backend->dll = LoadLibraryA("d3d9.dll");
  gala_assertf(backend->dll != NULL, "Unable to load Direct3D 9 runtime!");
  // TODO(mtwilliams): Try Direct3DCreate9Ex?
  typedef IDirect3D9 *(WINAPI *Direct3DCreate9_fn)(UINT);
  Direct3DCreate9_fn Direct3DCreate9_ = (Direct3DCreate9_fn)GetProcAddress(backend->dll, "Direct3DCreate9");
  gala_assertf(Direct3DCreate9_ != NULL, "Unable to initialize Direct3D 9 runtime!");
  backend->d3d9 = Direct3DCreate9_(D3D_SDK_VERSION);
  gala_assertf(backend->d3d9 != NULL, "Unable to initialize Direct3D 9 runtime!");
#endif
}

//===----------------------------------------------------------------------===//

void
gala_d3d9_backend_shutdown(
  gala_d3d9_backend_t *backend)
{
  gala_assert_debug(backend != NULL);
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  backend->d3d9->Release();
  FreeLibrary(backend->dll);
#if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
  // This might help find some (stupid) bugs.
  backend->d3d9 = (IDirect3D9 *)NULL;
  backend->dll = (HMODULE)NULL;
#endif
#endif
  gala_backend_shutdown(&backend->__backend__);
  bitbyte_foundation_tier4_allocator_t *heap = bitbyte_foundation_tier4_heap();
  heap->free(heap, (void *)backend);
}

//===----------------------------------------------------------------------===//

int gala_d3d9_backend_to_s(
  const gala_d3d9_backend_t *backend,
  char buf[],
  const int buf_sz)
{
  gala_assert_debug(backend != NULL);
  return snprintf(buf, buf_sz, "#<gala_d3d9_backend_t:%.16" PRIxPTR " IDirect3D9=%.16" PRIxPTR " >", backend, backend->d3d9);
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace gala {

//===----------------------------------------------------------------------===//

void D3D9Backend::init(::gala::D3D9Backend **backend) {
  ::gala_d3d9_backend_init((::gala_d3d9_backend_t **)backend);
}

//===----------------------------------------------------------------------===//

void D3D9Backend::shutdown() {
  ::gala_d3d9_backend_shutdown((::gala_d3d9_backend_t *)&this->__backend__);
}

//===----------------------------------------------------------------------===//

int D3D9Backend::to_s(char buf[], const int buf_sz) const {
  const ::gala_d3d9_backend_t *backend = (const ::gala_d3d9_backend_t *)this;
  return snprintf(buf, buf_sz, "#<gala::D3D9Backend:%.16" PRIxPTR " IDirect3D9=%.16" PRIxPTR " >", backend, backend->d3d9);
}

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
