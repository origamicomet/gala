//===-- gala/wgl.h --------------------------------------*- mode: C++11 -*-===//
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

#ifndef _GALA_WGL_H_
#define _GALA_WGL_H_

#include "gala/foundation.h"

#include "gala/pixel_format.h"

#if GALA_ENABLE_OPENGL
#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS

GALA_BEGIN_EXTERN_C

// Defined in `gala/wgl.cc`.
typedef struct gala_wgl_context gala_wgl_context_t;

extern GALA_LOCAL
void gala_wgl_init(void);

extern GALA_LOCAL
void gala_wgl_shutdown(void);

extern GALA_LOCAL
void *gala_wgl_get_proc_address(
  const char *name);

typedef enum gala_wgl_context_flags {
  /// Request debug context and enable debugging functionality.
  GALA_WGL_CONTEXT_DEBUG = (1 << 0),
  /// Request hardware acceleration.
  GALA_WGL_CONTEXT_ACCELERATED = (1 << 0),
} gala_wgl_context_flags_t;

typedef struct gala_wgl_context_creation_params {
  // REFACTOR(mtwilliams): Expose back-buffer format?
  // gala_pixel_format_t format;

  /// Minimum required context version.
  struct {
    gala_uint32_t major;
    gala_uint32_t minor;
  } version;

  gala_uint32_t flags;

  /// Context to share resources with.
  gala_wgl_context_t *share;
} gala_wgl_context_creation_params_t;

extern GALA_LOCAL
gala_wgl_context_t *gala_wgl_create_context(
  const gala_wgl_context_creation_params_t *context_creation_params);

extern GALA_LOCAL
void gala_wgl_destroy_context(
  gala_wgl_context_t *context);

// Defined in `gala/wgl.cc`.
typedef struct gala_wgl_surface gala_wgl_surface_t;

typedef enum gala_wgl_surface_flags {
  /// Fullscreen.
  GALA_WGL_SURFACE_FULLSCREEN = (1 << 0),
  /// Borderless if fullscreen.
  GALA_WGL_SURFACE_BORDERLESS = (1 << 1)
} gala_wgl_surface_flags_t;

extern GALA_LOCAL
gala_wgl_surface_t *gala_wgl_create_surface(
  gala_wgl_context_t *context,
  uintptr_t window,
  gala_uint32_t flags);

extern GALA_LOCAL
void gala_wgl_destroy_surface(
  gala_wgl_surface_t *surface);

extern GALA_LOCAL
void gala_wgl_dimensions_of_surface(
  gala_wgl_surface_t *surface,
  gala_uint32_t *width,
  gala_uint32_t *height);

extern GALA_LOCAL
void gala_wgl_bind(
  const gala_wgl_context_t *context,
  const gala_wgl_surface_t *surface);

typedef enum gala_wgl_present_flags {
  /// Synchronize to vertical blanks.
  GALA_WGL_PRESENT_SYNCHRONIZE  = (1 << 0),
  /// Tear if below refresh rate.
  GALA_WGL_PRESENT_TEAR_ON_MISS = (1 << 1)
} gala_wgl_present_flags_t;

extern GALA_LOCAL
void gala_wgl_present(
  gala_uint32_t n,
  gala_wgl_surface_t * const *surfaces,
  gala_uint32_t flags);

GALA_END_EXTERN_C

#endif // GALA_PLATFORM_WINDOWS
#endif // GALA_ENABLE_OPENGL

#endif // _GALA_WGL_H_
