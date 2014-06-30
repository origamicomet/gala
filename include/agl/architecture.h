//===-- agl/architecture.h --------------------------------------*- C++ -*-===//
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
/// \brief Defines various architectures and detects the target architecture
/// based on pre-processor definitions.
///
//===----------------------------------------------------------------------===//

#ifndef _AGL_ARCHITECTURE_H_
#define _AGL_ARCHITECTURE_H_

//============================================================================//

/// \def AGL_ARCHITECTURE_UNKNOWN
/// \brief Unknown or unsupported architecture.
///
#define AGL_ARCHITECTURE_UNKNOWN 0

/// \def AGL_ARCHITECTURE_X86
/// \brief Intel/AMD x86.
///
#define AGL_ARCHITECTURE_X86 1

/// \def AGL_ARCHITECTURE_X86_64
/// \brief Intel/AMD x86-64.
///
#define AGL_ARCHITECTURE_X86_64 2

//===----------------------------------------------------------------------===//

/// \def AGL_ARCHITECTURE
/// \brief The architecture AGL is built for.
///
#if defined(_M_IX86) || defined(__i386__)
  #define AGL_ARCHITECTURE AGL_ARCHITECTURE_X86
#elif defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || defined(__amd64__)
  #define AGL_ARCHITECTURE AGL_ARCHITECTURE_X86_64
#else
  #error ("You are building AGL for an unknown or unsupported architecture.")
#endif

//============================================================================//

#endif // _AGL_ARCHITECTURE_H_

//============================================================================//
