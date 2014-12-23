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

#include "gala/backend.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

bool gala_backend_available(
  const gala_backend_t backend)
{
  switch (backend) {
  #if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
    case GALA_BACKEND_D3D9:
    case GALA_BACKEND_D3D10:
    case GALA_BACKEND_D3D11:
    case GALA_BACKEND_D3D12:
    case GALA_BACKEND_GL2:
    case GALA_BACKEND_GL3:
    case GALA_BACKEND_GL4:
      return true;
  #elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__
    case GALA_BACKEND_D3D9:
    case GALA_BACKEND_D3D10:
    case GALA_BACKEND_D3D11:
    case GALA_BACKEND_D3D12:
      return false;
    case GALA_BACKEND_GL2:
    case GALA_BACKEND_GL3:
    case GALA_BACKEND_GL4:
      return true;
  #elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__
    case GALA_BACKEND_D3D9:
    case GALA_BACKEND_D3D10:
    case GALA_BACKEND_D3D11:
    case GALA_BACKEND_D3D12:
      return false;
    case GALA_BACKEND_GL2:
    case GALA_BACKEND_GL3:
    case GALA_BACKEND_GL4:
      return true;
  #endif
    case GALA_BACKEND_GLES:
    case GALA_BACKEND_GLES2:
    case GALA_BACKEND_GLES3:
    default:
      break;
  }

  return false;
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//===----------------------------------------------------------------------===//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace gala {

//===----------------------------------------------------------------------===//

namespace backend {

bool available(
  const gala::backends::__Enum__ backend)
{
  return ::gala_backend_available((::gala_backend_t)backend);
}

} // backend

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
