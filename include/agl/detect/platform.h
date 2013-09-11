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

#ifndef _AGL_DETECT_PLATFORM_H_
#define _AGL_DETECT_PLATFORM_H_

#include <agl/config.h>

#define AGL_PLATFORM_WINDOWS 1
#define AGL_PLATFORM_MACOSX  2
#define AGL_PLATFORM_LINUX   3
#define AGL_PLATFORM_BSD     4
#define AGL_PLATFORM_ANDROID 5
#define AGL_PLATFORM_IOS     6

#ifndef AGL_DONT_AUTODETECT_PLATFORM
  /* Microsoft Windows: */
  #if defined(_WIN32) || defined(_WIN64)
    #define AGL_PLATFORM AGL_PLATFORM_WINDOWS
  /* Mac OSX: */
  #elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #if !defined(TARGET_OS_IPHONE)
      #define AGL_PLATFORM AGL_PLATFORM_MACOSX
    #endif
  /* Linux: */
  #elif (defined(__linux__) && !defined(ANDROID))
    #define AGL_PLATFORM AGL_PLATFORM_LINUX
  /* BSD: */
  #elif (defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) \
         || defined(__DragonflyBSD))
    #define AGL_PLATFORM AGL_PLATFORM_BSD
  /* Android: */
  #elif defined(ANDROID)
    #define AGL_PLATFORM AGL_PLATFORM_ANDROID
  /* iOS: */
  #elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #if defined(TARGET_OS_IPHONE)
      #define AGL_PLATFORM AGL_PLATFORM_IOS
    #endif
  #else
    #error ("Unable to detect platform from pre-proccesor defines!")
  #endif
#else /* AGL_DONT_AUTODETECT_PLATFORM */
  #ifndef AGL_PLATFORM
    #error ("No platform specified!")
  #endif
#endif

/*! @def AGL_PLATFORM_IS_POSIX
   */
#define AGL_PLATFORM_IS_POSIX(_Platform) \
  ((AGL_PLATFORM == AGL_PLATFORM_MACOSX)  || \
   (AGL_PLATFORM == AGL_PLATFORM_LINUX)   || \
   (AGL_PLATFORM == AGL_PLATFORM_BSD)     || \
   (AGL_PLATFORM == AGL_PLATFORM_ANDROID) || \
   (AGL_PLATFORM == AGL_PLATFORM_IOS)        )

#endif /* _AGL_DETECT_PLATFORM_H_ */
