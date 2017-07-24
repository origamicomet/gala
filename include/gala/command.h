//===-- gala/command.h  ---------------------------------*- mode: C++11 -*-===//
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

#ifndef _GALA_COMMAND_H_
#define _GALA_COMMAND_H_

#include "gala/foundation.h"

GALA_BEGIN_EXTERN_C

typedef enum gala_command_type {
  /// No operation; do nothing.
  GALA_COMMAND_TYPE_NOP = 0,

  // Debug

  GALA_COMMAND_TYPE_ANNOTATE,
  GALA_COMMAND_TYPE_LABEL,

  // ...

  // Profiling

  // ...

  // Synchronization

  /// TODO(mtwilliams): Require frame markers.
  ///
  GALA_COMMAND_TYPE_START_OF_FRAME,
  GALA_COMMAND_TYPE_END_OF_FRAME,

  /// Writes a value when Gala has submitted all previous commands.
  GALA_COMMAND_TYPE_FENCE_ON_SUBMISSION,

  /// Writes a value when the GPU has processed all previous commands.
  /// \warning This can take a substantial amount of time and may even stall
  /// with some backends. Use sparingly.
  GALA_COMMAND_TYPE_FENCE_ON_COMPLETION,

  // Swap Chain
  GALA_COMMAND_TYPE_CREATE_SWAP_CHAIN,
  GALA_COMMAND_TYPE_DESTROY_SWAP_CHAIN,
  GALA_COMMAND_TYPE_RESIZE_SWAP_CHAIN,

  // Buffers
  GALA_COMMAND_TYPE_CREATE_BUFFER,
  GALA_COMMAND_TYPE_DESTROY_BUFFER,

  // Textures
  GALA_COMMAND_TYPE_CREATE_TEXTURE,
  GALA_COMMAND_TYPE_DESTROY_TEXTURE,

  // Samplers
  GALA_COMMAND_TYPE_CREATE_SAMPLER,
  GALA_COMMAND_TYPE_DESTROY_SAMPLER,

  // Pipelines
  GALA_COMMAND_TYPE_CREATE_PIPELINE,
  GALA_COMMAND_TYPE_DESTROY_PIPELINE,

  // Render Targets
  GALA_COMMAND_TYPE_CREATE_RENDER_TARGET_VIEW,
  GALA_COMMAND_TYPE_DESTROY_RENDER_TARGET_VIEW,

  // Depth-Stencil Targets
  GALA_COMMAND_TYPE_CREATE_DEPTH_STENCIL_TARGET_VIEW,
  GALA_COMMAND_TYPE_DESTROY_DEPTH_STENCIL_TARGET_VIEW,

  // State
  GALA_COMMAND_TYPE_SET_VIEWPORT,
  GALA_COMMAND_TYPE_SET_SCISSOR,
  GALA_COMMAND_TYPE_SET_PIPELINE,
  GALA_COMMAND_TYPE_SET_RENDER_AND_DEPTH_STENCIL_TARGETS,

  // Rendering
  GALA_COMMAND_TYPE_CLEAR_RENDER_TARGETS,
  GALA_COMMAND_TYPE_CLEAR_DEPTH_STENCIL_TARGET,

  // Transfer
  GALA_COMMAND_TYPE_READ_FROM_BUFFER,
  GALA_COMMAND_TYPE_WRITE_TO_BUFFER,
  GALA_COMMAND_TYPE_READ_FROM_TEXTURE,
  GALA_COMMAND_TYPE_WRITE_TO_TEXTURE,

  // Presentation
  GALA_COMMAND_TYPE_PRESENT = 255,

  /// \internal Force gala_uint32_t storage and alignment.
  GALA_COMMAND_TYPE_FORCE_UINT32 = 0x7fffffff
} gala_command_type_t;

typedef struct gala_command_header {
  gala_command_type_t type;
  gala_uint32_t size;
} gala_command_header_t;

typedef struct gala_command {
  gala_command_header_t header;
} gala_command_t;

GALA_END_EXTERN_C

#endif // _GALA_COMMAND_H_
