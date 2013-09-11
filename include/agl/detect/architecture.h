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

#ifndef _AGL_DETECT_ARCHITECTURE_H_
#define _AGL_DETECT_ARCHITECTURE_H_

#include <agl/config.h>

#define AGL_ARCHITECTURE_X86    1
#define AGL_ARCHITECTURE_X86_64 2
#define AGL_ARCHITECTURE_ARM    3

#ifndef AGL_DONT_AUTODETECT_ARCHITECTURE
  /* x86: */
  #if (defined(_M_IX86) || defined(__i386__))
    #define AGL_ARCHITECTURE AGL_ARCHITECTURE_X86
  /* x86-64: */
  #elif (defined(_M_X64) || defined(__x86_64__))
    #define AGL_ARCHITECTURE AGL_ARCHITECTURE_X86_64
  /* ARM: */
  #elif defined(__ARMEL__)
    #define AGL_ARCHITECTURE AGL_ARCHITECTURE_ARM
  #else
    #error ("Unable to detect architecture from pre-proccesor defines!")
  #endif
#else /* AGL_DONT_AUTODETECT_ARCHITECTURE */
  #ifndef AGL_ARCHITECTURE
    #error ("No architecture specified!")
  #endif
#endif

#endif /* _AGL_DETECT_ARCHITECTURE_H_ */
