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
  GALA_SWAP_CHAIN_FULLSCREEN = (1 << 0)
} gala_swap_chain_flags_t;

typedef struct gala_swap_chain_desc {
  /// Back buffer format.
  gala_pixel_format_t format;

  /// \defgroup Dimensions */
  /// @{
  uint32_t width;
  uint32_t height;
  /// @}

  // TODO(mtwilliams): Refactor into `gala_rational_t`?

  /// Refresh rate.
  ///
  /// \note To refresh as fast as possible set both the numerator and the
  /// denominator to zero.
  struct {
    uint32_t numerator;
    uint32_t denominator;
  } refresh_rate;

  ///
  uint32_t flags;

  ///
  uintptr_t surface;
} gala_swap_chain_desc_t;

/// \def GALA_INVALID_SWAP_CHAIN_HANDLE
/// \copydoc GALA_INVALID_RESOURCE_HANDLE
#define GALA_INVALID_SWAP_CHAIN_HANDLE \
  GALA_INVALID_RESOURCE_HANDLE

GALA_END_EXTERN_C

#endif // _GALA_RESOURCES_SWAP_CHAIN_H_
