//===-- gala/display_mode.c -------------------------------------*- C++ -*-===//
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

#include "gala/display_mode.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

void
gala_display_mode_init(
  gala_display_mode_t *display_mode)
{
  gala_assert_debug(display_mode != NULL);
  display_mode->width = 0;
  display_mode->height = 0;
  display_mode->refresh_rate.numer = 0;
  display_mode->refresh_rate.denom = 0;
  display_mode->format = GALA_PIXEL_FORMAT_INVALID;
}

//===----------------------------------------------------------------------===//

void
gala_display_mode_destroy(
  gala_display_mode_t *display_mode)
{
  gala_assert_debug(display_mode != NULL);
#if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
  // This might help find some (stupid) bugs.
  display_mode->width = 0;
  display_mode->height = 0;
  display_mode->refresh_rate.numer = 0;
  display_mode->refresh_rate.denom = 0;
  display_mode->format = GALA_PIXEL_FORMAT_INVALID;
#endif
}

//===----------------------------------------------------------------------===//

int gala_display_mode_to_s(
  const gala_display_mode_t *display_mode,
  char buf[],
  const int buf_sz)
{
  gala_assert_debug(display_mode != NULL);
  float refresh_rate_in_hz;
  if (display_mode->refresh_rate.denom == 0)
    refresh_rate_in_hz = (float)display_mode->refresh_rate.numer;
  else
    refresh_rate_in_hz = (float)display_mode->refresh_rate.numer / (float)display_mode->refresh_rate.denom;
  return snprintf(buf, buf_sz, "#<gala_display_mode_t:%.16" PRIxPTR " %ux%u@%.2f (%s)>",
                  display_mode, display_mode->width, display_mode->height,
                  refresh_rate_in_hz, gala_pixel_format_to_s(display_mode->format));
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace gala {

//===----------------------------------------------------------------------===//

void DisplayMode::init(::gala::DisplayMode *display_mode) {
  ::gala_display_mode_init(&display_mode->__display_mode__);
}

//===----------------------------------------------------------------------===//

void DisplayMode::destroy() {
  ::gala_display_mode_destroy(&this->__display_mode__);
}

//===----------------------------------------------------------------------===//

int DisplayMode::to_s(char buf[], const int buf_sz) const {
  float refresh_rate_in_hz;
  if (this->__display_mode__.refresh_rate.denom == 0)
    refresh_rate_in_hz = (float)this->__display_mode__.refresh_rate.numer;
  else
    refresh_rate_in_hz = (float)this->__display_mode__.refresh_rate.numer / (float)this->__display_mode__.refresh_rate.denom;
  return snprintf(buf, buf_sz, "#<gala::DisplayMode:%.16" PRIxPTR " %ux%u@%.2f (%s)>",
                  this, this->__display_mode__.width, this->__display_mode__.height,
                  refresh_rate_in_hz, gala_pixel_format_to_s(this->__display_mode__.format));
}

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
