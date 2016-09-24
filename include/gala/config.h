//===-- gala/config.h -----------------------------------*- mode: C++11 -*-===//
//
//                             _____     _
//                            |   __|___| |___
//                            |  |  | .'| | .'|
//                            |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Defines and checks the sanity of various pre-processor macros that
/// control the building and behaviour of Gala.
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_CONFIG_H_
#define _GALA_CONFIG_H_

/// \def GALA_CONFIGURATION_DEBUG
/// \brief Debug build.
#define GALA_CONFIGURATION_DEBUG 1

/// \def GALA_CONFIGURATION_DEVELOPMENT
/// \brief Development build.
#define GALA_CONFIGURATION_DEVELOPMENT 2

/// \def GALA_CONFIGURATION_RELEASE
/// \brief Release build.
#define GALA_CONFIGURATION_RELEASE 3

/// \def GALA_CONFIGURATION
/// \brief Specifies how "loose and fast" Gala is.
#if defined(DOXYGEN)
  #define GALA_CONFIGURATION
#else
  #if !defined(GALA_CONFIGURATION)
    #error ("No configuration specified! Please specify a configuration by defining `GALA_CONFIGURATION'.")
  #else
    #if (GALA_CONFIGURATION != GALA_CONFIGURATION_DEBUG) && \
        (GALA_CONFIGURATION != GALA_CONFIGURATION_DEVELOPMENT) && \
        (GALA_CONFIGURATION != GALA_CONFIGURATION_RELEASE)
      #error ("Unknown configuration specified. See include/gala/config.h for a list of possible configurations.")
    #endif
  #endif
#endif

/// \def GALA_PLATFORM_WINDOWS
/// \brief Microsoft Windows.
#define GALA_PLATFORM_WINDOWS 1

/// \def GALA_PLATFORM_MAC_OS_X
/// \brief Apple's Mac OS X.
#define GALA_PLATFORM_MAC_OS_X 2

/// \def GALA_PLATFORM_LINUX
/// \brief GNU/Linux.
#define GALA_PLATFORM_LINUX 3

/// \def GALA_PLATFORM_IOS
/// \brief Apple's iOS.
#define GALA_PLATFORM_IOS 4

/// \def GALA_PLATFORM_ANDROID
/// \brief Google's Android.
#define GALA_PLATFORM_ANDROID 5

/// \def GALA_PLATFORM
/// \brief Target platform.
#if defined(DOXYGEN)
  #define GALA_PLATFORM
#else // !defined(DOXYGEN)
  #if defined(_WIN32) || defined(_WIN64)
    #define GALA_PLATFORM GALA_PLATFORM_WINDOWS
  #elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #if defined(TARGET_OS_IPHONE)
      #define GALA_PLATFORM GALA_PLATFORM_IOS
    #else
      #define GALA_PLATFORM GALA_PLATFORM_MAC_OS_X
    #endif
  #elif defined(__linux__)
    #if defined(ANDROID)
      #define GALA_PLATFORM GALA_PLATFORM_ANDROID
    #else
      #define GALA_PLATFORM GALA_PLATFORM_LINUX
    #endif
  #else
    #error ("Unknown or unsupported platform!")
  #endif
#endif

/// \def GALA_COMPILER_MSVC
/// \brief Microsoft Visual C/C++.
#define GALA_COMPILER_MSVC 1

/// \def GALA_COMPILER_GCC
/// \brief GNU Compiler Collection.
#define GALA_COMPILER_GCC 2

/// \def GALA_COMPILER_CLANG
/// \brief LLVM/Clang.
#define GALA_COMPILER_CLANG 3

/// \def GALA_COMPILER
/// \brief Host compiler.
#if defined(DOXYGEN)
  #define GALA_COMPILER
