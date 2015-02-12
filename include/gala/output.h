//===-- gala/output.h -------------------------------------------*- C++ -*-===//
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

#ifndef _GALA_OUTPUT_H_
#define _GALA_OUTPUT_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"
#include "gala/error.h"

//===----------------------------------------------------------------------===//

#include "gala/output_mode.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_output {
  /// TODO(mike): Document this.
  bool primary;
  /// TODO(mike): Document this.
  struct {
    int32_t top, left, bottom, right;
  } bounds;
  /// TODO(mike): Document this.
  size_t num_modes;
  /// TODO(mike): Document this.
  const gala_output_mode_t * const *modes;
} gala_output_t;

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
gala_error_t gala_output_to_s(
  const gala_output_t *output,
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

/// \copydoc ::gala_aoutputr_t
class Output {
 public:
  /// \copydoc ::gala_output_to_s
  ::gala::Error to_s(
    char *buf,
    const size_t buf_sz,
    const ::gala::ErrorDetails **error_details = NULL) const
  {
    return (::gala::Error)::gala_output_to_s(&__output__,
                                              buf, buf_sz,
                                              (const ::gala_error_details_t **)error_details);
  }

 public:
  /// \copydoc ::gala_output_t::primary
  bool primary() const {
    return __output__.primary;
  }

  /// \copydoc ::gala_output_t::bounds
  void bounds(int32_t *top, int32_t *left, int32_t *bottom, int32_t *right) const {
    *top = __output__.bounds.top;
    *left = __output__.bounds.left;
    *bottom = __output__.bounds.bottom;
    *right = __output__.bounds.right;
  }

  /// \copydoc ::gala_output_t::modes
  const ::gala::OutputMode * const *modes() const {
    return (const ::gala::OutputMode * const *)__output__.modes;
  }

  /// \copydoc ::gala_output_t::num_modes
  size_t num_modes() const {
    return __output__.num_modes;
  }

 public:
  ::gala_output_t __output__;
};

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_OUTPUT_H_

//============================================================================//
