//===-- gala/resources/shader.h -------------------------*- mode: C++11 -*-===//
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

#ifndef _GALA_RESOURCES_SHADER_H_
#define _GALA_RESOURCES_SHADER_H_

#include "gala/resource.h"

GALA_BEGIN_EXTERN_C

typedef gala_resource_handle_t gala_shader_handle_t;

typedef enum gala_shader_type {
  /// Vertex shader.
  GALA_VERTEX_SHADER = 1,
  /// Pixel shader.
  GALA_PIXEL_SHADER = 2,
  /// Compute shader.
  GALA_COMPUTE_SHADER = 3,
  /// \internal Force gala_uint32_t storage and alignment.
  GALA_SHADER_TYPE_FORCE_UINT32 = 0x7fffffff
} gala_shader_type_t;

typedef enum gala_shader_encoding {
  GALA_SHADER_SOURCE   = 1,
  GALA_SHADER_COMPILED = 2,
  GALA_SHADER_CACHED   = 3,
} gala_shader_encoding_t;

typedef struct gala_shader_desc {
  /// Vertex, pixel, or compute shader?
  gala_shader_type_t type;

  /// Source, bytecode, or cached?
  gala_shader_encoding_t encoding;

  /// Opaque value to identify cached shader format.
  /// \note Ignored unless `type` is `GALA_SHADER_CACHED`.
  gala_uint64_t magic;

  const void *source;
  gala_uint32_t length;
} gala_shader_desc_t;

/// \def GALA_INVALID_SHADER_HANDLE
/// \copydoc GALA_INVALID_RESOURCE_HANDLE
#define GALA_INVALID_SHADER_HANDLE \
  GALA_INVALID_RESOURCE_HANDLE

// Defined in `gala/engine.h`
typedef struct gala_engine gala_engine_t;

// Defined in `gala/command_buffer.h`
typedef struct gala_command_buffer gala_command_buffer_t;

extern GALA_PUBLIC
gala_shader_handle_t gala_shader_create(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  const gala_shader_desc_t *desc);

extern GALA_PUBLIC
void gala_shader_destroy(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  gala_shader_handle_t handle);

// TODO(mtwilliams): Reflection.
 // Input attribute layout will be explicit.
 // Constants are queried.

GALA_END_EXTERN_C

#endif // _GALA_RESOURCES_SHADER_H_
