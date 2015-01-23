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

gala_error_t gala_adapter_to_s(
  const gala_adapter_t *adapter,
  char *buf,
  const size_t buf_sz,
  const gala_error_details_t **error_details)
{
#ifndef GALA_DISABLE_ARGUMENT_CHECKS
  if (adapter == NULL) {
    if (error_details) {
      *error_details = gala_error_details_create_unformatted(
        GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS,
        "Expected `adapter' to be non-NULL.");
    }
    return GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS;
  }
  if (buf == NULL) {
    if (error_details) {
      *error_details = gala_error_details_create_unformatted(
        GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS,
        "Expected `buf' to be non-NULL.");
    }
    return GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS;
  }
  if (buf_sz == 0) {
    if (error_details) {
      *error_details = gala_error_details_create_unformatted(
        GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS,
        "Expected `buf' to be greater than `0'.");
    }
    return GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS;
  }
#endif // !GALA_DISABLE_ARGUMENT_CHECKS
  const char *type_as_str = NULL;
  switch (adapter->type) {
    default: type_as_str = "unknown"; break;
    case GALA_ADAPTER_SOFTWARE: type_as_str = "software"; break;
    case GALA_ADAPTER_HARDWARE: type_as_str = "hardware"; break;
    case GALA_ADAPTER_PROXY: type_as_str = "proxy"; break;
  }
  // TODO(mike): Defer to implementation specific implementation.
  const int written = snprintf(buf, buf_sz, "#<gala_adapter_t:%" PRIxPTR " type=`%s'>",
                               adapter, type_as_str);
#ifndef GALA_DISABLE_ERROR_CHECKS
  if (written <= 0) {
    if (error_details) {
      *error_details = gala_error_details_create_unformatted(
        GALA_ERROR_OUT_OF_MEMORY,
        "The specified buffer is not large enough.");
    }
    return GALA_ERROR_OUT_OF_MEMORY;
  }
#endif // !GALA_DISABLE_ERROR_CHECKS
  if (error_details)
    *error_details = NULL;
  return GALA_ERROR_NONE;
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//
