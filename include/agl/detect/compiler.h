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

#ifndef _AGL_DETECT_COMPILER_H_
#define _AGL_DETECT_COMPILER_H_

#include <agl/config.h>

#define AGL_COMPILER_MSVC  1
#define AGL_COMPILER_CLANG 2
#define AGL_COMPILER_GCC   3
#define AGL_COMPILER_ICC   4

#ifndef AGL_DONT_AUTODETECT_COMPILER
  /* Microsoft Visual Studio C/C++: */
  #if defined(_MSC_VER)
    #define AGL_COMPILER AGL_COMPILER_MSVC
  /* Clang/LLVM: */
  #elif defined(__clang__)
    #define AGL_COMPILER AGL_COMPILER_CLANG
  /* GCC: */
  #elif (defined(__GNUC__) || defined(__GNUG__)) && \
        !(defined(__clang__) || defined(__ICC) || defined(__INTEL_COMPILER))
    #define AGL_COMPILER AGL_COMPILER_GCC
  /* Intel C/C++ Compiler: */
  #elif (defined(__ICC) || defined(__INTEL_COMPILER))
    #define AGL_COMPILER AGL_COMPILER_ICC
  #else
    #error ("Unable to detect compiler from pre-proccesor defines!")
  #endif
#else /* AGL_DONT_AUTODETECT_COMPILER */
  #ifndef AGL_COMPILER
    #error ("No compiler specified!")
  #endif
#endif

#endif /* _AGL_DETECT_COMPILER_H_ */
