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
  bitbyte_foundation_tier4_allocator_t *heap = bitbyte_foundation_tier4_heap();
  heap->free(heap, (void *)backend);
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
  // TODO(mtwilliams): Include gala_backend_d3d9_t::d3d9 (as d3d9).
  return snprintf(buf, buf_sz, "#<gala_backend_d3d9_t:%.16" PRIxPTR ">", backend);
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

struct gala_adapter_d3d9 {
  gala_adapter_t __adapter__;
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  UINT idx;
  D3DADAPTER_IDENTIFIER9 identifier;
#endif
};

//===----------------------------------------------------------------------===//

size_t
gala_backend_d3d9_num_adapters(
  const gala_backend_d3d9_t *backend)
{
  gala_assert_debug(backend != NULL);
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  return backend->d3d9->GetAdapterCount();
#endif
}

//===----------------------------------------------------------------------===//

const gala_adapter_d3d9_t *
gala_backend_d3d9_adapter(
  const gala_backend_d3d9_t *backend,
  const size_t idx)
{
  gala_assert_debug(backend != NULL);
  gala_assert_debug(idx < gala_backend_d3d9_num_adapters(backend));
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  bitbyte_foundation_tier4_allocator_t *heap = bitbyte_foundation_tier4_heap();
  gala_adapter_d3d9_t *adapter = (gala_adapter_d3d9_t *)heap->alloc(heap,
                                                                    sizeof(gala_adapter_d3d9_t),
                                                                    _Alignof(gala_adapter_d3d9_t));

  gala_adapter_init(&adapter->__adapter__);

  {
    const HRESULT result = backend->d3d9->GetAdapterIdentifier((UINT)idx, 0, &adapter->identifier);
    gala_assertf(result == D3D_OK, "IDirect3D9::GetAdapterIdentifier failed! (%x)", result);
  }

  if (strstr(adapter->identifier.Description, "PerfHUD") != NULL) {
    adapter->__adapter__.type = GALA_ADAPTER_TYPE_PROXY;
  } else {
    // TODO(mtwilliams): Check for support of other formats, namely sRGB.
    const BOOL bHardware =
      (backend->d3d9->CheckDeviceType((UINT)idx, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, FALSE) == D3D_OK) &&
      (backend->d3d9->CheckDeviceType((UINT)idx, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, TRUE) == D3D_OK);
    if (bHardware) {
      adapter->__adapter__.type = GALA_ADAPTER_TYPE_HARDWARE;
    } else {
      const BOOL bSoftware =
        (backend->d3d9->CheckDeviceType((UINT)idx, D3DDEVTYPE_SW, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, FALSE) == D3D_OK) &&
        (backend->d3d9->CheckDeviceType((UINT)idx, D3DDEVTYPE_SW, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, TRUE) == D3D_OK);
      if (bSoftware) {
        adapter->__adapter__.type = GALA_ADAPTER_TYPE_SOFTWARE;
      } else {
        const BOOL bReference =
          (backend->d3d9->CheckDeviceType((UINT)idx, D3DDEVTYPE_REF, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, FALSE) == D3D_OK) &&
          (backend->d3d9->CheckDeviceType((UINT)idx, D3DDEVTYPE_REF, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, TRUE) == D3D_OK);
        if (bReference) {
          adapter->__adapter__.type = GALA_ADAPTER_TYPE_SOFTWARE;
        } else {
          gala_assertf_always("Unable to determine device type!");
        }
      }
    }
  }

  return adapter;
#endif
}

//===----------------------------------------------------------------------===//

void
gala_adapter_d3d9_destroy(
  const gala_adapter_d3d9_t *adapter)
{
  gala_assert_debug(adapter != NULL);
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  bitbyte_foundation_tier4_allocator_t *heap = bitbyte_foundation_tier4_heap();
  heap->free(heap, (void *)adapter);
#endif
}

//===----------------------------------------------------------------------===//

int
gala_adapter_d3d9_to_s(
  const gala_adapter_d3d9_t *adapter,
  char buf[],
  const int buf_sz)
{
  gala_assert_debug(adapter != NULL);
  // TODO(mtwilliams): Include gala_adapter_d3d9_t::identifier::Description (as desc).
  return snprintf(buf, buf_sz, "#<gala_adapter_d3d9_t:%.16" PRIxPTR ">", adapter);
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//
