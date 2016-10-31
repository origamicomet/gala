//===-- gala/fence.cc -----------------------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//

#include "gala/fence.h"

#include "gala/commands.h"

GALA_BEGIN_EXTERN_C

// REFACTOR(mtwilliams): Common logic.

void gala_fence_on_submission(
  gala_command_buffer_t *command_buffer,
  gala_fence_t *fence,
  gala_fence_t writeback)
{
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(fence != NULL);

  gala_fence_command_t *cmd = (gala_fence_command_t *)gala_command_buffer_allocate(command_buffer, sizeof(gala_fence_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_FENCE_ON_SUBMISSION;
  cmd->command.header.size = sizeof(gala_fence_command_t);

  cmd->fence = fence;
  cmd->writeback = writeback;
}

void gala_fence_on_completion(
  gala_command_buffer_t *command_buffer,
  gala_fence_t *fence,
  gala_fence_t writeback)
{
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(fence != NULL);

  gala_fence_command_t *cmd = (gala_fence_command_t *)gala_command_buffer_allocate(command_buffer, sizeof(gala_fence_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_FENCE_ON_COMPLETION;
  cmd->command.header.size = sizeof(gala_fence_command_t);

  cmd->fence = fence;
  cmd->writeback = writeback;
}

GALA_END_EXTERN_C
