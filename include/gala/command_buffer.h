//===-- gala/command_buffer.h ---------------------------*- mode: C++11 -*-===//
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

#ifndef _GALA_COMMAND_BUFFER_H_
#define _GALA_COMMAND_BUFFER_H_

#include "gala/foundation.h"

GALA_BEGIN_EXTERN_C

/// \brief A user-controlled slice of memory used to queue up commands.
typedef struct gala_command_buffer {
  /// The lowest address of the command-buffer.
  gala_uintptr_t start;

  /// The highest address of the command-buffer.
  gala_uintptr_t end;

  /// The lowest unoccupied address of the command-buffer.
  gala_uintptr_t current;

  /// \brief Called when there is not enough space left in the command buffer
  /// to accommodate a new command.
  ///
  /// \note You don't necessarily have to resize the command-buffer, e.g.
  /// you could start consuming a copy in another thread.
  ///
  /// \param[in] command_buffer The command-buffer that is full.
  ///
  /// \returns A non-zero value if the command-buffer can accommodate the
  /// command; zero if the command-buffer cannot accommodate the command.
  bool (*exhausted)(struct gala_command_buffer *command_buffer);
} gala_command_buffer_t;

/// \brief Initializes a command-buffer to sane and helpful defaults.
/// \param[out] command_buffer The command-buffer to initialize.
extern GALA_PUBLIC
void gala_command_buffer_init(
  gala_command_buffer_t *command_buffer);

/// \brief Allocates the next @sz bytes from @command_buffer.
/// \returns A pointer to the first byte allocated.
extern GALA_PUBLIC
void *gala_command_buffer_allocate(
  gala_command_buffer_t *command_buffer,
  const size_t sz);

GALA_END_EXTERN_C

#ifdef __cplusplus
namespace gala {

/// \copydoc ::gala_command_buffer_t
class GALA_PUBLIC CommandBuffer {
 protected:
  CommandBuffer();
  CommandBuffer(const CommandBuffer &command_buffer);
  CommandBuffer &operator=(const CommandBuffer &command_buffer);
  virtual ~CommandBuffer();

 public:
  /// Returns the underlying ::gala_command_buffer_t.
  ::gala_command_buffer_t *underlying() { return &__command_buffer__; }
  const ::gala_command_buffer_t *underlying() const { return &__command_buffer__; }

 protected:
  /// \copydoc ::gala_command_buffer::exhausted
  virtual bool exhausted();

 private:
  ::gala_command_buffer_t __command_buffer__;
};

} // gala
#endif // __cplusplus

#endif // _GALA_COMMAND_BUFFER_H_
