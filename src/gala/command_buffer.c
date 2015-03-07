/*===-- gala/command_buffer.c -----------------------------------*- C++ -*-===*/
/*
 *  Gala
 *
 *  This file is distributed under the terms described in LICENSE.
 *
 *  Author(s):
 *
 *    * Michael Williams <mike@origamicomet.com>
 *                                                                            */
/*===----------------------------------------------------------------------===*/

#include "gala/command_buffer.h"

/*===----------------------------------------------------------------------===*/

#include "gala/commands.h"

/*============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*===----------------------------------------------------------------------===*/

static GALA_LOCAL bool
_assert_on_exhaustion(
  struct gala_command_buffer *command_buffer)
{
  gala_assert_debug(command_buffer != NULL);
  gala_assertf_always("The command-buffer %.16" PRIxPTR " was never initialized!", command_buffer);
  /* TODO(mtwilliams): Mark as no return. */
  return false;
}

void
gala_command_buffer_init(
  struct gala_command_buffer *command_buffer)
{
  gala_assert_debug(command_buffer != NULL);
  command_buffer->start = (uintptr_t)NULL;
  command_buffer->end = (uintptr_t)NULL;
  command_buffer->current = (uintptr_t)NULL;
  command_buffer->exhausted = &_assert_on_exhaustion;
}

/*===----------------------------------------------------------------------===*/

void *
gala_command_buffer_insert_yielded(
  struct gala_command_buffer *command_buffer,
  const size_t command_len)
{
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(command_len >= sizeof(struct gala_command));
  do {
    const uintptr_t room = command_buffer->end - command_buffer->current;
    if (command_len <= room) {
      void *command = (void *)command_buffer->current;
      command_buffer->current += command_len;
      return command;
    }
  } while(command_buffer->exhausted(command_buffer));
  gala_assertf_always("The command-buffer %.16" PRIxPTR " was unable to accomodate a command!");
  /* TODO(mtwilliams): Mark as no return. */
  return (void *)NULL;
}

void
gala_command_buffer_insert_yielded_finish(
  struct gala_command_buffer *command_buffer,
  void *command)
{
  gala_assert_debug(command_buffer != NULL);
  gala_assert(command != NULL);
  /* Does nothing, for now. */
}

/*===----------------------------------------------------------------------===*/

void
gala_command_buffer_insert_nop(
  struct gala_command_buffer *command_buffer)
{
  gala_assert_debug(command_buffer != NULL);
  gala_command_nop_t *cmd =
    (gala_command_nop_t *)gala_command_buffer_insert_yielded(command_buffer, sizeof(gala_command_nop_t));
  cmd->__command__.type = GALA_COMMAND_TYPE_NOP;
  cmd->__command__.len = sizeof(gala_command_nop_t);
  gala_command_buffer_insert_yielded_finish(command_buffer, (void *)cmd);
}

/*===----------------------------------------------------------------------===*/

void
gala_command_buffer_insert_fence_on_submission(
  struct gala_command_buffer *command_buffer,
  gala_fence_t fence,
  gala_fence_t *writeback)
{
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(fence != GALA_INVALID_FENCE);
  gala_assert_debug(writeback != NULL);
  gala_command_fence_t *cmd =
    (gala_command_fence_t *)gala_command_buffer_insert_yielded(command_buffer, sizeof(gala_command_fence_t));
  cmd->__command__.type = GALA_COMMAND_TYPE_FENCE_ON_SUBMISSION;
  cmd->__command__.len = sizeof(gala_command_fence_t);
  cmd->fence = fence;
  cmd->writeback = writeback;
  gala_command_buffer_insert_yielded_finish(command_buffer, (void *)cmd);
}

/*===----------------------------------------------------------------------===*/

void
gala_command_buffer_insert_fence_on_completion(
  struct gala_command_buffer *command_buffer,
  gala_fence_t fence,
  gala_fence_t *writeback)
{
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(fence != GALA_INVALID_FENCE);
  gala_assert_debug(writeback != NULL);
  gala_command_fence_t *cmd =
    (gala_command_fence_t *)gala_command_buffer_insert_yielded(command_buffer, sizeof(gala_command_fence_t));
  cmd->__command__.type = GALA_COMMAND_TYPE_FENCE_ON_COMPLETION;
  cmd->__command__.len = sizeof(gala_command_fence_t);
  cmd->fence = fence;
  cmd->writeback = writeback;
  gala_command_buffer_insert_yielded_finish(command_buffer, (void *)cmd);
}

/*===----------------------------------------------------------------------===*/

#ifdef __cplusplus
}
#endif // __cplusplus

/*============================================================================*/

#ifdef __cplusplus

/*===----------------------------------------------------------------------===*/

namespace gala {

/*===----------------------------------------------------------------------===*/

CommandBuffer::CommandBuffer() {
  ::gala_command_buffer_init(&this->__command_buffer__);

  struct __Proxy__ {
    static bool exhausted(::gala_command_buffer_t *command_buffer) {
      const size_t offs = offsetof(CommandBuffer, __command_buffer__);
      return ((::gala::CommandBuffer *)(((uintptr_t)command_buffer) - offs))->exhausted();
    }
  };

  this->__command_buffer__.exhausted = &__Proxy__::exhausted;
}

/*===----------------------------------------------------------------------===*/

CommandBuffer::~CommandBuffer() {
}

/*===----------------------------------------------------------------------===*/

bool CommandBuffer::exhausted() {
  gala_assertf_always("The command-buffer %.16" PRIxPTR " was exhausted!", this);
  /* TODO(mtwilliams): Mark as no return. */
  return false;
}

/*===----------------------------------------------------------------------===*/

void CommandBuffer::insert_nop() {
  ::gala_command_buffer_insert_nop(&this->__command_buffer__);
}

/*===----------------------------------------------------------------------===*/

void CommandBuffer::insert_fence_on_submission(
  ::gala::Fence fence, ::gala::Fence *writeback)
{
  ::gala_command_buffer_insert_fence_on_submission(&this->__command_buffer__,
                                                   (::gala_fence_t)fence,
                                                   (::gala_fence_t *)writeback);
}

/*===----------------------------------------------------------------------===*/

void CommandBuffer::insert_fence_on_completion(
  ::gala::Fence fence, ::gala::Fence *writeback)
{
  ::gala_command_buffer_insert_fence_on_completion(&this->__command_buffer__,
                                                   (::gala_fence_t)fence,
                                                   (::gala_fence_t *)writeback);
}

/*===----------------------------------------------------------------------===*/

} // gala

/*===----------------------------------------------------------------------===*/

#endif // __cplusplus

/*============================================================================*/
