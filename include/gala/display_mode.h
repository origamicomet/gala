//===-- gala/display_mode.h -------------------------------------*- C++ -*-===//
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

#ifndef _GALA_DISPLAY_MODE_H_
#define _GALA_DISPLAY_MODE_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"

//===----------------------------------------------------------------------===//

#include "gala/pixel_format.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_display_mode {
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

  /// The back-buffer's display format.
  gala_pixel_format_t format;
} gala_display_mode_t;

//===----------------------------------------------------------------------===//

/// \brief
/// \param display_mode
/// \returns
///
extern GALA_PUBLIC void
gala_display_mode_init(
  gala_display_mode_t *display_mode);

//===----------------------------------------------------------------------===//

/// \brief
/// \param display_mode
///
extern GALA_PUBLIC void
gala_display_mode_destroy(
  gala_display_mode_t *display_mode);

//===----------------------------------------------------------------------===//

/// \brief
/// \param display_mode
/// \param buf
/// \param buf_sz
/// \returns
///
extern GALA_PUBLIC int
gala_display_mode_to_s(
  const gala_display_mode_t *display_mode,
  char buf[],
  const int buf_sz);

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace gala {

//===----------------------------------------------------------------------===//

/// \copydoc ::gala_display_mode_t
class GALA_PUBLIC DisplayMode {
 public:
  /// \copydoc ::gala_display_mode_init
  static void init(::gala::DisplayMode *display_mode);

  /// \copydoc ::gala_display_mode_destroy
  void destroy();

 public:
  /// \copydoc ::gala_display_mode_to_s
  int to_s(char buf[], const int buf_sz) const;

 public:
  ::gala_display_mode_t __display_mode__;
};

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_DISPLAY_MODE_H_

//============================================================================//
