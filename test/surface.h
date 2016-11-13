//===-- test/surface.h ----------------------------------*- mode: C++11 -*-===//
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

#ifndef _GALA_TEST_SURFACE_H_
#define _GALA_TEST_SURFACE_H_

#include "gala/foundation.h"

namespace gala {
namespace test {

class Surface {
 Surface (const Surface &);
 Surface &operator= (const Surface &);

 private:
  Surface();
  ~Surface();

 public:
  struct Description {
    const char *title;
    struct {
      gala_uint32_t width;
      gala_uint32_t height;
    } dimensions;
  };

 public:
  static Surface *create(const Surface::Description &desc);
  void destroy();

 public:
  struct Event {
  };

  void update(void (*event_handler)(const Event *event, void *ctx),
              void *event_handler_ctx = NULL);

 public:
  void dimensions(gala_uint32_t *width, gala_uint32_t *height) const;
  void resize(gala_uint32_t new_width, gala_uint32_t new_height);

 public:
  uintptr_t to_native_hndl() const;

 private:
  uintptr_t native_hndl_;
};

} // test
} // gala

#endif // _GALA_TEST_SURFACE_H_
