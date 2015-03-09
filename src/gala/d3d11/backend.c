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
    // TODO(mtwilliams): Allocate enough room on the stack to store all the
    // returned interfaces then copy them to a tightly fit backend->adapters.itfs.
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
  for (UINT adapter = 0; adapter < backend->adapters.count; adapter++) {
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

void
gala_d3d11_backend_create_and_init_engine(
  const gala_d3d11_backend_t *backend,
  const gala_engine_creation_params_t *params,
  gala_d3d11_engine_t **engine_)
{
  gala_assert_debug(backend != NULL);
  gala_assert_debug(engine_ != NULL);
  gala_assert_debug(params != NULL);
  gala_assert_debug((params->type == GALA_ENGINE_TYPE_SOFTWARE) ||
                    (params->type == GALA_ENGINE_TYPE_HARDWARE));
  bitbyte_foundation_tier4_allocator_t *heap = bitbyte_foundation_tier4_heap();
  *engine_ = (gala_d3d11_engine_t *)heap->alloc(heap,
                                                sizeof(gala_d3d11_engine_t),
                                                _Alignof(gala_d3d11_engine_t));
  gala_engine_init(&(*engine_)->__engine__);
  gala_d3d11_engine_t *engine = *engine_;
  engine->__engine__.type = params->type;
  engine->__engine__.flags = params->flags;
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  backend->dxgi.factory->AddRef();
  engine->dxgi.factory = backend->dxgi.factory;
  engine->d3d11.dll = LoadLibraryA("D3D11.dll");
  gala_assertf(engine->d3d11.dll != NULL, "Unable to load Direct3D 11 runtime; could not load 'D3D11.dll'!");
  // TODO(mtwilliams): Get debug layers?
  typedef HRESULT (WINAPI *D3D11CreateDevice_fn)(IDXGIAdapter *, D3D_DRIVER_TYPE, HMODULE, UINT, const D3D_FEATURE_LEVEL *, UINT, UINT, ID3D11Device **, D3D_FEATURE_LEVEL *, ID3D11DeviceContext **);
  D3D11CreateDevice_fn D3D11CreateDevice_ = (D3D11CreateDevice_fn)GetProcAddress(engine->d3d11.dll, "D3D11CreateDevice");
  gala_assertf(D3D11CreateDevice_ != NULL, "Unable to initialize Direct3D 11 runtime; could not find 'D3D11CreateDevice'!");
  UINT flags = 0x00000000ul;
  if (params->flags & GALA_ENGINE_DEBUG)
    flags |= D3D11_CREATE_DEVICE_DEBUG;
  D3D_DRIVER_TYPE driver_type;
  // TODO(mtwilliams): Support GALA_ENGINE_TYPE_SOFTWARE?
  // if (params->type == GALA_ENGINE_TYPE_SOFTWARE)
  //   driver_type = D3D_DRIVER_TYPE_WARP;
  // else if (params->type == GALA_ENGINE_TYPE_HARDWARE)
  //   driver_type = D3D_DRIVER_TYPE_HARDWARE;
  gala_assert(params->type == GALA_ENGINE_TYPE_HARDWARE);
  driver_type = D3D_DRIVER_TYPE_HARDWARE;
  IDXGIAdapter *adapter = NULL;
  if (params->adapter != NULL)
    adapter = ((gala_d3d11_adapter_t *)params->adapter)->itf;
  /* engine->d3d11.device/feature_level/immediate_context = */ {
    // TODO(mtwilliams): Bump minimum requirements to Direct3D 10?
    static const D3D_FEATURE_LEVEL kFeatureLevels[] = {
      D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0,
      D3D_FEATURE_LEVEL_9_3, D3D_FEATURE_LEVEL_9_2, D3D_FEATURE_LEVEL_9_1 };
    const HRESULT hr = D3D11CreateDevice_(adapter, driver_type, NULL, flags,
                                          kFeatureLevels, 6, D3D11_SDK_VERSION,
                                          &engine->d3d11.device,
                                          &engine->d3d11.feature_level,
                                          &engine->d3d11.immediate_context);
    gala_assertf(hr == S_OK, "Unable to initialize Direct3D 11 runtime; D3D11CreateDevice failed (%x)!", hr);
  }
  engine->resources.lock = bitbyte_foundation_mutex_create();
  // TODO(mtwilliams): Release associated interfaces on shutdown?
  bitbyte_foundation_atomic_uint32_store_relaxed(&engine->resources.swap_chains.count, 0);
  memset((void *)&engine->resources.swap_chains.pool, 0, sizeof(engine->resources.swap_chains.pool));
#endif
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
  for (adapter->outputs.count = 0; /* ... */; adapter->outputs.count++) {
    // TODO(mtwilliams): Allocate enough room on the stack to store all the
    // returned interfaces then copy them to a tightly fit adapter->outputs.itfs.
    IDXGIOutput *output;
    if (adapter->itf->EnumOutputs(adapter->outputs.count, &output) == DXGI_ERROR_NOT_FOUND) {
      break;
    } else {
      output->Release();
    }
  }
  adapter->outputs.itfs = (IDXGIOutput **)heap->alloc(heap,
                                                      adapter->outputs.count * sizeof(IDXGIOutput *),
                                                      _Alignof(IDXGIOutput *));
  for (UINT output = 0; output < adapter->outputs.count; output++) {
    const HRESULT hr = adapter->itf->EnumOutputs(output, &adapter->outputs.itfs[output]);
    gala_assertf(hr == S_OK, "Unable to initialize Direct3D 11 runtime; IDXGIAdapter::EnumOutputs failed (%x)!", hr);
  }
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

void D3D11Backend::create_and_init_engine(
    const ::gala_engine_creation_params_t &params,
    ::gala::D3D11Engine **engine) const
{
  ::gala_d3d11_backend_create_and_init_engine(
    (const ::gala_d3d11_backend_t *)&this->__backend__,
    &params, (::gala_d3d11_engine_t **)engine);
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
