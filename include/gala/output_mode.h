//===-- gala/output_mode.h --------------------------------------*- C++ -*-===//
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

#ifndef _GALA_OUTPUT_MODE_H_
#define _GALA_OUTPUT_MODE_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"
#include "gala/error.h"
#include "gala/pixel_format.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_output_mode {
  /// The back-buffer's pixel format.
  gala_pixel_format_t format;

  /// \defgroup Dimensions The back-buffer's dimensions.
  /// @{
  uint32_t width;
  uint32_t height;
  /// @}

  /// The screen's refresh-rate as a rational (numer/denom) in hertz.
  struct {
    uint32_t numer;
    uint32_t denom;
  } refresh_rate;
} gala_output_mode_t;

//===----------------------------------------------------------------------===//

/// \brief
/// \param output
/// \param buf
/// \param buf_sz
/// \param error_details
/// \returns
///
extern
GALA_PUBLIC
gala_error_t gala_output_mode_to_s(
  const gala_output_mode_t *output_mode,
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

/// \copydoc ::gala_output_mode_t
class OutputMode {
 public:
  /// \copydoc ::gala_output_mode_to_s
  ::gala::Error to_s(
    char *buf,
    const size_t buf_sz,
    const ::gala::ErrorDetails **error_details = NULL) const
  {
    return (::gala::Error)::gala_output_mode_to_s(&__output_mode__,
                                             buf, buf_sz,
                                             (const ::gala_error_details_t **)error_details);
  }

 public:
  /// \copydoc ::gala_output_mode_t::format
  const ::gala::PixelFormat format() const { return ::gala::PixelFormat(__output_mode__.format); }

  /// \copydoc ::gala_output_mode_t::width
  uint32_t width() const { return __output_mode__.width; }

  /// \copydoc ::gala_output_mode_t::height
  uint32_t height() const { return __output_mode__.height; }

  /// \copydoc ::gala_output_mode_t::refresh_rate
  void refresh_rate(uint32_t *numer, uint32_t *denom) const {
    *numer = __output_mode__.refresh_rate.numer;
    *denom = __output_mode__.refresh_rate.denom;
  }

 public:
  ::gala_output_mode_t __output_mode__;
};

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_OUTPUT_MODE_H_

//============================================================================//
