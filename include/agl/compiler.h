//===-- agl/compiler.h ------------------------------------------*- C++ -*-===//
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
/// \brief Defines various compilers and detects the host compiler based on
/// pre-processor definitions.
///
//===----------------------------------------------------------------------===//

#ifndef _AGL_COMPILER_H_
#define _AGL_COMPILER_H_

//============================================================================//

/// \def AGL_COMPILER_UNKNOWN
/// \brief Unknown or unsupported compiler.
///
#define AGL_COMPILER_UNKNOWN 0

/// \def AGL_COMPILER_MSVC
/// \brief Microsoft Visual C/C++ Compiler.
///
#define AGL_COMPILER_MSVC 1

/// \def AGL_COMPILER_GCC
/// \brief GNU Compiler Collection.
///
#define AGL_COMPILER_GCC 2

/// \def AGL_COMPILER_CLANG
/// \brief LLVM/Clang.
///
#define AGL_COMPILER_CLANG 3

//===----------------------------------------------------------------------===//

/// \def AGL_COMPILER
/// \brief The compiler AGL is built for.
///
#if defined(_MSC_VER)
  #define AGL_COMPILER AGL_COMPILER_MSVC
#elif defined(__GNUC__)
  #define AGL_COMPILER AGL_COMPILER_GCC
#elif defined(__clang__)
  #define AGL_COMPILER AGL_COMPILER_CLANG
#else
  #error ("You are building AGL with an unknown or unsupported compiler.")
#endif

//============================================================================//

#endif // _AGL_COMPILER_H_

//============================================================================//
