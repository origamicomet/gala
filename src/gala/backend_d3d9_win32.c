//===-- gala/backend_d3d9_win32.c -------------------------------*- C++ -*-===//
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

#include "gala/backend_d3d9_win32.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

gala_error_t gala_backend_initialize_d3d9(
  gala_backend_t **backend_,
  const gala_error_details_t **error_details)
{
  // TODO(mike): Use a user-specified allocator.
  gala_backend_d3d9_t *backend =
    (gala_backend_d3d9_t *)calloc(sizeof(gala_backend_d3d9_t), 1);

  backend->__backend__.type = GALA_BACKEND_D3D9;
  backend->__backend__.shutdown = &gala_backend_shutdown_d3d9;

  backend->hDll = LoadLibraryA("d3d9.dll");
#ifndef GALA_DISABLE_ERROR_CHECKS
  if (backend->hDll == NULL) {
    free((void *)backend);
    if (error_details) {
      *error_details = gala_error_details_create_unformatted(
        GALA_ERROR_UNKNOWN,
        "Unable to load the Direct3D9 runtime (d3d9.dll).");
    }
    return GALA_ERROR_UNKNOWN;
  }
#endif // !GALA_DISABLE_ERROR_CHECKS

  // TODO(mike): Try Direct3DCreate9Ex?
  typedef IDirect3D9 *(WINAPI *Direct3DCreate9_fn)(UINT);
  Direct3DCreate9_fn Direct3DCreate9_ = (Direct3DCreate9_fn)GetProcAddress(backend->hDll,
                                                                           "Direct3DCreate9");
#ifndef GALA_DISABLE_ERROR_CHECKS
  if (Direct3DCreate9_ == NULL) {
    FreeLibrary(backend->hDll);
    free((void *)backend);
    if (error_details) {
      *error_details = gala_error_details_create_unformatted(
        GALA_ERROR_UNKNOWN,
        "Unable to initialize the Direct3D9 runtime.");
    }
    return GALA_ERROR_UNKNOWN;
  }
#endif // !GALA_DISABLE_ERROR_CHECKS

  backend->D3D9 = Direct3DCreate9_(D3D_SDK_VERSION);
#ifndef GALA_DISABLE_ERROR_CHECKS
  if (backend->D3D9 == NULL) {
    FreeLibrary(backend->hDll);
    free((void *)backend);
    if (error_details) {
      *error_details = gala_error_details_create_unformatted(
        GALA_ERROR_UNKNOWN,
        "Unable to initialize the Direct3D9 runtime.");
    }
    return GALA_ERROR_UNKNOWN;
  }
#endif // !GALA_DISABLE_ERROR_CHECKS

  *backend_ = (gala_backend_t *)backend;
  if (error_details)
    *error_details = NULL;
  return GALA_ERROR_NONE;
}

//===----------------------------------------------------------------------===//

gala_error_t gala_backend_shutdown_d3d9(
  gala_backend_t *backend_,
  const gala_error_details_t **error_details)
{
#ifndef GALA_DISABLE_ARGUMENT_CHECKS
  if (backend_->type != GALA_BACKEND_D3D9) {
    if (error_details) {
      *error_details = gala_error_details_create_unformatted(
        GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS,
        "Expected a backend of type `GALA_BACKEND_D3D9'.");
    }
    return GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS;
  }
#endif // !GALA_DISABLE_ARGUMENT_CHECKS
  gala_backend_d3d9_t *backend = (gala_backend_d3d9_t *)backend_;
  backend->D3D9->Release();
  FreeLibrary(backend->hDll);
  free((void *)backend);
  if (error_details)
    *error_details = NULL;
  return GALA_ERROR_NONE;
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//
