//===-- gala/config/argument_and_error_checking.h ---------------*- C++ -*-===//
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
/// \brief Documents and defines the pre-processor macros that control argument
/// and error checking.
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_CONFIG_ARGUMENT_AND_ERROR_CHECKING_INL_
#define _GALA_CONFIG_ARGUMENT_AND_ERROR_CHECKING_INL_

//============================================================================//

/// \def GALA_DISABLE_ARGUMENT_CHECKS
/// \brief If defined GALA won't check supplied arguments.
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
/// \brief If defined GALA won't check for errors.
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
/// \brief If defined GALA won't detail errors.
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

#endif // _GALA_CONFIG_ARGUMENT_AND_ERROR_CHECKING_INL_

//============================================================================//
