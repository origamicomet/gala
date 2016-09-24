//===-- gala/foundation/support/inlining.h --------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Defines pre-processor macros that assist in conveying to the
/// compiler when code should be inlined.
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_FOUNDATION_SUPPORT_INLINING_H_
#define _GALA_FOUNDATION_SUPPORT_INLINING_H_

/// \def GALA_INLINE
/// \brief Code should be inlined.
#if defined(DOXYGEN)
  #define GALA_INLINE
#else // !defined(DOXYGEN)
  #if defined(_MSC_VER)
    #define GALA_INLINE __forceinline
  #elif defined(__clang__) || defined(__GNUC__)
    #define GALA_INLINE __inline __attribute__ ((always_inline))
  #endif
#endif

#endif // _GALA_FOUNDATION_SUPPORT_INLINING_H_
