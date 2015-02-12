//===-- gala/adapter_d3d9_win32.h -------------------------------*- C++ -*-===//
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

#ifndef _GALA_ADAPTER_D3D9_WIN32_H_
#define _GALA_ADAPTER_D3D9_WIN32_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"
#include "gala/error.h"
#include "gala/adapter.h"

//===----------------------------------------------------------------------===//

#include "output_d3d9_win32.h"

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
typedef struct gala_adapter_d3d9 {
  /// \copydoc ::gala_adapter_t
  gala_adapter_t __adapter__;
  /// TODO(mike): Document this.
  UINT uiAdapter;
  /// TODO(mike): Document this.
  D3DADAPTER_IDENTIFIER9 Identifier;
} gala_adapter_d3d9_t;

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#endif // _GALA_ADAPTER_D3D9_WIN32_H_

//============================================================================//
