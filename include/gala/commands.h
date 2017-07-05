//===-- gala/commands.h ---------------------------------*- mode: C++11 -*-===//
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

#ifndef _GALA_COMMANDS_H_
#define _GALA_COMMANDS_H_

#include "gala/foundation.h"

#include "gala/resource.h"
#include "gala/resources.h"

#include "gala/command.h"
#include "gala/command_buffer.h"

GALA_BEGIN_EXTERN_C

typedef struct gala_fence_command {
  gala_command_t command;
  gala_fence_t *fence;
  gala_fence_t writeback;
} gala_fence_command_t;

typedef struct gala_create_swap_chain_command {
  gala_command_t command;
  gala_swap_chain_handle_t swap_chain_handle;
  gala_swap_chain_desc_t desc;
} gala_create_swap_chain_command_t;

typedef struct gala_destroy_swap_chain_command {
  gala_command_t command;
  gala_swap_chain_handle_t swap_chain_handle;
} gala_destroy_swap_chain_command_t;

typedef struct gala_resize_swap_chain_command {
  gala_command_t command;
  gala_swap_chain_handle_t swap_chain_handle;
  gala_uint32_t width;
  gala_uint32_t height;
} gala_resize_swap_chain_command_t;

typedef struct gala_create_render_target_view_command {
  gala_command_t command;
  gala_render_target_view_handle_t render_target_view_handle;
  gala_render_target_view_desc_t desc;
} gala_create_render_target_view_command_t;

typedef struct gala_destroy_render_target_view_command {
  gala_command_t command;
  gala_render_target_view_handle_t render_target_view_handle;
} gala_destroy_render_target_view_command_t;

typedef struct gala_create_depth_stencil_target_view_command {
  gala_command_t command;
  gala_depth_stencil_target_view_handle_t depth_stencil_target_view_handle;
  gala_depth_stencil_target_view_desc_t desc;
} gala_create_depth_stencil_target_view_command_t;

typedef struct gala_destroy_depth_stencil_target_view_command {
  gala_command_t command;
  gala_depth_stencil_target_view_handle_t depth_stencil_target_view_handle;
} gala_destroy_depth_stencil_target_view_command_t;

typedef struct gala_set_render_and_depth_stencil_targets_command {
  gala_command_t command;
  gala_uint32_t num_render_target_views;
  gala_render_target_view_handle_t render_target_view_handles[8];
  gala_depth_stencil_target_view_handle_t depth_stencil_target_view_handle;
} gala_set_render_and_depth_stencil_targets_command_t;

// TODO(mtwilliams): Expose granular clearing.
typedef struct gala_clear_render_targets_command {
  gala_command_t command;
  gala_float32_t rgba[4];
} gala_clear_render_targets_command_t;

typedef struct gala_clear_depth_stencil_target_command {
  gala_command_t command;
  struct {
    unsigned depth   : 1;
    unsigned stencil : 1;
  } channels;
  gala_float32_t depth;
  gala_uint32_t stencil;
} gala_clear_depth_stencil_target_command_t;

typedef struct gala_present_command {
  gala_command_t command;
  gala_swap_chain_handle_t swap_chain_handle;
} gala_present_command_t;

GALA_END_EXTERN_C

#endif // _GALA_COMMANDS_H_
