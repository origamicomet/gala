//===-- gala/adapter.c ------------------------------------------*- C++ -*-===//
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

#include "gala/adapter.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

void
gala_adapter_init(
  gala_adapter_t *adapter)
{
  gala_assert_debug(adapter != NULL);
  adapter->type = GALA_ADAPTER_UNKNOWN;
  adapter->desc[0] = '\0';
}

//===----------------------------------------------------------------------===//

void
gala_adapter_destroy(
  gala_adapter_t *adapter)
{
  gala_assert_debug(adapter != NULL);
#if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
  adapter->type = GALA_ADAPTER_UNKNOWN;
  adapter->desc[0] = '\0';
#endif
}

//===----------------------------------------------------------------------===//

int gala_adapter_to_s(
  const gala_adapter_t *adapter,
  char buf[], const int buf_sz)
{
  gala_assert_debug(adapter != NULL);
  const char *type_as_str = NULL;
  switch (adapter->type) {
    default: type_as_str = "#unknown"; break;
    case GALA_ADAPTER_SOFTWARE: type_as_str = "software"; break;
    case GALA_ADAPTER_HARDWARE: type_as_str = "hardware"; break;
    case GALA_ADAPTER_PROXY: type_as_str = "proxy"; break;
  }
  return snprintf(buf, buf_sz, "#<gala_adapter_t:%.16" PRIxPTR " type=%s desc='%s'>",
                  adapter, type_as_str, adapter->desc);
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//
