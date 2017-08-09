//===-- gala/resources/input_layout.h -------------------*- mode: C++11 -*-===//
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

#ifndef _GALA_RESOURCES_INPUT_LAYOUT_H_
#define _GALA_RESOURCES_INPUT_LAYOUT_H_

#include "gala/resource.h"

#include "gala/format.h"

GALA_BEGIN_EXTERN_C

typedef gala_resource_handle_t gala_input_layout_handle_t;

typedef struct gala_input_layout_attribute {
  gala_uint32_t slot;
  const char *name;
  gala_uint32_t index;
  gala_format_t format;
  gala_uint32_t stride;
  gala_uint32_t rate;
} gala_input_layout_attribute_t;

typedef struct gala_input_layout_desc {
  gala_uint32_t count;
  gala_input_layout_attribute_t attributes[16];  
} gala_input_layout_desc_t;

/// \def GALA_INVALID_INPUT_LAYOUT_HANDLE
/// \copydoc GALA_INVALID_RESOURCE_HANDLE
#define GALA_INVALID_INPUT_LAYOUT_HANDLE \
  GALA_INVALID_RESOURCE_HANDLE

// Defined in `gala/engine.h`
typedef struct gala_engine gala_engine_t;

// Defined in `gala/command_buffer.h`
typedef struct gala_command_buffer gala_command_buffer_t;

extern GALA_PUBLIC
gala_input_layout_handle_t gala_input_layout_create(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  const gala_input_layout_desc_t *desc);

extern GALA_PUBLIC
void gala_input_layout_destroy(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  gala_input_layout_handle_t handle);

GALA_END_EXTERN_C

#endif // _GALA_RESOURCES_INPUT_LAYOUT_H_
