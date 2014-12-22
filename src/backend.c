//===-- gala/backend.c ------------------------------------------*- C++ -*-===//
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

#include <gala/backend.h>

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

gala_bool_t gala_backend_available(
  const gala_backend_t backend)
{
  switch (backend) {
    case GALA_BACKEND_D3D9:
      return GALA_FALSE;
    case GALA_BACKEND_D3D10:
      return GALA_FALSE;
    case GALA_BACKEND_D3D11:
      return GALA_FALSE;
    case GALA_BACKEND_D3D12:
      return GALA_FALSE;
    case GALA_BACKEND_GL2:
      return GALA_FALSE;
    case GALA_BACKEND_GL3:
      return GALA_FALSE;
    case GALA_BACKEND_GL4:
      return GALA_FALSE;
    case GALA_BACKEND_GLES:
      return GALA_FALSE;
    case GALA_BACKEND_GLES2:
      return GALA_FALSE;
    case GALA_BACKEND_GLES3:
      return GALA_FALSE;
    default:
      break;
  }

  return GALA_FALSE;
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace gala {

//===----------------------------------------------------------------------===//

namespace Backend {

gala_bool_t available(
  const gala::Backends::__Enum__ backend)
{
  return !!(::gala_backend_available((::gala_backend_t)backend));
}

} // Backend

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
