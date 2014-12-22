//===-- gala/config.h -------------------------------------------*- C++ -*-===//
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
/// \brief Documents and defines the pre-processor macros that control Gala's
/// compile-time, link-time, and runtime behaviour.
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_CONFIG_H_
#define _GALA_CONFIG_H_

//============================================================================//

/// \def GALA_CONFIGURATION_DEBUG
/// \brief Self explanatory.
///
#define GALA_CONFIGURATION_DEBUG 1

/// \def GALA_CONFIGURATION_DEVELOPMENT
/// \brief Self explanatory.
///
#define GALA_CONFIGURATION_DEVELOPMENT 2

/// \def GALA_CONFIGURATION_RELEASE
/// \brief Self explanatory.
///
#define GALA_CONFIGURATION_RELEASE 3

/// \def GALA_CONFIGURATION
/// \brief Self explanatory.
///
#ifdef DOXYGEN
  #define GALA_CONFIGURATION
#else // #ifndef DOXYGEN
  #ifdef GALA_CONFIGURATION
    #if (GALA_CONFIGURATION != GALA_CONFIGURATION_DEBUG) && \
        (GALA_CONFIGURATION != GALA_CONFIGURATION_DEVELOPMENT) && \
        (GALA_CONFIGURATION != GALA_CONFIGURATION_RELEASE)
      #error ("Invalid or unknown configuration specified.")
    #else
    #endif
  #else // ifndef GALA_CONFIGURATION
    #error ("Configuration not specified.")
  #endif
#endif

//===----------------------------------------------------------------------===//

/// \def GALA_DISABLE_ARGUMENT_CHECKS
/// \brief If defined, Gala won't check supplied arguments.
///
#ifdef DOXYGEN
  #define GALA_DISABLE_ARGUMENT_CHECKS
#else // #ifndef DOXYGEN
  #if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
  #elif GALA_CONFIGURATION == GALA_CONFIGURATION_DEVELOPMENT
  #elif GALA_CONFIGURATION == GALA_CONFIGURATION_RELEASE
    #define GALA_DISABLE_ARGUMENT_CHECKS
  #else // #ifndef GALA_CONFIGURATION
  #endif
#endif

/// \def GALA_DISABLE_ERROR_CHECKS
/// \brief If defined, Gala won't check for errors.
///
#ifdef DOXYGEN
  #define GALA_DISABLE_ERROR_CHECKS
#else // #ifndef DOXYGEN
  #if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
  #elif GALA_CONFIGURATION == GALA_CONFIGURATION_DEVELOPMENT
  #elif GALA_CONFIGURATION == GALA_CONFIGURATION_RELEASE
    #define GALA_DISABLE_ERROR_CHECKS
  #else // #ifndef GALA_CONFIGURATION
  #endif
#endif

/// \def GALA_DISABLE_ERROR_DETAILS
/// \brief If defined, Gala won't provide error details.
///
#ifdef DOXYGEN
  #define GALA_DISABLE_ERROR_DETAILS
#else // #ifndef DOXYGEN
  #if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
  #elif GALA_CONFIGURATION == GALA_CONFIGURATION_DEVELOPMENT
  #elif GALA_CONFIGURATION == GALA_CONFIGURATION_RELEASE
    #define GALA_DISABLE_ERROR_DETAILS
  #else // #ifndef GALA_CONFIGURATION
  #endif
#endif

//============================================================================//

#endif // _GALA_CONFIG_H_

//============================================================================//
