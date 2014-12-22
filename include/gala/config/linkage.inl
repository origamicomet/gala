//===-- gala/config/linkage.inl ---------------------------------*- C++ -*-===//
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
/// \brief Documents and defines the pre-processor macros that control linkage.
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_CONFIG_LINKAGE_INL_
#define _GALA_CONFIG_LINKAGE_INL_

//============================================================================//

/// \def GALA_LINKAGE_INTERNAL
/// \brief Exports symbols for static linkage.
///
#define GALA_LINKAGE_STATIC 1

/// \def GALA_LINKAGE_INTERNAL
/// \brief Exports symbols for dynamic linkage.
///
#define GALA_LINKAGE_DYNAMIC 2

//===----------------------------------------------------------------------===//

/// \def GALA_LINKAGE
/// \brief Specifies if symbols are exported for static or dynamic linkage.
///
#ifdef DOXYGEN
  #define GALA_LINKAGE GALA_LINKAGE_STATIC
#else // #ifndef DOXYGEN
  #ifdef GALA_LINKAGE
    #if (GALA_LINKAGE != GALA_LINKAGE_STATIC) && \
        (GALA_LINKAGE != GALA_LINKAGE_DYNAMIC)
      #error ("Invalid or unknown linkage specified.")
    #else
    #endif
  #else // ifndef GALA_LINKAGE
    #error ("Linkage not specified.")
  #endif
#endif

//============================================================================//

#endif // _GALA_CONFIG_LINKAGE_INL_

//============================================================================//
