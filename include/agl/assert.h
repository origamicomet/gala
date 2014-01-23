/* ========================================================================== */
/*                                                                            */
/* This file is part of the Abstract Graphics Library.                        */
/*                                                                            */
/* Author(s):                                                                 */
/*                                                                            */
/*   Michael Williams <devbug@bitbyte.ca>                                     */
/*                                                                            */
/* This is free and unencumbered software released into the public domain.    */
/*                                                                            */
/* Anyone is free to copy, modify, publish, use, compile, sell, or distribute */
/* this software, either in source code form or as a compiled binary, for any */
/* purpose, commercial or non-commercial, and by any means.                   */
/*                                                                            */
/* In jurisdictions that recognize copyright laws, the author or authors of   */
/* this software dedicate any and all copyright interest in the software to   */
/* the public domain. We make this dedication for the benefit of the public   */
/* large and to the detriment of our heirs and successors. We intend this     */
/* dedication to be an overt act of relinquishment in perpetuity of all       */
/* present and future rights to this software under copyright law.            */
/*                                                                            */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    */
/* THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER   */
/* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,      */
/* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR      */
/* OTHER DEALINGS IN THE SOFTWARE.                                            */
/*                                                                            */
/* For more information, please refer to <http://unlicense.org/>              */
/*                                                                            */
/* ========================================================================== */
/*! @file include/agl/assert.h
     Provides configuration dependent and independent assertion macros.       */
/* ========================================================================== */

#ifndef _AGL_ASSERT_H_
#define _AGL_ASSERT_H_

#include <agl/config.h>
#include <agl/preprocessor.h>
#include <agl/log.h>

#include <signal.h>

/* ========================================================================== */
/*  Assertion:                                                                */
/*   * Independent                                                            */
/*   * Dependent                                                              */
/* ========================================================================== */

/* ========================================================================== */
/*  Independent:                                                              */
/* ========================================================================== */

/*! @def agl_assertf_
  Logs a message based on `_Format` and aborts if `_Condition` fails. */
#define agl_assertf_(_Condition, _Format, ...) \
  do { \
    if (!(_Condition)) { \
      agl_log(AGL_LOG_ERROR, _Format "\n", ## __VA_ARGS__); \
      raise(SIGABRT); \
    } \
  } while (0)

/*! @def agl_assert_
  Logs a message and aborts if `_Condition` fails. */
#define agl_assert_(_Condition) \
  agl_assertf_(_Condition, \
    "An assertion failed!\n" \
    "\n" \
    "  '%s' in %s on line %u\n" \
    "\n", \
    agl_stringificate(_Condition), \
    agl_stringificate(__FILE__), \
    ((unsigned)__LINE__) \
  )

/* ========================================================================== */
/*  Dependent:                                                                */
/* ========================================================================== */

/*! @def agl_assertf
  @copydoc agl_assert_f If, and only if, `_Level` is <= AGL_CONFIGURATION. */
#define agl_assertf(_Level, _Condition, _Format, ...) \
  agl_assertf_##_Level(_Condition, _Format, ## __VA_ARGS__)

#ifdef AGL_PARANOID
  #define agl_assertf_paranoid(_Condition, _Format, ...) \
    agl_assertf_(_Condition, _Format, ## __VA_ARGS__)
#else
  #define agl_assertf_paranoid(_Condition, _Format, ...) \
    do { (void)sizeof((_Condition)); } while (0)
#endif

#if (AGL_CONFIGURATION <= AGL_DEBUG)
  #define agl_assertf_debug(_Condition, _Format, ...) \
    agl_assertf_(_Condition, _Format, ## __VA_ARGS__)
#else
  #define agl_assertf_debug(_Condition, _Format, ...) \
    do { (void)sizeof((_Condition)); } while (0)
#endif

#if (AGL_CONFIGURATION <= AGL_DEVELOPMENT)
  #define agl_assertf_development(_Condition, _Format, ...) \
    agl_assertf_(_Condition, _Format, ## __VA_ARGS__)
#else
  #define agl_assertf_development(_Condition, _Format, ...) \
    do { (void)sizeof((_Condition)); } while (0)
#endif

#if (AGL_CONFIGURATION <= AGL_RELEASE)
  #define agl_assertf_release(_Condition, _Format, ...) \
    agl_assertf_(_Condition, _Format, ## __VA_ARGS__)
#else
  #define agl_assertf_release(_Condition, _Format, ...) \
    do { (void)sizeof((_Condition)); } while (0)
#endif

/*! @def agl_assert
  @copydoc agl_assert_ If, and only if, `_Level` is <= AGL_CONFIGURATION. */
#define agl_assert(_Level, _Condition) \
  agl_assertf(_Level, _Condition, \
    "An assertion failed!\n" \
    "\n" \
    "  '%s' in %s on line %u\n" \
    "\n", \
    agl_stringificate(_Condition), \
    agl_stringificate(__FILE__), \
    ((unsigned)__LINE__) \
  )

/* ========================================================================== */

#endif /* _AGL_ASSERT_H_ */
