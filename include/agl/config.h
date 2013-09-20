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

#ifndef _AGL_CONFIG_H_
#define _AGL_CONFIG_H_

/* ==========================================================================
    Compiler, architecture, and platform auto-detection:
   ========================================================================== */

/*! @def AGL_DONT_AUTODETECT_COMPILER
  If defined AGL won't attempt to detect the current compiler based on
  pre-processor defines. Instead it is expected to be user defined. */
#if defined(DOXYGEN)
  #define AGL_DONT_AUTODETECT_COMPILER
#endif

/*! @def AGL_DONT_AUTODETECT_PLATFORM
  If defined AGL won't attempt to detect the current platform based on
  pre-processor defines. Instead it is expected to be user defined. */
#if defined(DOXYGEN)
  #define AGL_DONT_AUTODETECT_PLATFORM
#endif

/*! @def AGL_DONT_AUTODETECT_ARCHITECTURE
  If defined AGL won't attempt to detect the current architecture based on
  pre-processor defines. Instead it is expected to be user defined. */
#if defined(DOXYGEN)
  #define AGL_DONT_AUTODETECT_ARCHITECTURE
#endif

/* ==========================================================================
    Linking:
   ========================================================================== */

/*! @def AGL_STATICALLY_LINKING
  If defined AGL doesn't utilize compiler specific keywords to mark public
  symbols for dynamic linking. */
#if defined(DOXYGEN)
  #define AGL_STATICALLY_LINKING
#endif

/* ==========================================================================
    Debugging:
   ========================================================================== */

/*! @define AGL_PARANOID
  If defined AGL will perform paranoid checks. This should be defined during
  compiler invocation. */
#if defined(DOXYGEN)
  #define AGL_PARANOID
#endif

/*! @define AGL_DEBUG
  If defined AGL will perform debugging checks. This should be defined
  during compiler invocation. */
#if defined(DOXYGEN)
  #define AGL_DEBUG
#endif

/*! @define AGL_RELEASE
  If defined AGL won't perform any debugging checks. This should be defined
  during compiler invocation. */
#if defined(DOXYGEN)
  #define AGL_RELEASE
#endif

#endif /* _AGL_CONFIG_H_ */
