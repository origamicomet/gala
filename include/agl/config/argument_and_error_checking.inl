//===-- agl/config/argument_and_error_checking.h ----------------*- C++ -*-===//
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
/// \brief Documents and defines the pre-processor macros that control argument
/// and error checking.
///
//===----------------------------------------------------------------------===//

#ifndef _AGL_CONFIG_ARGUMENT_AND_ERROR_CHECKING_INL_
#define _AGL_CONFIG_ARGUMENT_AND_ERROR_CHECKING_INL_

//============================================================================//

/// \def AGL_DISABLE_ARGUMENT_CHECKS
/// \brief If defined AGL won't check supplied arguments.
///
#ifdef DOXYGEN
  #define AGL_DISABLE_ARGUMENT_CHECKS
#else // #ifndef DOXYGEN
  #if AGL_CONFIGURATION == AGL_CONFIGURATION_DEBUG
  #elif AGL_CONFIGURATION == AGL_CONFIGURATION_DEVELOPMENT
  #elif AGL_CONFIGURATION == AGL_CONFIGURATION_RELEASE
    #define AGL_DISABLE_ARGUMENT_CHECKS
  #else // #ifndef AGL_CONFIGURATION
  #endif
#endif

/// \def AGL_DISABLE_ERROR_CHECKS
/// \brief If defined AGL won't check for errors.
///
#ifdef DOXYGEN
  #define AGL_DISABLE_ERROR_CHECKS
#else // #ifndef DOXYGEN
  #if AGL_CONFIGURATION == AGL_CONFIGURATION_DEBUG
  #elif AGL_CONFIGURATION == AGL_CONFIGURATION_DEVELOPMENT
  #elif AGL_CONFIGURATION == AGL_CONFIGURATION_RELEASE
    #define AGL_DISABLE_ERROR_CHECKS
  #else // #ifndef AGL_CONFIGURATION
  #endif
#endif

/// \def AGL_DISABLE_ERROR_DETAILS
/// \brief If defined AGL won't detail errors.
///
#ifdef DOXYGEN
  #define AGL_DISABLE_ERROR_DETAILS
#else // #ifndef DOXYGEN
  #if AGL_CONFIGURATION == AGL_CONFIGURATION_DEBUG
  #elif AGL_CONFIGURATION == AGL_CONFIGURATION_DEVELOPMENT
  #elif AGL_CONFIGURATION == AGL_CONFIGURATION_RELEASE
    #define AGL_DISABLE_ERROR_DETAILS
  #else // #ifndef AGL_CONFIGURATION
  #endif
#endif

//============================================================================//

#endif // _AGL_CONFIG_ARGUMENT_AND_ERROR_CHECKING_INL_

//============================================================================//
