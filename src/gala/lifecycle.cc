//===-- gala/lifecycle.cc -------------------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//

#include "gala/lifecycle.h"

#include "gala/commands.h"

GALA_BEGIN_EXTERN_C

void gala_start_of_frame(
  gala_command_buffer_t *command_buffer)
{
  gala_assert_debug(command_buffer != NULL);

  gala_frame_command_t *cmd =
    (gala_frame_command_t *)gala_command_buffer_allocate(
      command_buffer, sizeof(gala_frame_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_START_OF_FRAME;
  cmd->command.header.size = sizeof(gala_frame_command_t);

  cmd->id = 1;
  cmd->timestamp = 0;
  cmd->statistics = NULL;
}

void gala_end_of_frame(
  gala_command_buffer_t *command_buffer,
  gala_statistics_t *statistics)
{
  gala_assert_debug(command_buffer != NULL);

  gala_frame_command_t *cmd =
    (gala_frame_command_t *)gala_command_buffer_allocate(
      command_buffer, sizeof(gala_frame_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_END_OF_FRAME;
  cmd->command.header.size = sizeof(gala_frame_command_t);

  cmd->id = 1;
  cmd->timestamp = 0;
  cmd->statistics = statistics;
}

GALA_END_EXTERN_C
