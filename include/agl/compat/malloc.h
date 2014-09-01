//===-- agl/compat/malloc.h -------------------------------------*- C++ -*-===//
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
/// \brief Enforces the existence of alloca in malloc.h.
///
//===----------------------------------------------------------------------===//

#ifndef _AGL_COMPAT_MALLOC_H_
#define _AGL_COMPAT_MALLOC_H_

//============================================================================//

#if defined(__APPLE__) || defined(__linux__)
  #include <malloc.h>
  #include <alloca.h>
#elif defined(__GNUC__) || defined(__clang__)
  #include <malloc.h>
#elif defined(_MSC_VER)
  #include <malloc.h>
  #define alloca _alloca
#endif

//============================================================================//

#endif // _AGL_COMPAT_MALLOC_H_

//============================================================================//
