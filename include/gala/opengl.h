//===-- gala/opengl.h -----------------------------------*- mode: C++11 -*-===//
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

#ifndef _GALA_GL_H_
#define _GALA_GL_H_

#include "gala/foundation.h"

#include "gala/backend.h"
#include "gala/engine.h"

GALA_BEGIN_EXTERN_C

extern GALA_PUBLIC
void gala_ogl_init(void);

extern GALA_PUBLIC
void gala_ogl_shutdown(void);

extern GALA_PUBLIC
gala_engine_t *gala_ogl_create_and_init_engine(
  const gala_engine_creation_params_t *engine_creation_params);

extern GALA_PUBLIC
void gala_ogl_destroy_engine(
  gala_engine_t *engine);

extern GALA_PUBLIC
void gala_ogl_engine_execute(
  gala_engine_t *engine,
  const gala_command_buffer_t *commands);

GALA_END_EXTERN_C

#endif // _GALA_GL_H_
