//===-- gala/d3d9/adapter.c -------------------------------------*- C++ -*-===//
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

#include "gala/d3d9/adapter.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

void
gala_adapter_d3d9_init(
  gala_adapter_d3d9_t **adapter)
{
  gala_assert_debug(adapter != NULL);

  bitbyte_foundation_tier4_allocator_t *heap = bitbyte_foundation_tier4_heap();
  *adapter = (gala_adapter_d3d9_t *)heap->alloc(heap, sizeof(gala_adapter_d3d9_t), _Alignof(gala_adapter_d3d9_t));
  gala_adapter_init(&(*adapter)->__adapter__);

#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  (*adapter)->_uiAdapter = 0;
#endif
}

//===----------------------------------------------------------------------===//

void
gala_adapter_d3d9_destroy(
  gala_adapter_d3d9_t *adapter)
{
  gala_assert_debug(adapter != NULL);

#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  #if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
    adapter->_uiAdapter = 0;
  #endif
#endif

  bitbyte_foundation_tier4_allocator_t *heap = bitbyte_foundation_tier4_heap();
  gala_adapter_destroy(&adapter->__adapter__);
  heap->free(heap, (void *)adapter);
}

//===----------------------------------------------------------------------===//

int gala_adapter_d3d9_to_s(
  const gala_adapter_d3d9_t *adapter,
  char buf[], const int buf_sz)
{
  gala_assert_debug(adapter != NULL);
  char adapter_as_str[256];
  gala_adapter_to_s(&adapter->__adapter__, adapter_as_str, sizeof(adapter_as_str));
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  return snprintf(buf, buf_sz, "#<gala_adapter_d3d9_t:%.16" PRIxPTR " [%s] _uiAdapter=%x>",
                  adapter, adapter_as_str, adapter->_uiAdapter);
#endif
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//
