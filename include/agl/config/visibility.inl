//===-- agl/config/visibility.inl -------------------------------*- C++ -*-===//
//
//  Abstract Graphics Library (AGL)
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//    * Michael Williams <mwilliams@bitbyte.ca>
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Documents and defines the pre-processor macros that control symbol
/// visibility.
///
//===----------------------------------------------------------------------===//

#ifndef _AGL_CONFIG_VISIBILITY_INL_
#define _AGL_CONFIG_VISIBILITY_INL_

//============================================================================//

/// \def AGL_LOCAL
/// \brief Marks symbols for internal usage.
///
#ifdef DOXYGEN
  #define AGL_LOCAL
#else // #ifndef DOXYGEN
  #if AGL_LINKAGE == AGL_LINKAGE_STATIC
    #define AGL_LOCAL
  #elif AGL_LINKAGE == AGL_LINKAGE_DYNAMIC
    #ifdef __AGL_IS_BEING_COMPILED__
      #if defined(__GNUC__)
        #if __GNUC__ >= 4
          #define AGL_LOCAL __attribute__ ((visibility ("hidden")))
        #else
          #define AGL_LOCAL
        #endif
      #elif defined(__clang__)
        #define AGL_LOCAL __attribute__ ((visibility ("hidden")))
      #elif defined(_MSC_VER) || defined(__CYGWIN__)
        #define AGL_LOCAL
      #else
        #error ("Unknown or unsupported toolchain!")
      #endif
    #else // #ifndef __AGL_IS_BEING_COMPILED__
      #define AGL_LOCAL
    #endif
  #endif
#endif

/// \def AGL_PUBLIC
/// \brief Marks symbols for public usage.
///
#ifdef DOXYGEN
  #define AGL_PUBLIC
#else // #ifndef DOXYGEN
  #if AGL_LINKAGE == AGL_LINKAGE_STATIC
    #define AGL_PUBLIC
  #elif AGL_LINKAGE == AGL_LINKAGE_DYNAMIC
    #ifdef __AGL_IS_BEING_COMPILED__
      #if defined(__GNUC__)
        #if __GNUC__ >= 4
          #define AGL_PUBLIC __attribute__ ((visibility ("hidden")))
        #else
          #define AGL_PUBLIC
        #endif
      #elif defined(__clang__)
        #define AGL_PUBLIC __attribute__ ((visibility ("hidden")))
      #elif defined(_MSC_VER) || defined(__CYGWIN__)
        #define AGL_PUBLIC __declspec(dllexport)
      #else
        #error ("Unknown or unsupported toolchain!")
      #endif
    #else // #ifndef __AGL_IS_BEING_COMPILED__
      #if (defined(__GNUC__) && (__GNUC__ >= 4))
        #define AGL_PUBLIC __attribute__ ((visibility ("default")))
      #elif defined(__clang__)
        #define AGL_PUBLIC __attribute__ ((visibility ("default")))
      #elif defined(_MSC_VER) || defined(__CYGWIN__)
        #define AGL_PUBLIC __declspec(dllimport)
      #else
        #error ("Unknown or unsupported toolchain!")
      #endif
    #endif
  #endif
#endif

//============================================================================//

#endif // _AGL_CONFIG_VISIBILITY_INL_

//============================================================================//
