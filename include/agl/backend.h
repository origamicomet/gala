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
/// \brief Abstract Graphics Library.
///
//===----------------------------------------------------------------------===//

#ifndef _AGL_BACKEND_H_
#define _AGL_BACKEND_H_

//============================================================================//

#include "agl/linkage.h"
#include "agl/types.h"
#include "agl/error.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef enum agl_backend {
  /// Direct3D 9
  AGL_BACKEND_D3D9 = 1,
  /// Direct3D 11
  AGL_BACKEND_D3D11 = 2,
  /// OpenGL 2.1
  AGL_BACKEND_GL21 = 3,
  /// OpenGL 3.1
  AGL_BACKEND_GL31 = 4,
  /// OpenGL ES 2
  AGL_BACKEND_GLES2 = 5,
  /// OpenGL ES 3
  AGL_BACKEND_GLES3 = 6
} agl_backend_t;

//===----------------------------------------------------------------------===//

/// \brief
///
extern
AGL_EXPORT
agl_bool_t
agl_backend_available(
  const agl_backend_t backend);

//===----------------------------------------------------------------------===//

/// \brief
///
extern
AGL_EXPORT
agl_error_t
agl_backend_initialize(
  const agl_backend_t backend,
  agl_error_details_t **error_details);

//===----------------------------------------------------------------------===//

/// \brief
///
extern
AGL_EXPORT
agl_error_t
agl_backend_shutdown(
  const agl_backend_t backend,
  agl_error_details_t **error_details);

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#endif // _AGL_BACKEND_H_

//============================================================================//
