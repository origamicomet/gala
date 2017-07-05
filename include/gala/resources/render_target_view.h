//===-- gala/resources/render_target_view.h -------------*- mode: C++11 -*-===//
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

#ifndef _GALA_RESOURCES_RENDER_TARGET_VIEW_H_
#define _GALA_RESOURCES_RENDER_TARGET_VIEW_H_

#include "gala/resource.h"

#include "gala/pixel_format.h"

GALA_BEGIN_EXTERN_C

typedef gala_resource_handle_t gala_render_target_view_handle_t;

typedef struct gala_render_target_view_desc {
  /// Format.
  gala_pixel_format_t format;

  /// One, two, or three dimensional?
  gala_dimensionality_t dimensionality;

  /// \defgroup Dimensions
  /// @{
  gala_uint32_t width;
  gala_uint32_t height;
  /// @}

  /// Backing storage to render into.
  /// May be a swap-chain, texture, or a buffer.
  gala_resource_handle_t storage;
} gala_render_target_view_desc_t;

/// \def GALA_INVALID_RENDER_TARGET_VIEW_HANDLE
/// \copydoc GALA_INVALID_RESOURCE_HANDLE
#define GALA_INVALID_RENDER_TARGET_VIEW_HANDLE \
  GALA_INVALID_RESOURCE_HANDLE

// Defined in `gala/engine.h`
typedef struct gala_engine gala_engine_t;

// Defined in `gala/command_buffer.h`
typedef struct gala_command_buffer gala_command_buffer_t;

extern GALA_PUBLIC
gala_render_target_view_handle_t gala_render_target_view_create(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  const gala_render_target_view_desc_t *desc);

extern GALA_PUBLIC
void gala_render_target_view_destroy(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  gala_render_target_view_handle_t handle);

GALA_END_EXTERN_C

#endif // _GALA_RESOURCES_RENDER_TARGET_VIEW_H_
