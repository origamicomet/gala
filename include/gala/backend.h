//===-- gala/backend.h ------------------------------------------*- C++ -*-===//
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
/// \brief
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_BACKEND_H_
#define _GALA_BACKEND_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef enum gala_backend {
  /// Direct3D 9
  GALA_BACKEND_D3D9  = 1,
  /// Direct3D 10
  GALA_BACKEND_D3D10 = 2,
  /// Direct3D 11
  GALA_BACKEND_D3D11 = 3,
  /// Direct3D 12
  GALA_BACKEND_D3D12 = 4,
  /// OpenGL 2+
  GALA_BACKEND_GL2   = 5,
  /// OpenGL 3+
  GALA_BACKEND_GL3   = 6,
  /// OpenGL 4+
  GALA_BACKEND_GL4   = 7,
  /// OpenGL ES
  GALA_BACKEND_GLES  = 8,
  /// OpenGL ES 2
  GALA_BACKEND_GLES2 = 9,
  /// OpenGL ES 3
  GALA_BACKEND_GLES3 = 10
} gala_backend_t;

//===----------------------------------------------------------------------===//

/// \brief
/// \param backend
///
extern
GALA_PUBLIC
bool gala_backend_available(
  const gala_backend_t backend);

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//===----------------------------------------------------------------------===//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace gala {

//===----------------------------------------------------------------------===//

namespace backends {
typedef enum __Enum__ {
  /// \copydoc ::GALA_BACKEND_D3D9
  D3D9  = ::GALA_BACKEND_D3D9,
  /// \copydoc ::GALA_BACKEND_D3D10
  D3D10 = ::GALA_BACKEND_D3D10,
  /// \copydoc ::GALA_BACKEND_D3D11
  D3D11 = ::GALA_BACKEND_D3D11,
  /// \copydoc ::GALA_BACKEND_D3D12
  D3D12 = ::GALA_BACKEND_D3D12,
  /// \copydoc ::GALA_BACKEND_GL2
  GL2   = ::GALA_BACKEND_GL2,
  /// \copydoc ::GALA_BACKEND_GL3
  GL3   = ::GALA_BACKEND_GL3,
  /// \copydoc ::GALA_BACKEND_GL4
  GL4   = ::GALA_BACKEND_GL4,
  /// \copydoc ::GALA_BACKEND_GLES
  GLES  = ::GALA_BACKEND_GLES,
  /// \copydoc ::GALA_BACKEND_GLES2
  GLES2 = ::GALA_BACKEND_GLES2,
  /// \copydoc ::GALA_BACKEND_GLES3
  GLES3 = ::GALA_BACKEND_GLES3
} __Enum__;
} // backends

//===----------------------------------------------------------------------===//

namespace backend {

/// \copydoc ::gala_backend_available
extern
GALA_PUBLIC
bool available(
  const gala::backends::__Enum__ backend);

} // backend

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_BACKEND_H_

//============================================================================//
