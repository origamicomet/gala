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

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//
