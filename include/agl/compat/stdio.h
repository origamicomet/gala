//===-- agl/compat/stdio.h --------------------------------------*- C++ -*-===//
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
///
/// \file
/// \brief Enforces an ISO C9x complaint stdio.h.
///
//===----------------------------------------------------------------------===//

#ifndef _AGL_COMPAT_STDIO_H_
#define _AGL_COMPAT_STDIO_H_

//============================================================================//

#include <stdio.h>
#include <stdarg.h>

//============================================================================//

#if defined(_MSC_VER)
  #define vsnprintf __agl_vsnprintf
  inline int __agl_vsnprintf(
    char *buf, size_t sz, const char *fmt, va_list ap)
  {
    int count = -1;
    if (sz != 0)
      count = _vsnprintf_s(buf, sz, _TRUNCATE, fmt, ap);
    if (count == -1)
      count = _vscprintf(fmt, ap);
    return count;
  }

  #define snprintf __agl_snprintf
  inline int __agl_snprintf(
    char *buf, size_t sz, const char *fmt, ...)
  {
    va_list ap;
    va_start(ap, fmt);
    return __agl_vsnprintf(buf, sz, fmt, ap);
  }
#endif

//============================================================================//

#endif // _AGL_COMPAT_STDIO_H_

//============================================================================//
