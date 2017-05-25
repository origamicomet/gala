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

void gala_set_render_and_depth_stencil_targets(
  gala_command_buffer_t *command_buffer,
  gala_uint32_t num_render_targets,
  gala_render_target_view_handle_t *render_targets,
  gala_depth_stencil_target_view_handle_t depth_stencil_target)
{
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(num_render_targets <= 8);

  gala_set_render_and_depth_stencil_targets_command_t *cmd = (gala_set_render_and_depth_stencil_targets_command_t *)gala_command_buffer_allocate(command_buffer, sizeof(gala_set_render_and_depth_stencil_targets_command_t));

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

  gala_clear_render_targets_command_t *cmd = (gala_clear_render_targets_command_t *)gala_command_buffer_allocate(command_buffer, sizeof(gala_clear_render_targets_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_CLEAR_RENDER_TARGETS;
  cmd->command.header.size = sizeof(gala_clear_render_targets_command_t);

  cmd->rgba[0] = r;
  cmd->rgba[1] = g;
  cmd->rgba[2] = b;
  cmd->rgba[3] = a;
}

void gala_present(
  gala_command_buffer_t *command_buffer,
  gala_swap_chain_handle_t swap_chain_handle)
{
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(swap_chain_handle != GALA_INVALID_SWAP_CHAIN_HANDLE);

  gala_present_command_t *cmd = (gala_present_command_t *)gala_command_buffer_allocate(command_buffer, sizeof(gala_present_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_PRESENT;
  cmd->command.header.size = sizeof(gala_present_command_t);

  cmd->swap_chain_handle = swap_chain_handle;
}

GALA_END_EXTERN_C
