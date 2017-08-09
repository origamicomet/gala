//===-- gala/debug.h ------------------------------------*- mode: C++11 -*-===//
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

#ifndef _GALA_DEBUG_H_
#define _GALA_DEBUG_H_

#include "gala/foundation.h"

#include "gala/resource.h"

GALA_BEGIN_EXTERN_C

// Defined in `gala/command_buffer.h`
typedef struct gala_command_buffer gala_command_buffer_t;

extern GALA_PUBLIC
void gala_push_annotation(
  gala_command_buffer_t *command_buffer,
  const char *label,
  gala_uint32_t color);

extern GALA_PUBLIC
void gala_pop_annotation(
  gala_command_buffer_t *command_buffer);

extern GALA_PUBLIC
void gala_label(
  gala_command_buffer_t *command_buffer,
  gala_resource_handle_t handle,
  const char *name);

GALA_END_EXTERN_C

#endif // _GALA_DEBUG_H_
