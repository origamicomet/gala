//===-- gala/output_d3d9_win32.h --------------------------------*- C++ -*-===//
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

#ifndef _GALA_OUTPUT_D3D9_WIN32_H_
#define _GALA_OUTPUT_D3D9_WIN32_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"
#include "gala/error.h"
#include "gala/output.h"

//===----------------------------------------------------------------------===//

#define _WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d9.h>

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_output_d3d9 {
  /// \copydoc ::gala_output_t
  gala_output_t __output__;
  /// TODO(mike): Document this.
  HMONITOR hMonitor;
  /// TODO(mike): Document this.
  struct {
    UINT uiA8R8G8B8;
    UINT uiX8R8G8B8;
  } ModeCount;
} gala_output_d3d9_t;

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#endif // _GALA_OUTPUT_D3D9_WIN32_H_

//============================================================================//
