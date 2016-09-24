//===-- gala/command.h  ---------------------------------*- mode: C++11 -*-===//
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

#ifndef _GALA_COMMAND_H_
#define _GALA_COMMAND_H_

#include "gala/foundation.h"

GALA_BEGIN_EXTERN_C

typedef enum gala_command_type {
  /// No operation; do nothing.
  GALA_COMMAND_TYPE_NOP = 0,

  // Synchronization

  /// Writes a value when Gala has submitted all previous commands.
  GALA_COMMAND_TYPE_FENCE_ON_SUBMISSION = 1,

  /// Writes a value when the GPU has processed all previous commands.
  /// \warning This can take a substantial amount of time, and may even stall,
  /// with some backends. Use sparingly.
  GALA_COMMAND_TYPE_FENCE_ON_COMPLETION = 2,

  /// \internal Force gala_uint32_t storage and alignment.
  GALA_COMMAND_TYPE_FORCE_UINT32 = 0x7fffffff
} gala_command_type_t;

typedef struct gala_command_header {
  gala_command_type_t type;
  gala_uint32_t size;
} gala_command_header_t;

typedef struct gala_command {
  gala_command_header_t header;
} gala_command_t;

GALA_END_EXTERN_C

#ifdef __cplusplus
namespace gala {

/// \copydoc ::gala_command_t
struct GALA_PUBLIC Command : public ::gala_command_t {
 public:
  /// \copydoc ::gala_command_type_t
  typedef ::gala_command_type_t Type;

  /// \copydoc GALA_COMMAND_TYPE_NOP
  static const Type NOP = ::GALA_COMMAND_TYPE_NOP;
  /// \copydoc GALA_COMMAND_TYPE_FENCE_ON_SUBMISSION
  static const Type ON_SUBMISSION = ::GALA_COMMAND_TYPE_FENCE_ON_SUBMISSION;
  /// \copydoc GALA_COMMAND_TYPE_FENCE_ON_COMPLETION
  static const Type FENCE_ON_COMPLETION = ::GALA_COMMAND_TYPE_FENCE_ON_COMPLETION;

 public:
  /// \copydoc ::gala_command_header_t
  typedef ::gala_command_header_t Header;
};

} // gala
#endif // __cplusplus

#endif // _GALA_COMMAND_H_
