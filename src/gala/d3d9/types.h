//===-- gala/d3d9/types.h ---------------------------------------*- C++ -*-===//
//
//  Gala
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//   * Michael Williams <mike@origamicomet.com>
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_D3D9_TYPES_H_
#define _GALA_D3D9_TYPES_H_

//============================================================================//

#include "gala/backend.h"

//===----------------------------------------------------------------------===//

#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  #define WIN32_LEAN_AND_MEAN
  #define WIN32_EXTRA_LEAN

  #include <windows.h>
  #include <d3d9.h>

  #undef WIN32_EXTRA_LEAN
  #undef WIN32_LEAN_AND_MEAN

  #undef NEAR
  #undef FAR
  #undef near
  #undef far
  #undef NO_ERROR
  #undef ERROR
  #undef MK_SHIFT
  #undef MK_ALT
  #undef min
  #undef max
  #undef rad1
#else
  #error ("Direct3D 9 is unavailable or unsupported on this platform!")
#endif

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

struct gala_d3d9_backend {
  gala_backend_t __backend__;
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  HMODULE dll;
  IDirect3D9 *d3d9;
#endif
};

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#endif // _GALA_D3D9_TYPES_H_

//============================================================================//
