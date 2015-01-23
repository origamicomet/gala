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

//===----------------------------------------------------------------------===//

#include "gala/adapter_d3d9_win32.h"

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

  const UINT uiAdapterCount = backend->D3D9->GetAdapterCount();
  backend->__backend__.num_adapters = (size_t)uiAdapterCount;
  gala_adapter_d3d9_t *adapters = (gala_adapter_d3d9_t *)calloc((size_t)uiAdapterCount,
                                                                sizeof(gala_adapter_d3d9_t));
  const gala_adapter_t **adapters_ = (const gala_adapter_t **)calloc((size_t)uiAdapterCount,
                                                                     sizeof(gala_adapter_t *));
  backend->__backend__.adapters = adapters_;
#ifndef GALA_DISABLE_ERROR_CHECKS
  if ((adapters == NULL) || (adapters_ == NULL)) {
    if (adapters)
      free((void *)adapters);
    if (adapters_)
      free((void *)adapters_);
    FreeLibrary(backend->hDll);
    free((void *)backend);
    if (error_details) {
      *error_details = gala_error_details_create_unformatted(
        GALA_ERROR_OUT_OF_MEMORY,
        "Ran out of memory when querying Direct3D9 adapters.");
    }
    return GALA_ERROR_OUT_OF_MEMORY;
  }
#endif // !GALA_DISABLE_ERROR_CHECKS

  for (UINT uiAdapter = 0; uiAdapter < uiAdapterCount; ++uiAdapter) {
    adapters_[uiAdapter] = (const gala_adapter_t *)&adapters[uiAdapter];
    // TODO(mike): Stop assuming the adapter is hardware accelerated.
    adapters[uiAdapter].__adapter__.type = GALA_ADAPTER_HARDWARE;
    adapters[uiAdapter].__adapter__._backend = (gala_backend_t *)backend;
    adapters[uiAdapter].uiAdapter = uiAdapter;
    /* adapters[uiAdapter].Identifier = */ {
      const HRESULT Result = backend->D3D9->GetAdapterIdentifier(uiAdapter, 0, &adapters[uiAdapter].Identifier);
    #ifndef GALA_DISABLE_ERROR_CHECKS
      if (FAILED(Result)) {
        uiAdapter -= 1;
        for (; uiAdapter >= 0; --uiAdapter)
          CloseHandle(adapters[uiAdapter].hMonitor);
        free((void *)adapters);
        free((void *)adapters_);
        FreeLibrary(backend->hDll);
        free((void *)backend);
        if (error_details) {
          *error_details = gala_error_details_create_unformatted(
            GALA_ERROR_UNKNOWN,
            "Failed to query an adapter's identifier.");
        }
        return GALA_ERROR_UNKNOWN;
      }
    #endif // !GALA_DISABLE_ERROR_CHECKS
    }
    if (strstr(adapters[uiAdapter].Identifier.Description, ".") != NULL)
      adapters[uiAdapter].__adapter__.type = GALA_ADAPTER_PROXY;
    /* adapters[uiAdapter].hMonitor = */ {
      adapters[uiAdapter].hMonitor = backend->D3D9->GetAdapterMonitor(uiAdapter);
    #ifndef GALA_DISABLE_ERROR_CHECKS
      if (adapters[uiAdapter].hMonitor == NULL) {
        uiAdapter -= 1;
        for (; uiAdapter >= 0; --uiAdapter)
          CloseHandle(adapters[uiAdapter].hMonitor);
        free((void *)adapters);
        free((void *)adapters_);
        FreeLibrary(backend->hDll);
        free((void *)backend);
        if (error_details) {
          *error_details = gala_error_details_create_unformatted(
            GALA_ERROR_UNKNOWN,
            "Failed to query an adapter's associated monitor.");
        }
        return GALA_ERROR_UNKNOWN;
      }
    #endif // !GALA_DISABLE_ERROR_CHECKS
    }
    // TODO(mike):
    adapters[uiAdapter].__adapter__.num_outputs = 0;
    adapters[uiAdapter].__adapter__.outputs = NULL;
  }

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
  for (UINT uiAdapter = 0; uiAdapter < backend->__backend__.num_adapters; ++uiAdapter)
    CloseHandle(((const gala_adapter_d3d9_t **)backend->__backend__.adapters)[uiAdapter]->hMonitor);
  free((void *)backend->__backend__.adapters);
  free((void *)backend->__backend__.adapters[0]);
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
