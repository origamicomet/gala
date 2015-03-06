//===-- gala/d3d11/adapter.c ------------------------------------*- C++ -*-===//
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
#include "gala/d3d11/adapter.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

void
gala_d3d11_adapter_destroy(
  gala_d3d11_adapter_t *adapter)
{
  gala_assert_debug(adapter != NULL);
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  adapter->itf->Release();
#if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
  // This might help find some (stupid) bugs.
  adapter->itf = (IDXGIAdapter *)NULL;
#endif
#endif
  gala_adapter_destroy(&adapter->__adapter__);
  bitbyte_foundation_tier4_allocator_t *heap = bitbyte_foundation_tier4_heap();
  heap->free(heap, (void *)adapter);
}

//===----------------------------------------------------------------------===//

int gala_d3d11_adapter_to_s(
  const gala_d3d11_adapter_t *adapter,
  char buf[],
  const int buf_sz)
{
  gala_assert_debug(adapter != NULL);
  return snprintf(buf, buf_sz, "#<gala_d3d11_adapter_t:%.16" PRIxPTR " IDXGIAdapter=%.16" PRIxPTR ">", adapter, adapter->itf);
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

void D3D11Adapter::destroy() {
  ::gala_d3d11_adapter_destroy((::gala_d3d11_adapter_t *)&this->__adapter__);
}

//===----------------------------------------------------------------------===//

int D3D11Adapter::to_s(char buf[], const int buf_sz) const {
  const ::gala_d3d11_adapter_t *adapter = (const ::gala_d3d11_adapter_t *)this;
  return snprintf(buf, buf_sz, "#<gala::D3D11Adapter:%.16" PRIxPTR " IDXGIAdapter=%.16" PRIxPTR ">", adapter, adapter->itf);
}

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
