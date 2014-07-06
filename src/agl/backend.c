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

#include "agl/backend.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

agl_bool_t
agl_backend_available(
  const agl_backend_t backend)
{
  switch (backend) {
    case AGL_BACKEND_D3D9:
    #if AGL_PLATFORM == AGL_PLATFORM_WINDOWS
      return AGL_TRUE;
    #else
      return AGL_FALSE;
    #endif
    case AGL_BACKEND_D3D11:
    #if AGL_PLATFORM == AGL_PLATFORM_WINDOWS
      return AGL_TRUE;
    #else
      return AGL_FALSE;
    #endif
    case AGL_BACKEND_GL21:
    #if (AGL_PLATFORM == AGL_PLATFORM_WINDOWS)  || \
        (AGL_PLATFORM == AGL_PLATFORM_MAC_OS_X) || \
        (AGL_PLATFORM == AGL_PLATFORM_LINUX)
      return AGL_TRUE;
    #else
      return AGL_FALSE;
    #endif
    case AGL_BACKEND_GL31:
    #if (AGL_PLATFORM == AGL_PLATFORM_WINDOWS)  || \
        (AGL_PLATFORM == AGL_PLATFORM_MAC_OS_X) || \
        (AGL_PLATFORM == AGL_PLATFORM_LINUX)
      return AGL_TRUE;
    #else
      return AGL_FALSE;
    #endif
    case AGL_BACKEND_GLES2:
    #if (AGL_PLATFORM == AGL_PLATFORM_ANDROID) || \
        (AGL_PLATFORM == AGL_PLATFORM_IOS)
      return AGL_TRUE;
    #else
      return AGL_FALSE;
    #endif
    case AGL_BACKEND_GLES3:
    #if (AGL_PLATFORM == AGL_PLATFORM_ANDROID) || \
        (AGL_PLATFORM == AGL_PLATFORM_IOS)
      return AGL_TRUE;
    #else
      return AGL_FALSE;
    #endif
  }

  return AGL_FALSE;
}

//===----------------------------------------------------------------------===//

agl_error_t
agl_backend_initialize(
  const agl_backend_t backend,
  agl_error_details_t **error_details)
{
  if (error_details)
    *error_details = AGL_ERROR_UNFORMATTED("Not implemented, yet!");
  return AGL_ERROR_NOT_IMPLEMENTED;
}

//===----------------------------------------------------------------------===//

agl_error_t
agl_backend_shutdown(
  const agl_backend_t backend,
  agl_error_details_t **error_details)
{
  if (error_details)
    *error_details = AGL_ERROR_UNFORMATTED("Not implemented, yet!");
  return AGL_ERROR_NOT_IMPLEMENTED;
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//
