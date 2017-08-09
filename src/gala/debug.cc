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

void gala_push_annotation(
  gala_command_buffer_t *command_buffer,
  const char *label,
  gala_uint32_t color)
{
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(label != NULL);

  gala_push_annotation_command_t *cmd =
    (gala_push_annotation_command_t *)gala_command_buffer_allocate(
      command_buffer, sizeof(gala_push_annotation_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_PUSH_ANNOTATION;
  cmd->command.header.size = sizeof(gala_push_annotation_command_t);

  strncpy(&cmd->label[0], label, 256);

  cmd->color = color;
}

void gala_pop_annotation(
  gala_command_buffer_t *command_buffer)
{
  gala_assert_debug(command_buffer != NULL);

  gala_pop_annotation_command_t *cmd =
    (gala_pop_annotation_command_t *)gala_command_buffer_allocate(
      command_buffer, sizeof(gala_pop_annotation_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_POP_ANNOTATION;
  cmd->command.header.size = sizeof(gala_pop_annotation_command_t);
}

void gala_label(
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
