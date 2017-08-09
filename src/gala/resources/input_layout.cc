//===-- gala/resources/input_layout.cc ------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//

#include "gala/resources/input_layout.h"

#include "gala/engine.h"
#include "gala/commands.h"

GALA_BEGIN_EXTERN_C

gala_input_layout_handle_t gala_input_layout_create(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  const gala_input_layout_desc_t *desc)
{
  gala_assert_debug(engine != NULL);
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(desc != NULL);
  gala_assert_debug(desc->count <= 16);

  gala_create_input_layout_command_t *cmd =
    (gala_create_input_layout_command_t *)
      gala_command_buffer_allocate(command_buffer,
                                   sizeof(gala_create_input_layout_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_CREATE_INPUT_LAYOUT;
  cmd->command.header.size = sizeof(gala_create_input_layout_command_t);

  // REFACTOR(mtwilliams): This allocation dance.
  gala_input_layout_handle_t input_layout_handle = gala_resource_table_allocate(engine->resource_table);
  gala_resource_t *input_layout = gala_resource_table_lookup(engine->resource_table, input_layout_handle);

  input_layout->type = GALA_RESOURCE_TYPE_INPUT_LAYOUT;
  input_layout->meta = 0;
  input_layout->internal = 0;

  cmd->input_layout_handle = input_layout_handle;
  memcpy((void *)&cmd->desc, (const void *)desc, sizeof(gala_input_layout_desc_t));

  return input_layout_handle;
}

void gala_input_layout_destroy(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  gala_input_layout_handle_t handle)
{
  gala_assert_debug(engine != NULL);
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(handle != GALA_INVALID_INPUT_LAYOUT_HANDLE);

  gala_destroy_input_layout_command_t *cmd =
    (gala_destroy_input_layout_command_t *)
      gala_command_buffer_allocate(command_buffer,
                                   sizeof(gala_destroy_input_layout_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_DESTROY_INPUT_LAYOUT;
  cmd->command.header.size = sizeof(gala_destroy_input_layout_command);

  cmd->input_layout_handle = handle;
}

GALA_END_EXTERN_C
