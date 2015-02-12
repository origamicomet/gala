//===-- gala/pixel_format_d3d9_win32.h --------------------------*- C++ -*-===//
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
/// \brief TODO(mike): Document this file.
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_PIXEL_FORMAT_D3D9_WIN32_H_
#define _GALA_PIXEL_FORMAT_D3D9_WIN32_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"
#include "gala/pixel_format.h"

//===----------------------------------------------------------------------===//

#define _WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d9.h>

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

extern
D3DFORMAT gala_pixel_format_to_d3d9(
  const gala_pixel_format_t gala);

//===----------------------------------------------------------------------===//

extern
gala_pixel_format_t gala_pixel_format_from_d3d9(
  const D3DFORMAT d3d);

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#endif // _GALA_PIXEL_FORMAT_D3D9_WIN32_H_

//============================================================================//
