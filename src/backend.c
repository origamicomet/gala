//===-- agl/backend.c -------------------------------------------*- C++ -*-===//
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

#include <agl/backend.h>

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

agl_bool_t agl_backend_available(
  const agl_backend_t backend)
{
  switch (backend) {
    case AGL_BACKEND_D3D9:
      return AGL_FALSE;
    case AGL_BACKEND_D3D10:
      return AGL_FALSE;
    case AGL_BACKEND_D3D11:
      return AGL_FALSE;
    case AGL_BACKEND_D3D12:
      return AGL_FALSE;
    case AGL_BACKEND_GL2:
      return AGL_FALSE;
    case AGL_BACKEND_GL3:
      return AGL_FALSE;
    case AGL_BACKEND_GL4:
      return AGL_FALSE;
    case AGL_BACKEND_GLES:
      return AGL_FALSE;
    case AGL_BACKEND_GLES2:
      return AGL_FALSE;
    case AGL_BACKEND_GLES3:
      return AGL_FALSE;
    default:
      break;
  }

  return AGL_FALSE;
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace agl {

//===----------------------------------------------------------------------===//

namespace Backend {

agl_bool_t available(
  const agl::Backends::__Enum__ backend)
{
  return !!(::agl_backend_available((::agl_backend_t)backend));
}

} // Backend

//===----------------------------------------------------------------------===//

} // agl

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
