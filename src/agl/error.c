//===-- agl/error.c ---------------------------------------------*- C++ -*-===//
//
//  Abstract Graphics Library (AGL)
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//    * Michael Williams <mwilliams@bitbyte.ca>
//
//===----------------------------------------------------------------------===//

#include "agl/error.h"

//===----------------------------------------------------------------------===//

#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

#if defined(_MSC_VER)
  inline int _agl_error_vsnprintf(char *buf, size_t sz, const char *fmt, va_list ap) {
    int count = -1;
    if (sz != 0)
      count = _vsnprintf_s(buf, sz, _TRUNCATE, fmt, ap);
    if (count == -1)
      count = _vscprintf(fmt, ap);
    return count;
  }
#else
  #define _agl_error_vsnprintf vsnprintf
#endif

//===----------------------------------------------------------------------===//

agl_error_details_t *
agl_error_details_construct(
  const char *file,
  unsigned line,
  const char *reason)
{
  // TODO(mwilliams): Use user-specified allocator.
  agl_error_details_t *error_details =
    (agl_error_details_t *)
      malloc(sizeof(agl_error_details_t));

  if (error_details == NULL)
    // If this happens we're truely fucked.
    return NULL;

  error_details->file = file;
  error_details->line = line;
  error_details->reason = reason;
  error_details->__owned__ = 0;

  return error_details;
}

//===----------------------------------------------------------------------===//

agl_error_details_t *
agl_error_details_constructf(
  const char *file,
  unsigned line,
  const char *format,
  ...)
{
  // TODO(mwilliams): Use user-specified allocator.
  agl_error_details_t *error_details =
    (agl_error_details_t *)
      malloc(sizeof(agl_error_details_t));

  if (error_details == NULL)
    // If this happens we're truely fucked.
    return NULL;

  error_details->file = file;
  error_details->line = line;

  /* error_details->reason = */ {
    va_list ap;
    va_start(ap, format);
    const agl_size_t sz = _agl_error_vsnprintf(NULL, 0, format, ap);
    error_details->reason = (const char *)malloc(sz + 1);
    if (error_details->reason == NULL) {
      // Truely fucked if this happens too.
      free((void *)error_details);
      return NULL;
    }
    _agl_error_vsnprintf((char *)error_details->reason, sz, format, ap);
    va_end(ap);
  }

  error_details->__owned__ = 1;

  return error_details;
}

//===----------------------------------------------------------------------===//

void
agl_error_details_destruct(
  agl_error_details_t *error_details)
{
  // TODO(mwilliams): Use user-specified allocator.
  if (error_details) {
    if (error_details->__owned__)
      free((void *)error_details->reason);
    free((void *)error_details);
  }
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//
