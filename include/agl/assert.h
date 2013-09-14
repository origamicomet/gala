/*
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org/>
 */

#ifndef _AGL_ASSERT_H_
#define _AGL_ASSERT_H_

#include <agl/config.h>
#include <agl/detect.h>
#include <agl/compat.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ==========================================================================
    Assertions (agl_assert):
   ========================================================================== */

#define __agl_assert(_Condition) \
  do {if(!(_Condition)){raise(SIGABRT);}} while (0)

#define __agl_dont_assert(_Condition) \
  do {(void)sizeof((_Condition));} while (0)

#if defined(AGL_PARANOID)
  #define __agl_assert_paranoid(_Condition) \
    __agl_assert(_Condition)
#else
  #define __agl_assert_paranoid(_Condition) \
    __agl_dont_assert(_Condition)
#endif

#if (defined(AGL_DEBUG) || defined(AGL_PARANOID))
  #define __agl_assert_debug(_Condition) \
    __agl_assert(_Condition)
#else
  #define __agl_assert_debug(_Condition) \
    __agl_dont_assert(_Condition)
#endif

#if (defined(AGL_DEBUG) || defined(AGL_RELEASE) || defined(AGL_PARANOID))
  #define __agl_assert_release(_Condition) \
    __agl_assert(_Condition)
#else
  #define __agl_assert_release(_Condition) \
    __agl_dont_assert(_Condition)
#endif

#define agl_assert(_Level, _Condition) \
  __agl_assert_##_Level(_Condition)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _AGL_ASSERT_H_ */
