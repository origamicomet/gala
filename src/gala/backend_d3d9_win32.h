//===-- gala/backend_d3d9_win32.h -------------------------------*- C++ -*-===//
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

#ifndef _GALA_BACKEND_D3D9_WIN32_H_
#define _GALA_BACKEND_D3D9_WIN32_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"
#include "gala/error.h"
#include "gala/backend.h"

//===----------------------------------------------------------------------===//

#include "gala/adapter_d3d9_win32.h"

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
typedef struct gala_backend_d3d9 {
  /// \copydoc ::gala_backend_t
  gala_backend_t __backend__;
  ///
  HMODULE hDll;
  ///
  IDirect3D9 *D3D9;
} gala_backend_d3d9_t;

//===----------------------------------------------------------------------===//

extern
gala_error_t gala_backend_initialize_d3d9(
  gala_backend_t **backend,
  const gala_error_details_t **error_details);

//===----------------------------------------------------------------------===//

extern
gala_error_t gala_backend_shutdown_d3d9(
  gala_backend_t *backend,
  const gala_error_details_t **error_details);

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#endif // _GALA_BACKEND_D3D9_WIN32_H_

//============================================================================//
