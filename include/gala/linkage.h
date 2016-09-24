//===-- gala/linkage.h ----------------------------------*- mode: C++11 -*-===//
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
/// \brief Defines pre-processor macros that specify symbol visibility.
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_LINKAGE_H_
#define _GALA_LINKAGE_H_

/// \def GALA_LINKAGE_INTERNAL
/// \brief Exports symbols for inclusion of Gala via objects.
#define GALA_LINKAGE_INTERNAL 0

/// \def GALA_LINKAGE_STATIC
/// \brief Exports symbols for inclusion of Gala via static library.
#define GALA_LINKAGE_STATIC 1

/// \def GALA_LINKAGE_DYNAMIC
/// \brief Exports symbols for inclusion of Gala via dynamic library.
#define GALA_LINKAGE_DYNAMIC 2

/// \def GALA_LINKAGE
/// \brief Specifies how you intend to link to Gala.
#if !defined(GALA_LINKAGE)
  #error ("Please specify how you intend on linking to Gala by defining `GALA_LINKAGE'.")
#endif

/// \def GALA_LOCAL
/// \brief Marks a symbol for internal usage.
#if defined (DOXYGEN)
  #define GALA_LOCAL
#else // #if !defined(DOXYGEN)
  #if GALA_LINKAGE == GALA_LINKAGE_STATIC
    #define GALA_LOCAL
  #elif GALA_LINKAGE == GALA_LINKAGE_DYNAMIC
    #if defined (__GALA_IS_BEING_COMPILED__)
      #if defined(__GNUC__)
        #if __GNUC__ >= 4
          #define GALA_LOCAL __attribute__ ((visibility ("hidden")))
        #else
          #define GALA_LOCAL
        #endif
      #elif defined(__clang__)
        #define GALA_LOCAL __attribute__ ((visibility ("hidden")))
      #elif defined(_MSC_VER) || defined(__CYGWIN__)
        #define GALA_LOCAL
      #else
        #error ("Unknown or unsupported toolchain!")
      #endif
    #else // #if !defined(__GALA_IS_BEING_COMPILED__)
      #define GALA_LOCAL
    #endif
  #endif
#endif

/// \def GALA_PUBLIC
/// \brief Marks a symbol for public usage.
#if defined (DOXYGEN)
  #define GALA_PUBLIC
#else // #if !defined(DOXYGEN)
  #if GALA_LINKAGE == GALA_LINKAGE_STATIC
    #define GALA_PUBLIC
  #elif GALA_LINKAGE == GALA_LINKAGE_DYNAMIC
    #if defined (__GALA_IS_BEING_COMPILED__)
      #if defined(__GNUC__)
        #if __GNUC__ >= 4
          #define GALA_PUBLIC __attribute__ ((visibility ("default")))
        #else
          #define GALA_PUBLIC
        #endif
      #elif defined(__clang__)
        #define GALA_PUBLIC __attribute__ ((visibility ("default")))
      #elif defined(_MSC_VER) || defined(__CYGWIN__)
        #define GALA_PUBLIC __declspec(dllexport)
      #else
        #error ("Unknown or unsupported toolchain!")
      #endif
    #else // #if !defined(__GALA_IS_BEING_COMPILED__)
      #if (defined(__GNUC__) && (__GNUC__ >= 4))
        #define GALA_PUBLIC
      #elif defined(__clang__)
        #define GALA_PUBLIC
      #elif defined(_MSC_VER) || defined(__CYGWIN__)
        #define GALA_PUBLIC __declspec(dllimport)
      #else
        #error ("Unknown or unsupported toolchain!")
      #endif
    #endif
  #endif
#endif

/// \def GALA_BEGIN_EXTERN_C
/// \internal
/// \def GALA_END_EXTERN_C
/// \internal
#if defined (DOXYGEN)
  #define GALA_BEGIN_EXTERN_C
  #define GALA_END_EXTERN_C
#else // #if !defined(DOXYGEN)
  #if defined(__cplusplus)
    #define GALA_BEGIN_EXTERN_C extern "C" {
    #define GALA_END_EXTERN_C }
  #else // #if !defined(__cplusplus)
    #define GALA_BEGIN_EXTERN_C
    #define GALA_END_EXTERN_C
  #endif
#endif

/// \def GALA_BEGIN_NAMESPACE
/// \internal
/// \def GALA_END_NAMESPACE
/// \internal
#define GALA_BEGIN_NAMESPACE namespace gala {
#define GALA_END_NAMESPACE } // gala

#endif // _GALA_LINKAGE_H_
