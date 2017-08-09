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
void gala_set_viewport(
  gala_command_buffer_t *command_buffer,
  gala_uint32_t x,
  gala_uint32_t y,
  gala_uint32_t w,
  gala_uint32_t h);

extern GALA_PUBLIC
void gala_set_scissor(
  gala_command_buffer_t *command_buffer,
  gala_uint32_t x,
  gala_uint32_t y,
  gala_uint32_t w,
  gala_uint32_t h);

extern GALA_PUBLIC
void gala_set_pipeline(
  gala_command_buffer_t *command_buffer,
  gala_pipeline_handle_t pipeline_handle);

extern GALA_PUBLIC
void gala_set_shaders(
  gala_command_buffer_t *command_buffer,
  gala_shader_handle_t vertex_shader_handle,
  gala_shader_handle_t pixel_shader_handle);

extern GALA_PUBLIC
void gala_set_input_layout(
  gala_command_buffer_t *command_buffer,
  gala_input_layout_handle_t input_layout_handle);

extern GALA_PUBLIC
void gala_set_topology(
  gala_command_buffer_t *command_buffer,
  gala_topology_t topology);

extern GALA_PUBLIC
void gala_set_render_and_depth_stencil_targets(
  gala_command_buffer_t *command_buffer,
  gala_uint32_t num_render_targets,
  gala_render_target_view_handle_t *render_targets,
  gala_depth_stencil_target_view_handle_t depth_stencil_target);

// TODO(mtwilliams): Expose a variant that specifies different clear values for
// each target.
extern GALA_PUBLIC
void gala_clear_render_targets(
  gala_command_buffer_t *command_buffer,
  gala_float32_t r,
  gala_float32_t g,
  gala_float32_t b,
  gala_float32_t a);

extern GALA_PUBLIC
void gala_draw(
  gala_command_buffer_t *command_buffer,
  const gala_draw_t *draw);

extern GALA_PUBLIC
void gala_present(
  gala_command_buffer_t *command_buffer,
  gala_swap_chain_handle_t swap_chain_handle);

// PERF(mtwilliams): Expose a resource discard command that invalidates
// contents of a resource. Would equate to `glInvalidateXxx`.

GALA_END_EXTERN_C

#endif // _GALA_RENDER_H_
