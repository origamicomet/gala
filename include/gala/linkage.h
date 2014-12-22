//===-- gala/linkage.h ------------------------------------------*- C++ -*-===//
//
//  Gala
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//    * Michael Williams <mike@origamicomet.com>
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Documents and defines the pre-processor macros that control symbol
/// visibility.
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_LINKAGE_H_
#define _GALA_LINKAGE_H_

//============================================================================//

/// \def GALA_INTERNAL_LINKAGE
/// \brief Exports symbols for inclusion of Gala via objects.
///
#define GALA_INTERNAL_LINKAGE 0

/// \def GALA_STATIC_LINKAGE
/// \brief Exports symbols for inclusion of Gala via static library.
///
#define GALA_STATIC_LINKAGE 1

/// \def GALA_DYNAMIC_LINKAGE
/// \brief Exports symbols for inclusion of Gala via dynamic library.
///
#define GALA_DYNAMIC_LINKAGE 2

//===----------------------------------------------------------------------===//

/// \def GALA_LOCAL
/// \brief Marks symbols for internal usage.
///
#ifdef DOXYGEN
  #define GALA_LOCAL
#else // #ifndef DOXYGEN
  #if GALA_LINKAGE == GALA_STATIC_LINKAGE
    #define GALA_LOCAL
  #elif GALA_LINKAGE == GALA_DYNAMIC_LINAKGE
    #ifdef __GALA_IS_BEING_COMPILED__
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
    #else // #ifndef __GALA_IS_BEING_COMPILED__
      #define GALA_LOCAL
    #endif
  #endif
#endif

//===----------------------------------------------------------------------===//

/// \def GALA_PUBLIC
/// \brief Marks symbols for public usage.
///
#ifdef DOXYGEN
  #define GALA_PUBLIC
#else // #ifndef DOXYGEN
  #if GALA_LINKAGE == GALA_STATIC_LINKAGE
    #define GALA_PUBLIC
  #elif GALA_LINKAGE == GALA_DYNAMIC_LINAKGE
    #ifdef __GALA_IS_BEING_COMPILED__
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
    #else // #ifndef __GALA_IS_BEING_COMPILED__
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

//============================================================================//

#endif // _GALA_LINKAGE_H_

//============================================================================//
