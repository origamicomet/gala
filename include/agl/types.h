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
/*! @file include/agl/types.h
     Provides an ISO C9x complaiant stdint.h, and inttypes.h as well as a
     hackish stdbool.h solution for Microsoft's Optimizing C/C++ Compiler.    */
/* ========================================================================== */

#ifndef _AGL_TYPES_H_
#define _AGL_TYPES_H_

/* ========================================================================== */
/*  Standard Types:                                                           */
/*   * stdint.h                                                               */
/*   * inttypes.h                                                             */
/*   * stdbool.h                                                              */
/* ========================================================================== */

/* ========================================================================== */
/*  stdint.h:                                                                 */
/* ========================================================================== */

#ifndef __STDC_LIMIT_MACROS // [
  #define __STDC_LIMIT_MACROS
#endif // __STDC_LIMIT_MACROS ]

#ifndef __STDC_CONSTANT_MACROS // [
  #define __STDC_CONSTANT_MACROS
#endif // __STDC_CONSTANT_MACROS ]

#ifdef _MSC_VER // [
  // ISO C9x  compliant stdint.h for Microsoft Visual Studio
  // Based on ISO/IEC 9899:TC2 Committee draft (May 6, 2005) WG14/N1124
  //
  //  Copyright (c) 2006-2008 Alexander Chemeris
  //
  // Redistribution and use in source and binary forms, with or without
  // modification, are permitted provided that the following conditions are met:
  //
  //   1. Redistributions of source code must retain the above copyright notice,
  //      this list of conditions and the following disclaimer.
  //
  //   2. Redistributions in binary form must reproduce the above copyright
  //      notice, this list of conditions and the following disclaimer in the
  //      documentation and/or other materials provided with the distribution.
  //
  //   3. The name of the author may be used to endorse or promote products
  //      derived from this software without specific prior written permission.
  //
  // THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
  // WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  // MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
  // EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  // SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
  // PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
  // OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
  // WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
  // OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
  // ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  //
  ///////////////////////////////////////////////////////////////////////////////

  #ifndef _MSC_STDINT_H_ // [
  #define _MSC_STDINT_H_

  // Prevent Microsoft's stdint.h from being included:
  #define _STDINT

  #if _MSC_VER > 1000
  #pragma once
  #endif

  #include <limits.h>

  // For Visual Studio 6 in C++ mode and for many Visual Studio versions when
  // compiling for ARM we should wrap <wchar.h> include with 'extern "C++" {}'
  // or compiler give many errors like this:
  //   error C2733: second C linkage of overloaded function 'wmemchr' not allowed
  #ifdef __cplusplus
  extern "C" {
  #endif
  #  include <wchar.h>
  #ifdef __cplusplus
  }
  #endif

  // Define _W64 macros to mark types changing their size, like intptr_t.
  #ifndef _W64
  #  if !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && _MSC_VER >= 1300
  #     define _W64 __w64
  #  else
  #     define _W64
  #  endif
  #endif

  // 7.18.1 Integer types

  // 7.18.1.1 Exact-width integer types

  // Visual Studio 6 and Embedded Visual C++ 4 doesn't
  // realize that, e.g. char has the same size as __int8
  // so we give up on __intX for them.
  #if (_MSC_VER < 1300)
     typedef signed char       int8_t;
     typedef signed short      int16_t;
     typedef signed int        int32_t;
     typedef unsigned char     uint8_t;
     typedef unsigned short    uint16_t;
     typedef unsigned int      uint32_t;
  #else
     typedef signed __int8     int8_t;
     typedef signed __int16    int16_t;
     typedef signed __int32    int32_t;
     typedef unsigned __int8   uint8_t;
     typedef unsigned __int16  uint16_t;
     typedef unsigned __int32  uint32_t;
  #endif
  typedef signed __int64       int64_t;
  typedef unsigned __int64     uint64_t;


  // 7.18.1.2 Minimum-width integer types
  typedef int8_t    int_least8_t;
  typedef int16_t   int_least16_t;
  typedef int32_t   int_least32_t;
  typedef int64_t   int_least64_t;
  typedef uint8_t   uint_least8_t;
  typedef uint16_t  uint_least16_t;
  typedef uint32_t  uint_least32_t;
  typedef uint64_t  uint_least64_t;

  // 7.18.1.3 Fastest minimum-width integer types
  typedef int8_t    int_fast8_t;
  typedef int16_t   int_fast16_t;
  typedef int32_t   int_fast32_t;
  typedef int64_t   int_fast64_t;
  typedef uint8_t   uint_fast8_t;
  typedef uint16_t  uint_fast16_t;
  typedef uint32_t  uint_fast32_t;
  typedef uint64_t  uint_fast64_t;

  // 7.18.1.4 Integer types capable of holding object pointers
  #ifdef _WIN64 // [
     typedef signed __int64    intptr_t;
     typedef unsigned __int64  uintptr_t;
  #else // _WIN64 ][
     typedef _W64 signed int   intptr_t;
     typedef _W64 unsigned int uintptr_t;
  #endif // _WIN64 ]

  // 7.18.1.5 Greatest-width integer types
  typedef int64_t   intmax_t;
  typedef uint64_t  uintmax_t;

  // 7.18.2 Limits of specified-width integer types

  #if !defined(__cplusplus) || defined(__STDC_LIMIT_MACROS) // [   See footnote 220 at page 257 and footnote 221 at page 259

  // 7.18.2.1 Limits of exact-width integer types
  #define INT8_MIN     ((int8_t)_I8_MIN)
  #define INT8_MAX     _I8_MAX
  #define INT16_MIN    ((int16_t)_I16_MIN)
  #define INT16_MAX    _I16_MAX
  #define INT32_MIN    ((int32_t)_I32_MIN)
  #define INT32_MAX    _I32_MAX
  #define INT64_MIN    ((int64_t)_I64_MIN)
  #define INT64_MAX    _I64_MAX
  #define UINT8_MAX    _UI8_MAX
  #define UINT16_MAX   _UI16_MAX
  #define UINT32_MAX   _UI32_MAX
  #define UINT64_MAX   _UI64_MAX

  // 7.18.2.2 Limits of minimum-width integer types
  #define INT_LEAST8_MIN    INT8_MIN
  #define INT_LEAST8_MAX    INT8_MAX
  #define INT_LEAST16_MIN   INT16_MIN
  #define INT_LEAST16_MAX   INT16_MAX
  #define INT_LEAST32_MIN   INT32_MIN
  #define INT_LEAST32_MAX   INT32_MAX
  #define INT_LEAST64_MIN   INT64_MIN
  #define INT_LEAST64_MAX   INT64_MAX
  #define UINT_LEAST8_MAX   UINT8_MAX
  #define UINT_LEAST16_MAX  UINT16_MAX
  #define UINT_LEAST32_MAX  UINT32_MAX
  #define UINT_LEAST64_MAX  UINT64_MAX

  // 7.18.2.3 Limits of fastest minimum-width integer types
  #define INT_FAST8_MIN    INT8_MIN
  #define INT_FAST8_MAX    INT8_MAX
  #define INT_FAST16_MIN   INT16_MIN
  #define INT_FAST16_MAX   INT16_MAX
  #define INT_FAST32_MIN   INT32_MIN
  #define INT_FAST32_MAX   INT32_MAX
  #define INT_FAST64_MIN   INT64_MIN
  #define INT_FAST64_MAX   INT64_MAX
  #define UINT_FAST8_MAX   UINT8_MAX
  #define UINT_FAST16_MAX  UINT16_MAX
  #define UINT_FAST32_MAX  UINT32_MAX
  #define UINT_FAST64_MAX  UINT64_MAX

  // 7.18.2.4 Limits of integer types capable of holding object pointers
  #ifdef _WIN64 // [
  #  define INTPTR_MIN   INT64_MIN
  #  define INTPTR_MAX   INT64_MAX
  #  define UINTPTR_MAX  UINT64_MAX
  #else // _WIN64 ][
  #  define INTPTR_MIN   INT32_MIN
  #  define INTPTR_MAX   INT32_MAX
  #  define UINTPTR_MAX  UINT32_MAX
  #endif // _WIN64 ]

  // 7.18.2.5 Limits of greatest-width integer types
  #define INTMAX_MIN   INT64_MIN
  #define INTMAX_MAX   INT64_MAX
  #define UINTMAX_MAX  UINT64_MAX

  // 7.18.3 Limits of other integer types

  #ifdef _WIN64 // [
  #  define PTRDIFF_MIN  _I64_MIN
  #  define PTRDIFF_MAX  _I64_MAX
  #else  // _WIN64 ][
  #  define PTRDIFF_MIN  _I32_MIN
  #  define PTRDIFF_MAX  _I32_MAX
  #endif  // _WIN64 ]

  #define SIG_ATOMIC_MIN  INT_MIN
  #define SIG_ATOMIC_MAX  INT_MAX

  #ifndef SIZE_MAX // [
  #  ifdef _WIN64 // [
  #     define SIZE_MAX  _UI64_MAX
  #  else // _WIN64 ][
  #     define SIZE_MAX  _UI32_MAX
  #  endif // _WIN64 ]
  #endif // SIZE_MAX ]

  // WCHAR_MIN and WCHAR_MAX are also defined in <wchar.h>
  #ifndef WCHAR_MIN // [
  #  define WCHAR_MIN  0
  #endif  // WCHAR_MIN ]
  #ifndef WCHAR_MAX // [
  #  define WCHAR_MAX  _UI16_MAX
  #endif  // WCHAR_MAX ]

  #define WINT_MIN  0
  #define WINT_MAX  _UI16_MAX

  #endif // __STDC_LIMIT_MACROS ]

  // 7.18.4 Limits of other integer types

  #if !defined(__cplusplus) || defined(__STDC_CONSTANT_MACROS) // [   See footnote 224 at page 260

  // 7.18.4.1 Macros for minimum-width integer constants

  #define INT8_C(val)  val##i8
  #define INT16_C(val) val##i16
  #define INT32_C(val) val##i32
  #define INT64_C(val) val##i64

  #define UINT8_C(val)  val##ui8
  #define UINT16_C(val) val##ui16
  #define UINT32_C(val) val##ui32
  #define UINT64_C(val) val##ui64

  // 7.18.4.2 Macros for greatest-width integer constants
  #define INTMAX_C   INT64_C
  #define UINTMAX_C  UINT64_C

  #endif // __STDC_CONSTANT_MACROS ]

  #include <stddef.h>

  #endif // _MSC_STDINT_H_ ]
