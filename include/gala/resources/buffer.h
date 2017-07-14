//===-- gala/resources/buffer.h -------------------------*- mode: C++11 -*-===//
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

#ifndef _GALA_RESOURCES_BUFFER_H_
#define _GALA_RESOURCES_BUFFER_H_

#include "gala/resource.h"

#include "gala/pixel_format.h"

GALA_BEGIN_EXTERN_C

typedef gala_resource_handle_t gala_buffer_handle_t;

typedef enum gala_buffer_type {
  /// Index buffer.
  GALA_INDEX_BUFFER = 1,
  /// Vertex buffer.
  GALA_VERTEX_BUFFER = 2,
  /// Constant buffer.
  GALA_CONSTANT_BUFFER = 3,
  /// \internal Force gala_uint32_t storage and alignment.
  GALA_BUFFER_TYPE_FORCE_UINT32 = 0x7fffffff
} gala_buffer_type_t;

/// \def GALA_INVALID_BUFFER_HANDLE
/// \copydoc GALA_INVALID_RESOURCE_HANDLE
#define GALA_INVALID_BUFFER_HANDLE \
  GALA_INVALID_RESOURCE_HANDLE

// Defined in `gala/engine.h`
typedef struct gala_engine gala_engine_t;

// Defined in `gala/command_buffer.h`
typedef struct gala_command_buffer gala_command_buffer_t;

extern GALA_PUBLIC
gala_buffer_handle_t gala_buffer_create(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  gala_mutability_t mutability,
  gala_buffer_type_t type,
  gala_uint32_t size,
  const void *data);

extern GALA_PUBLIC
void gala_buffer_update(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  gala_buffer_handle_t buffer,
  gala_uint32_t offset,
  gala_uint32_t length,
  const void *data);

extern GALA_PUBLIC
void gala_buffer_destroy(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  gala_buffer_handle_t handle);

GALA_END_EXTERN_C

#endif // _GALA_RESOURCES_BUFFER_H_
