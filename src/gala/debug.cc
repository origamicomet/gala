//===-- gala/debug.cc -----------------------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//

#include "gala/debug.h"

#include "gala/commands.h"

GALA_BEGIN_EXTERN_C

void gala_debug_label(
  gala_command_buffer_t *command_buffer,
  gala_resource_handle_t handle,
  const char *name)
{
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(handle != GALA_INVALID_RESOURCE_HANDLE);
  gala_assert_debug(name != NULL);

  gala_label_command_t *cmd =
    (gala_label_command_t *)gala_command_buffer_allocate(
      command_buffer, sizeof(gala_label_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_LABEL;
  cmd->command.header.size = sizeof(gala_label_command_t);

  cmd->handle = handle;

  strncpy(&cmd->name[0], name, 256);
}

GALA_END_EXTERN_C
