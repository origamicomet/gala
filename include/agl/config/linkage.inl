//===-- agl/config/linkage.inl ----------------------------------*- C++ -*-===//
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
/// \brief Documents and defines the pre-processor macros that control linkage.
///
//===----------------------------------------------------------------------===//

#ifndef _AGL_CONFIG_LINKAGE_INL_
#define _AGL_CONFIG_LINKAGE_INL_

//============================================================================//

/// \def AGL_LINKAGE_INTERNAL
/// \brief Exports symbols for static linkage.
///
#define AGL_LINKAGE_STATIC 1

/// \def AGL_LINKAGE_INTERNAL
/// \brief Exports symbols for dynamic linkage.
///
#define AGL_LINKAGE_DYNAMIC 2

//===----------------------------------------------------------------------===//

/// \def AGL_LINKAGE
/// \brief Specifies if symbols are exported for static or dynamic linkage.
///
#ifdef DOXYGEN
  #define AGL_LINKAGE AGL_LINKAGE_STATIC
#else // #ifndef DOXYGEN
  #ifdef AGL_LINKAGE
    #if (AGL_LINKAGE != AGL_LINKAGE_STATIC) && \
        (AGL_LINKAGE != AGL_LINKAGE_DYNAMIC)
      #error ("Invalid or unknown linkage specified.")
    #else
    #endif
  #else // ifndef AGL_LINKAGE
    #error ("Linkage not specified.")
  #endif
#endif

//============================================================================//

#endif // _AGL_CONFIG_LINKAGE_INL_

//============================================================================//
