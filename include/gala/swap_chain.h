//===-- gala/swap_chain.h ---------------------------------------*- C++ -*-===//
//
//  Gala
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//    * Michael Williams <mike@origamicomet.com>
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief TODO(mike): Document this file.
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_SWAP_CHAIN_H_
#define _GALA_SWAP_CHAIN_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"
#include "gala/error.h"

//===----------------------------------------------------------------------===//

#include "gala/pixel_format.h"

//===----------------------------------------------------------------------===//

#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_swap_chain_opts {
  ///
  gala_pixel_format_t format;
  ///
  /// @{
  uint32_t width;
  uint32_t height;
  /// @}
  struct {
    ///
    uint32_t numer;
    ///
    uint32_t denom;
  } refresh_rate;
  ///
  bool fullscreen;
  ///
  bool vsync;
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  ///
  HWND hWnd;
#endif
} gala_swap_chain_opts_t;

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_swap_chain {
  /// The backend this belongs to.
  struct gala_backend *_backend;
} gala_swap_chain_t;

//===----------------------------------------------------------------------===//

/// \brief
/// \param swap_chain
/// \param buf
/// \param buf_sz
/// \param error_details
/// \returns
///
extern
GALA_PUBLIC
gala_error_t gala_swap_chain_to_s(
  const gala_swap_chain_t *swap_chain,
  char *buf,
  const size_t buf_sz,
  const gala_error_details_t **error_details);

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace gala {

//===----------------------------------------------------------------------===//

/// \copydoc ::gala_swap_chain_t
class SwapChain {
 public:
  /// \copydoc ::gala_swap_chain_to_s
  ::gala::Error to_s(
    char *buf,
    const size_t buf_sz,
    const ::gala::ErrorDetails **error_details = NULL) const
  {
    return (::gala::Error)::gala_swap_chain_to_s(&__swap_chain__,
                                                 buf, buf_sz,
                                                 (const ::gala_error_details_t **)error_details);
  }

 public:
  ::gala_swap_chain_t __swap_chain__;
};

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_SWAP_CHAIN_H_

//============================================================================//
