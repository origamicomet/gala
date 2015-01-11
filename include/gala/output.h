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
/// \brief
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_OUTPUT_H_
#define _GALA_OUTPUT_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_output {
  ///
  bool primary;
  ///
  struct {
    int32_t top;
    int32_t left;
    int32_t bottom;
    int32_t right;
  } bounds;
  ///
  size_t num_modes;
  ///
  const struct gala_output_mode **modes;
} gala_output_t;

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_output_mode {
  ///
  uint32_t width;
  ///
  uint32_t height;
  ///
  struct {
    uint32_t numer;
    uint32_t denom;
  } refresh_rate;
  // TODO(mike): Implement.
  // ///
  // gala_pixel_format_t format;
} gala_output_mode_t;

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//===----------------------------------------------------------------------===//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace gala {

//===----------------------------------------------------------------------===//

/// \copydoc ::gala_output_t
class Output
{
 public:
  /// \copydoc ::gala_output_mode_t
  class Mode
  {
   private:
    Mode();
    Mode(const Mode &output_mode);
    Mode &operator=(const Mode &output_mode);
    ~Mode();

   public:
    /// \copydoc ::gala_output_mode_t::width
    const uint32_t width() const { return __output_mode__.width; }

    /// \copydoc ::gala_output_mode_t::height
    const uint32_t height() const { return __output_mode__.height; }

    /// \copydoc ::gala_output_mode_t::refresh_rate
    void refresh_rate(uint32_t *numer,
                      uint32_t *denom) const
    {
      *numer = __output_mode__.refresh_rate.numer;
      *denom = __output_mode__.refresh_rate.denom;
    }

    // TODO(mike): Implement.
    // /// \copydoc ::gala_output_mode_t::format
    // const PixelFormat format() const { return (PixelFormat)__output_mode__.format; }

   private:
    ::gala_output_mode_t __output_mode__;
  };

 private:
  Output();
  Output(const Output &output);
  Output &operator=(const Output &output);
  ~Output();

 public:
  /// \copydoc ::gala_output_t::primary
  const bool primary() const { return __output__.primary; }

  /// \copydoc ::gala_output_t::bounds
  void bounds(uint32_t *top,
              uint32_t *left,
              uint32_t *bottom,
              uint32_t *right) const
  {
    *top = __output__.bounds.top;
    *left = __output__.bounds.left;
    *bottom = __output__.bounds.bottom;
    *right = __output__.bounds.right;
  }

  /// \copydoc ::gala_output_t::num_modes
  const size_t num_modes() const { return __output__.num_modes; }

  /// \copydoc ::gala_output_t::modes
  const ::gala::Output::Mode **modes() const { return (const ::gala::Output::Mode **)__output__.modes; }

 private:
  ::gala_output_t __output__;
};

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_OUTPUT_H_

//============================================================================//
