//===-- gala/d3d11/backend.c -------------------------------------*- C++ -*-===//
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

#include "gala/d3d11/types.h"
#include "gala/d3d11/backend.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

void
gala_d3d11_backend_init(
  gala_d3d11_backend_t **backend_)
{
  gala_assert_debug(backend_ != NULL);
  bitbyte_foundation_tier4_allocator_t *heap = bitbyte_foundation_tier4_heap();
  *backend_ = (gala_d3d11_backend_t *)heap->alloc(heap,
                                                sizeof(gala_d3d11_backend_t),
                                                _Alignof(gala_d3d11_backend_t));
  gala_backend_init(&(*backend_)->__backend__);
  gala_d3d11_backend_t *backend = *backend_;
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  backend->dxgi.dll = LoadLibraryA("DXGI.dll");
  gala_assertf(backend->dxgi.dll != NULL, "Unable to load Direct3D 11 runtime; could not load 'DXGI.dll'!");
  // TODO(mtwilliams): Try CreateDXGIFactory1 or CreateDXGIFactory2?
  // TODO(mtwilliams): Get debug interfaces with DXGIGetDebugInterface?
  typedef HRESULT (WINAPI *CreateDXGIFactory_fn)(REFIID, void **);
  CreateDXGIFactory_fn CreateDXGIFactory_ = (CreateDXGIFactory_fn)GetProcAddress(backend->dxgi.dll, "CreateDXGIFactory");
  gala_assertf(CreateDXGIFactory_ != NULL, "Unable to initialize Direct3D 11 runtime; could not find 'CreateDXGIFactory'!");
  /* backend->dxgi.factory = */ {
    const HRESULT hr = CreateDXGIFactory_(__uuidof(IDXGIFactory), (void **)&backend->dxgi.factory);
    gala_assertf(hr == S_OK, "Unable to initialize Direct3D 11 runtime; CreateDXGIFactory failed (%x)!", hr);
  }
  for (backend->adapters.count = 0; /* ... */; backend->adapters.count++) {
    IDXGIAdapter *adapter;
    if (backend->dxgi.factory->EnumAdapters(backend->adapters.count, &adapter) == DXGI_ERROR_NOT_FOUND) {
      break;
    } else {
      adapter->Release();
    }
  }
  backend->adapters.itfs = (IDXGIAdapter **)heap->alloc(heap,
                                                        backend->adapters.count * sizeof(IDXGIAdapter *),
                                                        _Alignof(IDXGIAdapter *));
  for (UINT adapter = 0; adapter < backend->adapters.count; ++adapter) {
    const HRESULT hr = backend->dxgi.factory->EnumAdapters(adapter, &backend->adapters.itfs[adapter]);
    gala_assertf(hr == S_OK, "Unable to initialize Direct3D 11 runtime; IDXGIFactory::EnumAdapters failed (%x)!", hr);
  }
#endif
}

//===----------------------------------------------------------------------===//

void
gala_d3d11_backend_shutdown(
  gala_d3d11_backend_t *backend)
{
  gala_assert_debug(backend != NULL);
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  for (UINT adapter = 0; adapter < backend->adapters.count; ++adapter) {
    backend->adapters.itfs[adapter]->Release();
  #if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
    // This might help find some (stupid) bugs.
    backend->adapters.itfs[adapter] = (IDXGIAdapter *)NULL;
  #endif
  }
  backend->dxgi.factory->Release();
  FreeLibrary(backend->dxgi.dll);
#if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
  // This might help find some (stupid) bugs.
  backend->adapters.count = 0;
  backend->adapters.itfs = (IDXGIAdapter **)NULL;
  backend->dxgi.factory = (IDXGIFactory *)NULL;
  backend->dxgi.dll = (HMODULE)NULL;
#endif
#endif
  gala_backend_shutdown(&backend->__backend__);
  bitbyte_foundation_tier4_allocator_t *heap = bitbyte_foundation_tier4_heap();
  heap->free(heap, (void *)backend);
}

//===----------------------------------------------------------------------===//

size_t
gala_d3d11_backend_num_adapters(
  const gala_d3d11_backend_t *backend)
{
  gala_assert_debug(backend != NULL);
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  return backend->adapters.count;
#endif
}

//===----------------------------------------------------------------------===//

gala_d3d11_adapter_t *
gala_d3d11_backend_adapter(
  const gala_d3d11_backend_t *backend,
  const size_t idx)
{
  gala_assert_debug(backend != NULL);
  gala_assert_debug(idx < backend->adapters.count);
  bitbyte_foundation_tier4_allocator_t *heap = bitbyte_foundation_tier4_heap();
  gala_d3d11_adapter_t *adapter = (gala_d3d11_adapter_t *)heap->alloc(heap,
                                                                      sizeof(gala_d3d11_adapter_t),
                                                                      _Alignof(gala_d3d11_adapter_t));
  gala_adapter_init(&adapter->__adapter__);
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  backend->adapters.itfs[idx]->AddRef();
  adapter->itf = backend->adapters.itfs[idx];
#endif
  return adapter;
}

//===----------------------------------------------------------------------===//

int gala_d3d11_backend_to_s(
  const gala_d3d11_backend_t *backend,
  char buf[],
  const int buf_sz)
{
  gala_assert_debug(backend != NULL);
  return snprintf(buf, buf_sz, "#<gala_d3d11_backend_t:%.16" PRIxPTR " IDXGIFactory=%.16" PRIxPTR ">", backend, backend->dxgi.factory);
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

void D3D11Backend::init(::gala::D3D11Backend **backend) {
  ::gala_d3d11_backend_init((::gala_d3d11_backend_t **)backend);
}

//===----------------------------------------------------------------------===//

void D3D11Backend::shutdown() {
  ::gala_d3d11_backend_shutdown((::gala_d3d11_backend_t *)&this->__backend__);
}

//===----------------------------------------------------------------------===//

size_t D3D11Backend::num_adapters() const {
  return ::gala_d3d11_backend_num_adapters((const ::gala_d3d11_backend_t *)&this->__backend__);
}

//===----------------------------------------------------------------------===//

::gala::D3D11Adapter *D3D11Backend::adapter(const size_t idx) const {
  return (::gala::D3D11Adapter *)::gala_d3d11_backend_adapter((const ::gala_d3d11_backend_t *)&this->__backend__, idx);
}

//===----------------------------------------------------------------------===//

int D3D11Backend::to_s(char buf[], const int buf_sz) const {
  const ::gala_d3d11_backend_t *backend = (const ::gala_d3d11_backend_t *)this;
  return snprintf(buf, buf_sz, "#<gala::D3D11Backend:%.16" PRIxPTR " IDXGIFactory=%.16" PRIxPTR ">", backend, backend->dxgi.factory);
}

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
