//===-- gala/command_buffer.cc --------------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//

#include "gala/command_buffer.h"

#include "gala/command.h"

GALA_BEGIN_EXTERN_C

static GALA_LOCAL
bool _assert_on_exhaustion(
  gala_command_buffer_t *command_buffer)
{
  gala_assert_debug(command_buffer != NULL);
  gala_assertf(0, "The command-buffer %.16" PRIxPTR " was never initialized!", command_buffer);
  return false;
}

void gala_command_buffer_init(
  gala_command_buffer_t *command_buffer)
{
  gala_assert_debug(command_buffer != NULL);

  command_buffer->start = (uintptr_t)NULL;
  command_buffer->end = (uintptr_t)NULL;
  command_buffer->current = (uintptr_t)NULL;

  command_buffer->exhausted = &_assert_on_exhaustion;
}

void *gala_command_buffer_allocate(
  gala_command_buffer_t *command_buffer,
  const size_t sz)
{
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(sz >= sizeof(gala_command_t));

  do {
    const size_t room = command_buffer->end - command_buffer->current;
    if (sz <= room) {
      void *command = (void *)command_buffer->current;
      command_buffer->current += sz;
      return command;
    }
  } while (command_buffer->exhausted(command_buffer));

  gala_assertf(0, "The command-buffer %.16" PRIxPTR " was unable to accommodate a command!", command_buffer);
  return (void *)NULL;
}

GALA_END_EXTERN_C

#ifdef __cplusplus
namespace gala {

CommandBuffer::CommandBuffer() {
  ::gala_command_buffer_init(&__command_buffer__);

  struct Proxy {
    static bool exhausted(::gala_command_buffer_t *faux_command_buffer) {
      // Reconstruct pointer to `this` with black magicks.
      const size_t offset = offsetof(CommandBuffer, __command_buffer__);
      CommandBuffer *command_buffer = (CommandBuffer *)((uintptr_t)faux_command_buffer - offset);
      return command_buffer->exhausted();
    }
  };

  __command_buffer__.exhausted = &Proxy::exhausted;
}

CommandBuffer::~CommandBuffer() {
}

bool CommandBuffer::exhausted() {
  gala_assertf(0, "You didn't override CommandBuffer::exhausted!", this);
  return false;
}

} // gala
#endif // __cplusplus
