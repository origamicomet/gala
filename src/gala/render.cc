//===-- gala/render.cc ----------------------------------------*- C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//

#include "gala/render.h"

GALA_BEGIN_EXTERN_C

void gala_set_viewport(
  gala_command_buffer_t *command_buffer,
  gala_uint32_t x,
  gala_uint32_t y,
  gala_uint32_t w,
  gala_uint32_t h)
{
  gala_assert_debug(command_buffer != NULL);

  gala_set_viewport_command_t *cmd =
    (gala_set_viewport_command_t *)
      gala_command_buffer_allocate(command_buffer,
                                   sizeof(gala_set_viewport_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_SET_VIEWPORT;
  cmd->command.header.size = sizeof(gala_set_viewport_command);

  cmd->x = x;
  cmd->y = y;
  cmd->w = w;
  cmd->h = h;
}

void gala_set_scissor(
  gala_command_buffer_t *command_buffer,
  gala_uint32_t x,
  gala_uint32_t y,
  gala_uint32_t w,
  gala_uint32_t h)
{
  gala_assert_debug(command_buffer != NULL);

  gala_set_scissor_command_t *cmd =
    (gala_set_scissor_command_t *)
      gala_command_buffer_allocate(command_buffer,
                                   sizeof(gala_set_scissor_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_SET_SCISSOR;
  cmd->command.header.size = sizeof(gala_set_scissor_command);

  cmd->x = x;
  cmd->y = y;
  cmd->w = w;
  cmd->h = h;
}

void gala_set_pipeline(
  gala_command_buffer_t *command_buffer,
  gala_pipeline_handle_t pipeline_handle)
{
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(pipeline_handle != GALA_INVALID_PIPELINE_HANDLE);

  gala_set_pipeline_command_t *cmd =
    (gala_set_pipeline_command_t *)
      gala_command_buffer_allocate(command_buffer,
                                   sizeof(gala_set_pipeline_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_SET_PIPELINE;
  cmd->command.header.size = sizeof(gala_set_pipeline_command_t);

  cmd->pipeline_handle = pipeline_handle;
}

void gala_set_shaders(
  gala_command_buffer_t *command_buffer,
  gala_shader_handle_t vertex_shader_handle,
  gala_shader_handle_t pixel_shader_handle)
{
  gala_assert_debug(command_buffer != NULL);

  gala_set_shaders_command_t *cmd =
    (gala_set_shaders_command_t *)
      gala_command_buffer_allocate(command_buffer,
                                   sizeof(gala_set_shaders_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_SET_SHADERS;
  cmd->command.header.size = sizeof(gala_set_shaders_command_t);

  cmd->vertex_shader_handle = vertex_shader_handle;
  cmd->pixel_shader_handle = pixel_shader_handle;
}

void gala_set_input_layout(
  gala_command_buffer_t *command_buffer,
  gala_input_layout_handle_t input_layout_handle)
{
  gala_assert_debug(command_buffer != NULL);

  gala_set_input_layout_command_t *cmd =
    (gala_set_input_layout_command_t *)
      gala_command_buffer_allocate(command_buffer,
                                   sizeof(gala_set_input_layout_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_SET_INPUT_LAYOUT;
  cmd->command.header.size = sizeof(gala_set_input_layout_command_t);

  cmd->input_layout_handle = input_layout_handle;
}

void gala_set_topology(
  gala_command_buffer_t *command_buffer,
  gala_topology_t topology)
{
  gala_assert_debug(command_buffer != NULL);

  gala_set_topology_command_t *cmd =
    (gala_set_topology_command_t *)
      gala_command_buffer_allocate(command_buffer,
                                   sizeof(gala_set_topology_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_SET_TOPOLOGY;
  cmd->command.header.size = sizeof(gala_set_topology_command_t);

  cmd->topology = topology;
}

void gala_set_render_and_depth_stencil_targets(
  gala_command_buffer_t *command_buffer,
  gala_uint32_t num_render_targets,
  const gala_render_target_view_handle_t *render_targets,
  gala_depth_stencil_target_view_handle_t depth_stencil_target)
{
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(num_render_targets <= 8);

  gala_set_render_and_depth_stencil_targets_command_t *cmd =
    (gala_set_render_and_depth_stencil_targets_command_t *)
      gala_command_buffer_allocate(command_buffer,
                                   sizeof(gala_set_render_and_depth_stencil_targets_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_SET_RENDER_AND_DEPTH_STENCIL_TARGETS;
  cmd->command.header.size = sizeof(gala_set_render_and_depth_stencil_targets_command_t);

  cmd->num_render_target_views = num_render_targets;

  memcpy((void *)&cmd->render_target_view_handles[0],
         (const void *)&render_targets[0],
         num_render_targets * sizeof(gala_render_target_view_handle_t));

  cmd->depth_stencil_target_view_handle = depth_stencil_target;
}

void gala_clear_render_targets(
  gala_command_buffer_t *command_buffer,
  gala_float32_t r,
  gala_float32_t g,
  gala_float32_t b,
  gala_float32_t a)
{
  gala_assert_debug(command_buffer != NULL);

  gala_clear_render_targets_command_t *cmd =
    (gala_clear_render_targets_command_t *)
      gala_command_buffer_allocate(command_buffer,
                                   sizeof(gala_clear_render_targets_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_CLEAR_RENDER_TARGETS;
  cmd->command.header.size = sizeof(gala_clear_render_targets_command_t);

  cmd->rgba[0] = r;
  cmd->rgba[1] = g;
  cmd->rgba[2] = b;
  cmd->rgba[3] = a;
}

void gala_draw(
  gala_command_buffer_t *command_buffer,
  const gala_draw_t *draw)
{
  gala_assert_debug(command_buffer != NULL);

  gala_draw_command_t *cmd =
    (gala_draw_command_t *)
      gala_command_buffer_allocate(command_buffer,
                                   sizeof(gala_draw_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_DRAW;
  cmd->command.header.size = sizeof(gala_draw_command_t);

  cmd->indicies = draw->indicies;
  cmd->vertices = draw->vertices;
  
  cmd->constants[0] = draw->constants[0];
  cmd->constants[1] = draw->constants[1];
  cmd->constants[2] = draw->constants[2];
  cmd->constants[3] = draw->constants[3];
  cmd->constants[4] = draw->constants[4];
  cmd->constants[5] = draw->constants[5];
  cmd->constants[6] = draw->constants[6];
  cmd->constants[7] = draw->constants[7];

  cmd->first = draw->first;
  cmd->count = draw->count;
}

void gala_present(
  gala_command_buffer_t *command_buffer,
  gala_swap_chain_handle_t swap_chain_handle)
{
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(swap_chain_handle != GALA_INVALID_SWAP_CHAIN_HANDLE);

  gala_present_command_t *cmd =
    (gala_present_command_t *)
      gala_command_buffer_allocate(command_buffer,
                                   sizeof(gala_present_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_PRESENT;
  cmd->command.header.size = sizeof(gala_present_command_t);

  cmd->swap_chain_handle = swap_chain_handle;
}

GALA_END_EXTERN_C
