//===-- gala/foundation/support/reachability.h ----------*- mode: C++11 -*-===//
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
/// compiler the reachability of code.
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_FOUNDATION_SUPPORT_REACHABILITY_H_
#define _GALA_FOUNDATION_SUPPORT_REACHABILITY_H_

/// \def GALA_TRAP
/// \brief Errant, but reachable, code path.
#if defined(DOXYGEN)
  #define GALA_TRAP()
#else // !defined(DOXYGEN)
  #if defined(_MSC_VER)
    #define GALA_TRAP() __debugbreak()
  #elif defined(__GNUC__)
    #define GALA_TRAP() __builtin_trap()
  #endif
#endif

/// \def GALA_UNREACHABLE
/// \brief Code is unreachable.
#if defined(DOXYGEN)
  #define GALA_UNREACHABLE()
#else // !defined(GALA_UNREACHABLE)
  #if defined(_MSC_VER)
    #define GALA_UNREACHABLE() __assume(0)
  #elif defined(__clang__)
    #define GALA_UNREACHABLE() __builtin_unreachable()
  #elif defined(__GNUC__)
    #if __GNUC_VERSION__ >= 40500
      #define GALA_UNREACHABLE() __builtin_unreachable()
    #else // __GNUC_VERSION__ < 40500
      #include <signal.h>
      #define GALA_UNREACHABLE() do { ::signal(SIGTRAP); } while(0, 0)
    #endif
  #endif
#endif

#endif // _GALA_FOUNDATION_SUPPORT_REACHABILITY_H_
