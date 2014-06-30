//===-- agl/system.h --------------------------------------------*- C++ -*-===//
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
/// \brief Defines various systems and detects the target system based on
/// pre-processor definitions.
///
//===----------------------------------------------------------------------===//

#ifndef _AGL_SYSTEM_H_
#define _AGL_SYSTEM_H_

//============================================================================//

/// \def AGL_SYSTEM_UNKNOWN
/// \brief Unknown or unsupported system.
///
#define AGL_SYSTEM_UNKNOWN 0

/// \def AGL_SYSTEM_WINDOWS
/// \brief Microsoft Windows.
///
#define AGL_SYSTEM_WINDOWS 1

/// \def AGL_SYSTEM_MAC_OS_X
/// \brief Mac OS X.
///
#define AGL_SYSTEM_MAC_OS_X 2

/// \def AGL_SYSTEM_LINUX
/// \brief Linux.
///
#define AGL_SYSTEM_LINUX 3

/// \def AGL_SYSTEM_ANDROID
/// \brief Android.
///
#define AGL_SYSTEM_ANDROID 4

/// \def AGL_SYSTEM_IOS
/// \brief iOS.
///
#define AGL_SYSTEM_IOS 5

//===----------------------------------------------------------------------===//

/// \def AGL_SYSTEM
/// \brief The system AGL is built for.
///
#if (defined(_WIN32) || defined(_WIN64))
  #define AGL_SYSTEM AGL_SYSTEM_WINDOWS
#elif defined(__APPLE__)
  #include <TargetConditionals.h>
  #if defined(TARGET_OS_IPHONE)
    #define AGL_SYSTEM AGL_SYSTEM_IOS
  #else
    #define AGL_SYSTEM AGL_SYSTEM_MAC_OS_X
  #endif
#elif defined(__linux__)
  #if defined(ANDROID)
    #define AGL_SYSTEM AGL_SYSTEM_ANDROID
  #else
    #define AGL_SYSTEM AGL_SYSTEM_LINUX
  #endif
#else
  #error ("You are building AGL for an unknown or unsupported system.")
#endif

//============================================================================//

#endif // _AGL_SYSTEM_H_

//============================================================================//
