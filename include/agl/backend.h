//===-- agl/backend.h -------------------------------------------*- C++ -*-===//
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
/// \brief TODO
///
//===----------------------------------------------------------------------===//

#ifndef _AGL_BACKEND_H_
#define _AGL_BACKEND_H_

//============================================================================//

#include <agl/config.h>
#include <agl/compat.h>
#include <agl/types.h>

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef enum agl_backend {
  /// Direct3D 9
  AGL_BACKEND_D3D9  = 1,
  /// Direct3D 10
  AGL_BACKEND_D3D10 = 2,
  /// Direct3D 11
  AGL_BACKEND_D3D11 = 3,
  /// Direct3D 12
  AGL_BACKEND_D3D12 = 4,
  /// OpenGL 2+
  AGL_BACKEND_GL2   = 5,
  /// OpenGL 3+
  AGL_BACKEND_GL3   = 6,
  /// OpenGL 4+
  AGL_BACKEND_GL4   = 7,
  /// OpenGL ES
  AGL_BACKEND_GLES  = 8,
  /// OpenGL ES 2
  AGL_BACKEND_GLES2 = 9,
  /// OpenGL ES 3
  AGL_BACKEND_GLES3 = 10
} agl_backend_t;

//===----------------------------------------------------------------------===//

/// \brief
/// \param
///
extern
AGL_PUBLIC
agl_bool_t agl_backend_available(
  const agl_backend_t backend);

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//===----------------------------------------------------------------------===//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace agl {

//===----------------------------------------------------------------------===//

namespace Backends {
typedef enum __Enum__ {
  /// \copydoc ::AGL_BACKEND_D3D9
  D3D9  = ::AGL_BACKEND_D3D9,
  /// \copydoc ::AGL_BACKEND_D3D10
  D3D10 = ::AGL_BACKEND_D3D10,
  /// \copydoc ::AGL_BACKEND_D3D11
  D3D11 = ::AGL_BACKEND_D3D11,
  /// \copydoc ::AGL_BACKEND_D3D12
  D3D12 = ::AGL_BACKEND_D3D12,
  /// \copydoc ::AGL_BACKEND_GL2
  GL2   = ::AGL_BACKEND_GL2,
  /// \copydoc ::AGL_BACKEND_GL3
  GL3   = ::AGL_BACKEND_GL3,
  /// \copydoc ::AGL_BACKEND_GL4
  GL4   = ::AGL_BACKEND_GL4,
  /// \copydoc ::AGL_BACKEND_GLES
  GLES  = ::AGL_BACKEND_GLES,
  /// \copydoc ::AGL_BACKEND_GLES2
  GLES2 = ::AGL_BACKEND_GLES2,
  /// \copydoc ::AGL_BACKEND_GLES3
  GLES3 = ::AGL_BACKEND_GLES3
} __Enum__;
} // Backends

//===----------------------------------------------------------------------===//

namespace Backend {

/// \copydoc ::agl_backend_available
extern
AGL_PUBLIC
agl_bool_t available(
  const agl::Backends::__Enum__ backend);

} // Backend

//===----------------------------------------------------------------------===//

} // agl

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _AGL_BACKEND_H_

//============================================================================//
