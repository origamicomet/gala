//===-- gala/pipeline.h ---------------------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//
//
// TODO(mtwilliams): Document the purpose of this file.
//
//===----------------------------------------------------------------------===//

#ifndef _GALA_PIPELINE_H_
#define _GALA_PIPELINE_H_

#include "gala/resource.h"

GALA_BEGIN_EXTERN_C

typedef enum gala_winding {
  GALA_CW  = 1,
  GALA_CCW = 2
} gala_winding_t;

typedef enum gala_fill_mode {
  GALA_SOLID     = 1,
  GALA_WIREFRAME = 2,
} gala_fill_mode_t;

typedef enum gala_cull_mode {
  GALA_CULL_NONE  = 0,
  GALA_CULL_FRONT = 1,
  GALA_CULL_BACK  = 2
} gala_cull_mode_t;

typedef enum gala_comparison {
  GALA_NEVER         = 0,
  GALA_LESS          = 1,
  GALA_EQUAL         = 2,
  GALA_LESS_EQUAL    = 3,
  GALA_GREATER       = 4,
  GALA_GREATER_EQUAL = 5,
  GALA_NOT_EQUAL     = 6,
  GALA_ALWAYS        = 7,
  /// \internal Force gala_uint32_t storage and alignment.
  GALA_COMPARISON_FORCE_UINT32 = 0x7fffffff
} gala_comparison_t;

typedef enum gala_blend {
  GALA_BLEND_ZERO               = 0,
  GALA_BLEND_ONE                = 1,
  GALA_BLEND_SRC_COLOR          = 2,
  GALA_BLEND_INV_SRC_COLOR      = 3,
  GALA_BLEND_SRC_ALPHA          = 4,
  GALA_BLEND_INV_SRC_ALPHA      = 5,
  GALA_BLEND_DEST_ALPHA         = 6,
  GALA_BLEND_INV_DEST_ALPHA     = 7,
  GALA_BLEND_DEST_COLOR         = 8,
  GALA_BLEND_INV_DEST_COLOR     = 9,
  GALA_BLEND_SRC_ALPHA_SATURATE = 10,
  GALA_BLEND_BLEND_FACTOR       = 11,
  GALA_BLEND_INV_BLEND_FACTOR   = 12,
} gala_blend_t;

typedef enum gala_blend_operation {
  GALA_BLEND_OP_ADD          = 0,
  GALA_BLEND_OP_SUBTRACT     = 1,
  GALA_BLEND_OP_REV_SUBTRACT = 2,
  GALA_BLEND_OP_MIN          = 3,
  GALA_BLEND_OP_MAX          = 4
} gala_blend_operation_t;

typedef enum gala_stencil_operation {
  GALA_STENCIL_OP_ZERO               = 0,
  GALA_STENCIL_OP_KEEP               = 1,
  GALA_STENCIL_OP_REPLACE            = 2,
  GALA_STENCIL_OP_INVERT             = 3,
  GALA_STENCIL_OP_INCREMENT          = 4,
  GALA_STENCIL_OP_DECREMENT          = 5,
  GALA_STENCIL_OP_INCREMENT_SATURATE = 6,
  GALA_STENCIL_OP_DECREMENT_SATURATE = 7
} gala_stencil_operation_t;

typedef gala_resource_handle_t gala_pipeline_handle_t;

typedef struct gala_pipeline_desc {
  gala_winding_t winding;

  gala_fill_mode_t fill;
  gala_cull_mode_t cull;

  struct {
    gala_bool_t blend;

    // TODO(mtwilliams): Seperate color and alpha. 
    gala_blend_t src;
    gala_blend_t dst;
    gala_blend_operation_t op;

    gala_float32_t factor[4];

    // TODO(mtwilliams): Document mask layout.
     // 0-3 = RGBA for Render Target 0
     // 4-7 = RGBA for Render Target 1
     // ...
    gala_uint32_t mask;
  } color;

  struct {
    gala_bool_t test;

    gala_comparison_t comparison;

    gala_uint32_t mask;
  } depth;

  struct {
    gala_bool_t test;

    struct {
      gala_comparison_t comparison;
      gala_stencil_operation_t pass;
      gala_stencil_operation_t fail_to_depth;
      gala_stencil_operation_t fail_to_stencil;
    } front;

    struct {
      gala_comparison_t comparison;
      gala_stencil_operation_t pass;
      gala_stencil_operation_t fail_to_depth;
      gala_stencil_operation_t fail_to_stencil;
    } back;

    gala_uint8_t ref;

    // TODO(mtwilliams): Read mask as well?
    gala_uint8_t mask;
  } stencil;
} gala_pipeline_desc_t;

/// \def GALA_INVALID_PIPELINE_HANDLE
/// \copydoc GALA_INVALID_RESOURCE_HANDLE
#define GALA_INVALID_PIPELINE_HANDLE \
  GALA_INVALID_RESOURCE_HANDLE

// Defined in `gala/engine.h`
typedef struct gala_engine gala_engine_t;

// Defined in `gala/command_buffer.h`
typedef struct gala_command_buffer gala_command_buffer_t;

extern GALA_PUBLIC
gala_pipeline_handle_t gala_pipeline_create(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  const gala_pipeline_desc_t *desc);

extern GALA_PUBLIC
void gala_pipeline_destroy(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  gala_pipeline_handle_t handle);

GALA_END_EXTERN_C

#endif // _GALA_PIPELINE_H_
