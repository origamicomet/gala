//===-- gala/error.c --------------------------------------------*- C++ -*-===//
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

#include "gala/error.h"

//===----------------------------------------------------------------------===//

#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

const gala_error_details_t *gala_error_details_create_formatted(
  const gala_error_t error,
  const char *format,
  ...)
{
  // TODO(mike): Use a user-specified allocator.
  gala_error_details_t *error_details =
    (gala_error_details_t *)calloc(sizeof(gala_error_details_t), 1);
  error_details->error = error;
  va_list ap;
  va_start(ap, format);
  const int buf_sz = vsnprintf(NULL, -1, format, ap);
  char *buf = (char *)calloc(1, buf_sz + 1);
  vsnprintf(buf, buf_sz, format, ap);
  error_details->details = (const char *)buf;
  error_details->_own_details_mem = true;
  return error_details;
}

//===----------------------------------------------------------------------===//

const gala_error_details_t *gala_error_details_create_unformatted(
  const gala_error_t error,
  const char *details)
{
  // TODO(mike): Use a user-specified allocator.
  gala_error_details_t *error_details =
    (gala_error_details_t *)calloc(sizeof(gala_error_details_t), 1);
  error_details->error = error;
  error_details->details = details;
  error_details->_own_details_mem = false;
  return error_details;
}

//===----------------------------------------------------------------------===//

void gala_error_details_destroy(
  const gala_error_details_t *error_details)
{
  if (error_details) {
    if (error_details->_own_details_mem) {
      if (error_details->details) {
        free((void *)error_details->details);
      }
    }
    free((void *)error_details);
  }
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//
