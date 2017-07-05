//===-- gala/backend.h ----------------------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//
//
// TODO(mtwilliams): Document the purpose of this file.
//
//===----------------------------------------------------------------------===//

#ifndef _GALA_BACKEND_H_
#define _GALA_BACKEND_H_

#include "gala/foundation.h"

GALA_BEGIN_EXTERN_C

/// \brief
typedef enum gala_backend {
  /// Invalid.
  GALA_BACKEND_INVALID = 0,

  /// Null.
  GALA_BACKEND_NULL = 1,

  /// Reference.
  GALA_BACKEND_REF = 2,

  /// Direct3D 9
  GALA_BACKEND_D3D9 = 10,

  /// Direct3D 11
  GALA_BACKEND_D3D11 = 11,

  /// Direct3D 12
  GALA_BACKEND_D3D12 = 12,

  /// OpenGL 3
  GALA_BACKEND_OPENGL = 20,

  /// OpenGL ES 2
  GALA_BACKEND_GLES2 = 30,

  /// OpenGL ES 3
  GALA_BACKEND_GLES3 = 31,

  /// \internal Force gala_uint32_t storage and alignment.
  GALA_BACKEND_FORCE_UINT32 = 0x7fffffff
} gala_backend_t;

GALA_END_EXTERN_C

#endif // _GALA_BACKEND_H_
