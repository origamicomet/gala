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

// TODO(mtwilliams): Factor into seperate file?
typedef enum gala_topology {
  GALA_POINTS    = 1,
  GALA_LINES     = 2,
  GALA_TRIANGLES = 3,
  /// \internal Force gala_uint32_t storage and alignment.
  GALA_TOPOLOGY_FORCE_UINT32 = 0x7fffffff
} gala_topology_t;

// TODO(mtwilliams): Factor into seperate file?
// TODO(mtwilliams): Indicate mergability and reorderability.
typedef struct gala_draw {
  gala_buffer_handle_t indicies;
  gala_buffer_handle_t vertices;

  gala_buffer_handle_t constants[8];

  gala_uint32_t first;
  gala_uint32_t count;
} gala_draw_t;

typedef struct gala_label_command {
  gala_command_t command;
  gala_resource_handle_t handle;
  char name[256];
} gala_label_command_t;

typedef struct gala_frame_command {
  gala_command_t command;
  gala_uint64_t id;
  gala_uint64_t timestamp;
  struct gala_statistics *statistics;
} gala_frame_command_t;

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

typedef struct gala_create_pipeline_command {
  gala_command_t command;
  gala_pipeline_handle_t pipeline_handle;
  gala_pipeline_desc_t desc;
} gala_create_pipeline_command_t;

typedef struct gala_destroy_pipeline_command {
  gala_command_t command;
  gala_pipeline_handle_t pipeline_handle;
} gala_destroy_pipeline_command_t;

typedef struct gala_create_buffer_command {
  gala_command_t command;
  gala_buffer_handle_t buffer_handle;
  gala_mutability_t mutability;
  gala_uint32_t size;
  const void *data;
} gala_create_buffer_command_t;

typedef struct gala_destroy_buffer_command {
  gala_command_t command;
  gala_buffer_handle_t buffer_handle;
} gala_destroy_buffer_command_t;

typedef struct gala_create_texture_command {
  gala_command_t command;
  gala_texture_handle_t texture_handle;
  gala_texture_desc_t desc;
} gala_create_texture_command_t;

typedef struct gala_destroy_texture_command {
  gala_command_t command;
  gala_texture_handle_t texture_handle;
} gala_destroy_texture_command_t;

typedef struct gala_create_sampler_command {
  gala_command_t command;
  gala_sampler_handle_t sampler_handle;
  gala_sampler_desc_t desc;
} gala_create_sampler_command_t;

typedef struct gala_destroy_sampler_command {
  gala_command_t command;
  gala_sampler_handle_t sampler_handle;
} gala_destroy_sampler_command_t;

typedef struct gala_create_shader_command {
  gala_command_t command;
  gala_shader_handle_t shader_handle;
  gala_shader_desc_t desc;
} gala_create_shader_command_t;

typedef struct gala_destroy_shader_command {
  gala_command_t command;
  gala_shader_handle_t shader_handle;
} gala_destroy_shader_command_t;

typedef struct gala_create_input_layout_command {
  gala_command_t command;
  gala_input_layout_handle_t input_layout_handle;
  gala_input_layout_desc_t desc;
} gala_create_input_layout_command_t;

typedef struct gala_destroy_input_layout_command {
  gala_command_t command;
  gala_input_layout_handle_t input_layout_handle;
} gala_destroy_input_layout_command_t;

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

typedef struct gala_set_viewport_command {
  gala_command_t command;
  gala_uint32_t x, y, w, h;
} gala_set_viewport_command_t;

typedef struct gala_set_scissor_command {
  gala_command_t command;
  gala_uint32_t x, y, w, h;
} gala_set_scissor_command_t;

typedef struct gala_set_pipeline_command {
  gala_command_t command;
  gala_pipeline_handle_t pipeline_handle;
} gala_set_pipeline_command_t;

typedef struct gala_set_shaders_command {
  gala_command_t command;
  gala_shader_handle_t vertex_shader_handle;
  gala_shader_handle_t pixel_shader_handle;
} gala_set_shaders_command_t;

typedef struct gala_set_input_layout_command {
  gala_command_t command;
  gala_input_layout_handle_t input_layout_handle;
} gala_set_input_layout_command_t;

typedef struct gala_set_topology_command {
  gala_command_t command;
  gala_topology_t topology;
} gala_set_topology_command_t;

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

typedef struct gala_draw_command {
  gala_command_t command;
  
  gala_buffer_handle_t indicies;
  gala_buffer_handle_t vertices;
  
  gala_buffer_handle_t constants[8];

  gala_uint32_t first;
  gala_uint32_t count;
} gala_draw_command_t;

typedef struct gala_read_from_buffer_command {
  gala_command_t command;
} gala_read_from_buffer_command_t;

typedef struct gala_write_to_buffer_command {
  gala_command_t command;
  gala_buffer_handle_t buffer_handle;
  gala_uint32_t offset;
  gala_uint32_t length;
  const void *data;
} gala_write_to_buffer_command_t;

typedef struct gala_read_from_texture_command {
  gala_command_t command;
  gala_texture_handle_t texture_handle;
  gala_texture_slice_t slice;
  void *out;
} gala_read_from_texture_command_t;

typedef struct gala_write_to_texture_command {
  gala_command_t command;
  gala_texture_handle_t texture_handle;
  gala_texture_slice_t slice;
  const void *in;
} gala_write_to_texture_command_t;

typedef struct gala_present_command {
  gala_command_t command;
  gala_swap_chain_handle_t swap_chain_handle;
} gala_present_command_t;

GALA_END_EXTERN_C

#endif // _GALA_COMMANDS_H_
