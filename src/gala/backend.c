//===-- gala/backend.c ------------------------------------------*- C++ -*-===//
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

#include "gala/backend.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

extern
gala_error_t gala_backend_initialize_d3d9(
  gala_backend_t **backend,
  const gala_error_details_t **error_details);

//===----------------------------------------------------------------------===//

gala_error_t gala_backend_initialize(
  const gala_backend_type_t type,
  gala_backend_t **backend,
  const gala_error_details_t **error_details)
{
#ifndef GALA_DISABLE_ARGUMENT_CHECKS
  if ((type < GALA_BACKEND_NULL) || (type > GALA_BACKEND_D3D9)) {
    if (error_details) {
      *error_details = gala_error_details_create_unformatted(
        GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS,
        "Expected `type' to be a valid ::gala_backend_type_t.");
    }
    return GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS;
  }
  if (backend == NULL) {
    if (error_details) {
      *error_details = gala_error_details_create_unformatted(
        GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS,
        "Expected `backend' to be non-NULL.");
    }
    return GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS;
  }
#endif // !GALA_DISABLE_ARGUMENT_CHECKS
  switch (type) {
    // TODO(mike): Provide a null backend.
    // case GALA_BACKEND_NULL:
    //   return gala_backend_initialize_null(backend, error_details);
    case GALA_BACKEND_D3D9:
      return gala_backend_initialize_d3d9(backend, error_details);
  #ifndef GALA_DISABLE_ERROR_CHECKS
    default:
      if (error_details) {
        *error_details = gala_error_details_create_unformatted(
          GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS,
          "Unknown or unimplemented backend `type'.");
      }
      return GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS;
  #endif // !GALA_DISABLE_ERROR_CHECKS
  }
  if (error_details)
    *error_details = NULL;
  return GALA_ERROR_UNKNOWN;
}

//===----------------------------------------------------------------------===//

gala_error_t gala_backend_to_s(
  const gala_backend_t *backend,
  char *buf,
  const size_t buf_sz,
  const gala_error_details_t **error_details)
{
#ifndef GALA_DISABLE_ARGUMENT_CHECKS
  if (backend == NULL) {
    if (error_details) {
      *error_details = gala_error_details_create_unformatted(
        GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS,
        "Expected `backend' to be non-NULL.");
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
  switch (backend->type) {
    default: type_as_str = "unknown"; break;
    case GALA_BACKEND_NULL: type_as_str = "null"; break;
    case GALA_BACKEND_D3D9: type_as_str = "direct3d9"; break;
  }
  // TODO(mike): Defer to implementation specific implementation.
  const int written = snprintf(buf, buf_sz, "#<gala_backend_t:%.16" PRIxPTR " type=`%s'>",
                               backend, type_as_str);
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