#else // _MSC_VER ]
  #include <stddef.h>
  #include <stdint.h>
#endif // !_MSC_VER ]

/* ========================================================================== */
/*  inttypes.h:                                                               */
/* ========================================================================== */

#ifndef __STDC_FORMAT_MACROS // [
  #define __STDC_FORMAT_MACROS
#endif // __STDC_FORMAT_MACROS ]

#ifdef _MSC_VER // [
  // ISO C9x  compliant inttypes.h for Microsoft Visual Studio
  // Based on ISO/IEC 9899:TC2 Committee draft (May 6, 2005) WG14/N1124
  //
  //  Copyright (c) 2006 Alexander Chemeris
  //
  // Redistribution and use in source and binary forms, with or without
  // modification, are permitted provided that the following conditions are met:
  //
  //   1. Redistributions of source code must retain the above copyright notice,
  //      this list of conditions and the following disclaimer.
  //
  //   2. Redistributions in binary form must reproduce the above copyright
  //      notice, this list of conditions and the following disclaimer in the
  //      documentation and/or other materials provided with the distribution.
  //
  //   3. The name of the author may be used to endorse or promote products
  //      derived from this software without specific prior written permission.
  //
  // THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
  // WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  // MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
  // EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  // SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
  // PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
  // OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
  // WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
  // OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
  // ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  //
  ///////////////////////////////////////////////////////////////////////////////

  #ifndef _MSC_INTTYPES_H_ // [
  #define _MSC_INTTYPES_H_

  #if _MSC_VER > 1000
  #pragma once
  #endif

  // 7.8 Format conversion of integer types

  typedef struct {
     intmax_t quot;
     intmax_t rem;
  } imaxdiv_t;

  // 7.8.1 Macros for format specifiers

  #if !defined(__cplusplus) || defined(__STDC_FORMAT_MACROS) // [   See footnote 185 at page 198

  // The fprintf macros for signed integers are:
  #define PRId8       "d"
  #define PRIi8       "i"
  #define PRIdLEAST8  "d"
  #define PRIiLEAST8  "i"
  #define PRIdFAST8   "d"
  #define PRIiFAST8   "i"

  #define PRId16       "hd"
  #define PRIi16       "hi"
  #define PRIdLEAST16  "hd"
  #define PRIiLEAST16  "hi"
  #define PRIdFAST16   "hd"
  #define PRIiFAST16   "hi"

  #define PRId32       "I32d"
  #define PRIi32       "I32i"
  #define PRIdLEAST32  "I32d"
  #define PRIiLEAST32  "I32i"
  #define PRIdFAST32   "I32d"
  #define PRIiFAST32   "I32i"

  #define PRId64       "I64d"
  #define PRIi64       "I64i"
  #define PRIdLEAST64  "I64d"
  #define PRIiLEAST64  "I64i"
  #define PRIdFAST64   "I64d"
  #define PRIiFAST64   "I64i"

  #define PRIdMAX     "I64d"
  #define PRIiMAX     "I64i"

  #define PRIdPTR     "Id"
  #define PRIiPTR     "Ii"

  // The fprintf macros for unsigned integers are:
  #define PRIo8       "o"
  #define PRIu8       "u"
  #define PRIx8       "x"
  #define PRIX8       "X"
  #define PRIoLEAST8  "o"
  #define PRIuLEAST8  "u"
  #define PRIxLEAST8  "x"
  #define PRIXLEAST8  "X"
  #define PRIoFAST8   "o"
  #define PRIuFAST8   "u"
  #define PRIxFAST8   "x"
  #define PRIXFAST8   "X"

  #define PRIo16       "ho"
  #define PRIu16       "hu"
  #define PRIx16       "hx"
  #define PRIX16       "hX"
  #define PRIoLEAST16  "ho"
  #define PRIuLEAST16  "hu"
  #define PRIxLEAST16  "hx"
  #define PRIXLEAST16  "hX"
  #define PRIoFAST16   "ho"
  #define PRIuFAST16   "hu"
  #define PRIxFAST16   "hx"
  #define PRIXFAST16   "hX"

  #define PRIo32       "I32o"
  #define PRIu32       "I32u"
  #define PRIx32       "I32x"
  #define PRIX32       "I32X"
  #define PRIoLEAST32  "I32o"
  #define PRIuLEAST32  "I32u"
  #define PRIxLEAST32  "I32x"
  #define PRIXLEAST32  "I32X"
  #define PRIoFAST32   "I32o"
  #define PRIuFAST32   "I32u"
  #define PRIxFAST32   "I32x"
  #define PRIXFAST32   "I32X"

  #define PRIo64       "I64o"
  #define PRIu64       "I64u"
  #define PRIx64       "I64x"
  #define PRIX64       "I64X"
  #define PRIoLEAST64  "I64o"
  #define PRIuLEAST64  "I64u"
  #define PRIxLEAST64  "I64x"
  #define PRIXLEAST64  "I64X"
  #define PRIoFAST64   "I64o"
  #define PRIuFAST64   "I64u"
  #define PRIxFAST64   "I64x"
  #define PRIXFAST64   "I64X"

  #define PRIoMAX     "I64o"
  #define PRIuMAX     "I64u"
  #define PRIxMAX     "I64x"
  #define PRIXMAX     "I64X"

  #define PRIoPTR     "Io"
  #define PRIuPTR     "Iu"
  #define PRIxPTR     "Ix"
  #define PRIXPTR     "IX"

  // The fscanf macros for signed integers are:
  #define SCNd8       "d"
  #define SCNi8       "i"
  #define SCNdLEAST8  "d"
  #define SCNiLEAST8  "i"
  #define SCNdFAST8   "d"
  #define SCNiFAST8   "i"

  #define SCNd16       "hd"
  #define SCNi16       "hi"
  #define SCNdLEAST16  "hd"
  #define SCNiLEAST16  "hi"
  #define SCNdFAST16   "hd"
  #define SCNiFAST16   "hi"

  #define SCNd32       "ld"
  #define SCNi32       "li"
  #define SCNdLEAST32  "ld"
  #define SCNiLEAST32  "li"
  #define SCNdFAST32   "ld"
  #define SCNiFAST32   "li"

  #define SCNd64       "I64d"
  #define SCNi64       "I64i"
  #define SCNdLEAST64  "I64d"
  #define SCNiLEAST64  "I64i"
  #define SCNdFAST64   "I64d"
  #define SCNiFAST64   "I64i"

  #define SCNdMAX     "I64d"
  #define SCNiMAX     "I64i"

  #ifdef _WIN64 // [
  #  define SCNdPTR     "I64d"
  #  define SCNiPTR     "I64i"
  #else  // _WIN64 ][
  #  define SCNdPTR     "ld"
  #  define SCNiPTR     "li"
  #endif  // _WIN64 ]

  // The fscanf macros for unsigned integers are:
  #define SCNo8       "o"
  #define SCNu8       "u"
  #define SCNx8       "x"
  #define SCNX8       "X"
  #define SCNoLEAST8  "o"
  #define SCNuLEAST8  "u"
  #define SCNxLEAST8  "x"
  #define SCNXLEAST8  "X"
  #define SCNoFAST8   "o"
  #define SCNuFAST8   "u"
  #define SCNxFAST8   "x"
  #define SCNXFAST8   "X"

  #define SCNo16       "ho"
  #define SCNu16       "hu"
  #define SCNx16       "hx"
  #define SCNX16       "hX"
  #define SCNoLEAST16  "ho"
  #define SCNuLEAST16  "hu"
  #define SCNxLEAST16  "hx"
  #define SCNXLEAST16  "hX"
  #define SCNoFAST16   "ho"
  #define SCNuFAST16   "hu"
  #define SCNxFAST16   "hx"
  #define SCNXFAST16   "hX"

  #define SCNo32       "lo"
  #define SCNu32       "lu"
  #define SCNx32       "lx"
  #define SCNX32       "lX"
  #define SCNoLEAST32  "lo"
  #define SCNuLEAST32  "lu"
  #define SCNxLEAST32  "lx"
  #define SCNXLEAST32  "lX"
  #define SCNoFAST32   "lo"
  #define SCNuFAST32   "lu"
  #define SCNxFAST32   "lx"
  #define SCNXFAST32   "lX"

  #define SCNo64       "I64o"
  #define SCNu64       "I64u"
  #define SCNx64       "I64x"
  #define SCNX64       "I64X"
  #define SCNoLEAST64  "I64o"
  #define SCNuLEAST64  "I64u"
  #define SCNxLEAST64  "I64x"
  #define SCNXLEAST64  "I64X"
  #define SCNoFAST64   "I64o"
  #define SCNuFAST64   "I64u"
  #define SCNxFAST64   "I64x"
  #define SCNXFAST64   "I64X"

  #define SCNoMAX     "I64o"
  #define SCNuMAX     "I64u"
  #define SCNxMAX     "I64x"
  #define SCNXMAX     "I64X"

  #ifdef _WIN64 // [
  #  define SCNoPTR     "I64o"
  #  define SCNuPTR     "I64u"
  #  define SCNxPTR     "I64x"
  #  define SCNXPTR     "I64X"
  #else  // _WIN64 ][
  #  define SCNoPTR     "lo"
  #  define SCNuPTR     "lu"
  #  define SCNxPTR     "lx"
  #  define SCNXPTR     "lX"
  #endif  // _WIN64 ]

  #endif // __STDC_FORMAT_MACROS ]

  // 7.8.2 Functions for greatest-width integer types

  // 7.8.2.1 The imaxabs function
  #define imaxabs _abs64

  // 7.8.2.2 The imaxdiv function

  // This is modified version of div() function from Microsoft's div.c found
  // in %MSVC.NET%\crt\src\div.c
  #ifdef STATIC_IMAXDIV // [
  static
  #else // STATIC_IMAXDIV ][
  _inline
  #endif // STATIC_IMAXDIV ]
  imaxdiv_t __cdecl imaxdiv(intmax_t numer, intmax_t denom)
  {
     imaxdiv_t result;

     result.quot = numer / denom;
     result.rem = numer % denom;

     if (numer < 0 && result.rem > 0) {
        // did division wrong; must fix up
        ++result.quot;
        result.rem -= denom;
     }

     return result;
  }

  // 7.8.2.3 The strtoimax and strtoumax functions
  #define strtoimax _strtoi64
  #define strtoumax _strtoui64

  // 7.8.2.4 The wcstoimax and wcstoumax functions
  #define wcstoimax _wcstoi64
  #define wcstoumax _wcstoui64

  #endif // _MSC_INTTYPES_H_ ]
#else // _MSC_VER ]
  #include <inttypes.h>
#endif // !_MSC_VER ]

/* ========================================================================== */
/*  stdbool.h:                                                                */
/* ========================================================================== */

#ifdef _MSC_VER // [
  #ifndef _MSC_STDBOOL_H_ // [
  #define _MSC_STDBOOL_H_

  #if _MSC_VER > 1000
  #pragma once
  #endif

  #ifndef __cplusplus // [
    #ifdef __bool_true_false_are_defined // [
      typedef unsigned char _Bool;
      typedef _Bool bool;
      #define true ((_Bool)1)
      #define false ((_Bool)0)
      #define __bool_true_false_are_defined 1
    #endif // __bool_true_false_are_defined ]
  #endif // !__cplusplus ]

  #endif // _MSC_STDBOOL_H_ ]
#else // _MSC_VER ]
  #include <stdbool.h>
#endif // !_MSC_VER ]

/* ========================================================================== */

#endif /* _AGL_TYPES_H_ */
