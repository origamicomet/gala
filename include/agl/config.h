//===-- agl/config.h --------------------------------------------*- C++ -*-===//
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
/// \brief Documents and defines the pre-processor macros that control AGL's
/// compile-time, link-time, and runtime behaviour.
///
//===----------------------------------------------------------------------===//

#ifndef _AGL_CONFIG_H_
#define _AGL_CONFIG_H_

//============================================================================//

/// \def AGL_CONFIGURATION_DEBUG
/// \brief Self explanatory.
///
#define AGL_CONFIGURATION_DEBUG 1

/// \def AGL_CONFIGURATION_DEVELOPMENT
/// \brief Self explanatory.
///
#define AGL_CONFIGURATION_DEVELOPMENT 2

/// \def AGL_CONFIGURATION_RELEASE
/// \brief Self explanatory.
///
#define AGL_CONFIGURATION_RELEASE 3

/// \def AGL_CONFIGURATION
/// \brief Self explanatory.
///
#ifdef DOXYGEN
  #define AGL_CONFIGURATION
#else // #ifndef DOXYGEN
  #ifdef AGL_CONFIGURATION
    #if (AGL_CONFIGURATION != AGL_CONFIGURATION_DEBUG) && \
        (AGL_CONFIGURATION != AGL_CONFIGURATION_DEVELOPMENT) && \
        (AGL_CONFIGURATION != AGL_CONFIGURATION_RELEASE)
      #error ("Invalid or unknown configuration specified.")
    #else
    #endif
  #else // ifndef AGL_CONFIGURATION
    #error ("Configuration not specified.")
  #endif
#endif

//===----------------------------------------------------------------------===//

#include <agl/config/linkage.inl>
#include <agl/config/visibility.inl>

//===----------------------------------------------------------------------===//

#include <agl/config/argument_and_error_checking.inl>

//============================================================================//

#endif // _AGL_CONFIG_H_

//============================================================================//
