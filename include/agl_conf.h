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

#ifndef _AGL_CONF_H_
#define _AGL_CONF_H_

#if defined(DOXYGEN)
  #define AGL_DONT_AUTODETECT_COMPILER
  #define AGL_DONT_AUTODETECT_PLATFORM
  #define AGL_DONT_AUTODETECT_ARCHITECTURE
  #define AGL_COMPILING
  #define AGL_STATICALLY_LINKING
  #define AGL_PARANOID
  #define AGL_DEBUG_BUILD
  #define AGL_RELEASE_BUILD
#endif

/*! @def AGL_DONT_AUTODETECT_COMPILER
  If defined AGL won't attempt to detect the current compiler based on preprocessor macros.
  Instead, it is expected to be user defined. */
/* #define AGL_DONT_AUTODETECT_COMPILER 1 */

/*! @def AGL_DONT_AUTODETECT_PLATFORM
  If defined AGL won't attempt to detect the target platform based on preprocessor macros.
  Instead, it is expected to be user defined. */
/* #define AGL_DONT_AUTODETECT_PLATFORM 1 */

/*! @def AGL_DONT_AUTODETECT_ARCHITECTURE
  If defined AGL won't attempt to detect the target architecture based on preprocessor macros.
  Instead, it is expected to be user defined. */
/* #define AGL_DONT_AUTODETECT_ARCHITECTURE 1 */

/*! @def AGL_STATICALLY_LINKING
  If defined AGL doesn't mark symbols for dynamic linking with compiler specific keywords. */
/* #define AGL_STATICALLY_LINKING 1 */

/*! @def AGL_COMPILING
  If defined AGL marks symbols for dynamic linking (if AGL_STATICALLY_LINKING is not defined).
  This should be defined during compiler invocation, eg., -DAGL_COMPILING=1 */

/*! @def AGL_PARANOID
  If defined AGL will perform paranoid checks.
  This should be defined during compiler invocation, eg., -DAGL_PARANOID=1 */

/*! @def AGL_DEBUG_BUILD
  If defined AGL will perform debugging related checks and use debug runtimes.
  This should be defined during compiler invocation, eg., -DAGL_DEBUG_BUILD=1 */

/*! @def AGL_RELEASE_BUILD
  If defined AGL will not perform debugging related checks and use release runtimes.
  This should be defined during compiler invocation, eg., -DAGL_RELEASE_BUILD=1 */

#endif /* _AGL_CONF_H_ */
