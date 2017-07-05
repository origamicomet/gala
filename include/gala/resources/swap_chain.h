//===-- gala/resources/swap_chain.h ---------------------*- mode: C++11 -*-===//
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

#ifndef _GALA_RESOURCES_SWAP_CHAIN_H_
#define _GALA_RESOURCES_SWAP_CHAIN_H_

#include "gala/resource.h"

#include "gala/pixel_format.h"

GALA_BEGIN_EXTERN_C

typedef gala_resource_handle_t gala_swap_chain_handle_t;

typedef enum gala_swap_chain_flags {
  /// Fullscreen.
  GALA_SWAP_CHAIN_FULLSCREEN = (1 << 0),
  /// Borderless if fullscreen.
  GALA_SWAP_CHAIN_BORDERLESS = (1 << 1)
} gala_swap_chain_flags_t;

typedef struct gala_swap_chain_desc {
  /// Back buffer format.
  gala_pixel_format_t format;

  /// \defgroup Dimensions */
  /// @{
  gala_uint32_t width;
  gala_uint32_t height;
  /// @}

  // TODO(mtwilliams): Refactor into `gala_rational_t`?
  // TODO(mtwilliams): Replace with `GALA_SWAP_CHAIN_VERTICAL_SYNC`.
   // Also expose `GALA_SWAP_CHAIN_TEAR_ON_MISS`.

  /// Refresh rate.
  ///
  /// \note To refresh as fast as possible set both the numerator and the
  /// denominator to zero.
  struct {
    gala_uint32_t numerator;
    gala_uint32_t denominator;
  } refresh_rate;

  ///
  gala_uint32_t flags;

  ///
  uintptr_t surface;
} gala_swap_chain_desc_t;

/// \def GALA_INVALID_SWAP_CHAIN_HANDLE
/// \copydoc GALA_INVALID_RESOURCE_HANDLE
#define GALA_INVALID_SWAP_CHAIN_HANDLE \
  GALA_INVALID_RESOURCE_HANDLE

// Defined in `gala/engine.h`
typedef struct gala_engine gala_engine_t;

// Defined in `gala/command_buffer.h`
typedef struct gala_command_buffer gala_command_buffer_t;

extern GALA_PUBLIC
gala_swap_chain_handle_t gala_swap_chain_create(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  const gala_swap_chain_desc_t *desc);

extern GALA_PUBLIC
void gala_swap_chain_destroy(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  gala_swap_chain_handle_t handle);

extern GALA_PUBLIC
void gala_swap_chain_resize(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  gala_swap_chain_handle_t handle,
  gala_uint32_t width,
  gala_uint32_t height);

GALA_END_EXTERN_C

#endif // _GALA_RESOURCES_SWAP_CHAIN_H_