#else // !defined(DOXYGEN)
  #if defined(_MSC_VER)
    #define GALA_COMPILER GALA_COMPILER_MSVC
    #define GALA_MICROSOFT_VISUAL_STUDIO_2013 1800
    #define GALA_MICROSOFT_VISUAL_STUDIO_2012 1700
    #define GALA_MICROSOFT_VISUAL_STUDIO_2010 1600
    #define GALA_MICROSOFT_VISUAL_STUDIO_2008 1500
    #define GALA_MICROSOFT_VISUAL_STUDIO_2005 1400
    #define GALA_MICROSOFT_VISUAL_STUDIO_2003 1310
    #define GALA_MICROSOFT_VISUAL_STUDIO_2002 1300
    #define GALA_MICROSOFT_VISUAL_C_6 1200
    #if (_MSC_VER >= MICROSOFT_VISUAL_STUDIO_2005)
      // ASSUME(mtwilliams): Microsoft Visual Studio 2005 or newer.
    #elif (_MSC_VER == MICROSOFT_VISUAL_STUDIO_2003)
      #error ("Microsoft Visual C/C++ .NET 2003 is unsupported! Please upgrade to Microsoft Visual C/C++ 2005 or newer.")
    #elif (_MSC_VER == MICROSOFT_VISUAL_STUDIO_2002)
      #error ("Microsoft Visual C/C++ .NET 2002 is unsupported! Please upgrade to Microsoft Visual C/C++ 2005 or newer.")
      // Not to mention that it has major bugs so annoying that Microsoft provides
      // complementary upgrades to Microsoft Visual C/C++ .NET 2003!
    #elif (_MSC_VER == GALA_MICROSOFT_VISUAL_C_6)
      #error ("Microsoft Visual C/C++ 6 is unsupported! Please upgrade to Microsoft Visual C/C++ 2005 or newer.")
      // If we did ever want to support it, we should check for Service Pack 6 by
      // checking if _MSC_FULL_VER is less than 12008804.
    #else
      #error ("Your version of Microsoft Visual C/C++ is unsupported! Please upgrade to Microsoft Visual C/C++ 2005 or newer.")
    #endif
  #elif defined(__GNUC__)
    #if defined(__clang__)
      #define GALA_COMPILER GALA_COMPILER_CLANG
      #define __CLANG_VERSION__ (__clang_major__ * 10000 \
                                 + __clang_minor__ * 100 \
                                 + __clang_patchlevel__)
    #else // !defined(__clang__)
      // ASSUME(mtwilliams): That we're being compiled with GCC.
      #define GALA_COMPILER GALA_COMPILER_GCC
      #if defined(__GNUC_PATCHLEVEL__)
        #define __GNUC_VERSION__ (__GNUC__ * 10000 \
                                  + __GNUC_MINOR__ * 100 \
                                  + __GNUC_PATCHLEVEL__)
      #else
        #define __GNUC_VERSION__ (__GNUC__ * 10000 \
                                  + __GNUC_MINOR__ * 100)
      #endif
    #endif
  #else
    #error ("Unknown or unsupported compiler!")
  #endif
#endif

/// \def GALA_ARCHITECTURE_X86
/// \brief Intel/AMD x86.
#define GALA_ARCHITECTURE_X86 1

/// \def GALA_ARCHITECTURE_X86_64
/// \brief Intel/AMD x86-64.
#define GALA_ARCHITECTURE_X86_64 2

/// \def GALA_ARCHITECTURE
/// \brief Target architecture.
#if defined(DOXYGEN)
  #define GALA_COMPILER
#else // !defined(DOXYGEN)
  #if defined(_M_IX86) || defined(__i386__)
    #define GALA_ARCHITECTURE GALA_ARCHITECTURE_X86
  #elif defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || defined(__amd64__)
    #define GALA_ARCHITECTURE GALA_ARCHITECTURE_X86_64
  #else
    #error ("Unknown or unsupported architecture!")
  #endif
#endif

/// \def GALA_DISABLE_ARGUMENT_CHECKS
/// \brief Gala won't check supplied arguments if defined.
///
#if defined(DOXYGEN)
  #define GALA_DISABLE_ARGUMENT_CHECKS
#else // !defined(DOXYGEN)
  #if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
  #elif GALA_CONFIGURATION == GALA_CONFIGURATION_DEVELOPMENT
    #define GALA_DISABLE_ARGUMENT_CHECKS
  #elif GALA_CONFIGURATION == GALA_CONFIGURATION_RELEASE
    #define GALA_DISABLE_ARGUMENT_CHECKS
  #endif
#endif

/// \def GALA_DISABLE_ERROR_CHECKS
/// \brief Gala won't check for errors if defined.
///
#if defined(DOXYGEN)
  #define GALA_DISABLE_ERROR_CHECKS
#else // !defined(DOXYGEN)
  #if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
  #elif GALA_CONFIGURATION == GALA_CONFIGURATION_DEVELOPMENT
  #elif GALA_CONFIGURATION == GALA_CONFIGURATION_RELEASE
    #define GALA_DISABLE_ERROR_CHECKS
  #endif
#endif

/// \def GALA_DISABLE_ERROR_DETAILS
/// \brief Gala won't provide error details if defined.
///
#if defined(DOXYGEN)
  #define GALA_DISABLE_ERROR_DETAILS
#else // !defined(DOXYGEN)
  #if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
  #elif GALA_CONFIGURATION == GALA_CONFIGURATION_DEVELOPMENT
  #elif GALA_CONFIGURATION == GALA_CONFIGURATION_RELEASE
    #define GALA_DISABLE_ERROR_DETAILS
  #endif
#endif

#endif // _GALA_CONFIG_H_
