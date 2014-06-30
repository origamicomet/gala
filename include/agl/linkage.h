//===-- agl/linakge.h -------------------------------------------*- C++ -*-===//
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
/// \brief Defines the pre-processor macros that assist with symbol visibility.
///
//===----------------------------------------------------------------------===//

#ifndef _AGL_LINKAGE_H_
#define _AGL_LINKAGE_H_

//============================================================================//

/// \def AGL_INTERNAL_LINKAGE
/// \brief Exports symbols for inclusion of AGL via objects.
///
#define AGL_INTERNAL_LINKAGE 0

/// \def AGL_STATIC_LINKAGE
/// \brief Exports symbols for inclusion of AGL via static library.
///
#define AGL_STATIC_LINKAGE 1

/// \def AGL_DYNAMIC_LINKAGE
/// \brief Exports symbols for inclusion of AGL via dynamic library.
///
#define AGL_DYNAMIC_LINKAGE 2

//===----------------------------------------------------------------------===//

/// \def AGL_EXPORT
/// \brief Marks a symbol for export.
///
#ifdef _MSC_VER
  #ifdef AGL_LINKAGE
    #if AGL_LINKAGE == AGL_INTERNAL_LINKAGE
      #define AGL_EXPORT
    #elif AGL_LINKAGE == AGL_STATIC_LINKAGE
      #define AGL_EXPORT
    #elif AGL_DYNAMIC_LINKAGE == AGL_DYNAMIC_LINKAGE
      #ifdef AGL_COMPILING
        #define AGL_EXPORT __declspec(dllexport)
      #else
        #define AGL_EXPORT __declspec(dllimport)
      #endif
    #endif
  #else
    #error ("You need to specify AGL_LINKAGE when building and using AGL!")
  #endif
#else
  #define AGL_EXPORT
#endif

//============================================================================//

#endif // _AGL_LINKAGE_H_

//============================================================================//
