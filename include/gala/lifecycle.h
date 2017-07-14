//===-- gala/lifecycle.h --------------------------------*- mode: C++11 -*-===//
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

#ifndef _GALA_LIFECYCLE_H_
#define _GALA_LIFECYCLE_H_

#include "gala/foundation.h"

GALA_BEGIN_EXTERN_C

/// Statistics collected each frame.
typedef struct gala_statistics {
  /// Monotonically increasing frame identifier.
  gala_uint64_t id;

  /// Nanoseconds it took to specify all commands.
  gala_uint64_t build;

  /// Nanoseconds it took to submit all commands.
  gala_uint64_t submission;

  struct {
    /// Number of writes made to buffers this frame.
    gala_uint64_t writes;
    /// Times buffers were flushed (whole or in part) this frame.
    gala_uint64_t flushes;
  } buffers;
} gala_statistics_t;

// Defined in `gala/engine.h`
typedef struct gala_engine gala_engine_t;

// Defined in `gala/command_buffer.h`
typedef struct gala_command_buffer gala_command_buffer_t;

extern GALA_PUBLIC
void gala_start_of_frame(
  gala_command_buffer_t *command_buffer);

extern GALA_PUBLIC
void gala_end_of_frame(
  gala_command_buffer_t *command_buffer,
  gala_statistics_t *statistics);

GALA_END_EXTERN_C

#endif // _GALA_LIFECYCLE_H_
