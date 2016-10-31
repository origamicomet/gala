//===-- gala/render.h -----------------------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_RENDER_H_
#define _GALA_RENDER_H_

#include "gala/foundation.h"

#include "gala/resource.h"
#include "gala/resources.h"

#include "gala/command.h"
#include "gala/commands.h"
#include "gala/command_buffer.h"

GALA_BEGIN_EXTERN_C

// Defined in `gala/engine.h`
typedef struct gala_engine gala_engine_t;

extern GALA_PUBLIC
void gala_set_render_and_depth_stencil_targets(
  gala_command_buffer_t *command_buffer,
  gala_uint32_t num_render_targets,
  gala_render_target_view_handle_t *render_targets,
  gala_depth_stencil_target_view_handle_t depth_stencil_target);

extern GALA_PUBLIC
void gala_clear_render_targets_command(
  gala_command_buffer_t *command_buffer,
  gala_float32_t r,
  gala_float32_t g,
  gala_float32_t b,
  gala_float32_t a);

extern GALA_PUBLIC
void gala_present(
  gala_command_buffer_t *command_buffer,
  gala_swap_chain_handle_t swap_chain_handle);

GALA_END_EXTERN_C

#endif // _GALA_RENDER_H_
