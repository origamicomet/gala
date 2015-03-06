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

void
gala_backend_init(
  gala_backend_t *backend)
{
  gala_assert_debug(backend != NULL);
  backend->type = GALA_BACKEND_TYPE_INVALID;
}

//===----------------------------------------------------------------------===//

void
gala_backend_shutdown(
  gala_backend_t *backend)
{
  gala_assert_debug(backend != NULL);
#if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
  // This might help find some (stupid) bugs.
  backend->type = GALA_BACKEND_TYPE_INVALID;
#endif
}

//===----------------------------------------------------------------------===//

int gala_backend_to_s(
  const gala_backend_t *backend,
  char buf[],
  const int buf_sz)
{
  gala_assert_debug(backend != NULL);
  return snprintf(buf, buf_sz, "#<gala_backend_t:%.16" PRIxPTR ">", backend);
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//
