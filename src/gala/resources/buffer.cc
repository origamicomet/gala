//===-- gala/resources/buffer.cc ------------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//

#include "gala/resources/buffer.h"

#include "gala/engine.h"
#include "gala/commands.h"

GALA_BEGIN_EXTERN_C

gala_buffer_handle_t gala_buffer_create(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  gala_mutability_t mutability,
  gala_buffer_type_t type,
  gala_uint32_t size,
  const void *data)
{
  gala_assert_debug(engine != NULL);
  gala_assert_debug(command_buffer != NULL);

  gala_create_buffer_command_t *cmd =
    (gala_create_buffer_command_t *)
      gala_command_buffer_allocate(command_buffer,
                                   sizeof(gala_create_buffer_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_CREATE_BUFFER;
  cmd->command.header.size = sizeof(gala_create_buffer_command_t);

  // REFACTOR(mtwilliams): This allocation dance.
  gala_buffer_handle_t buffer_handle = gala_resource_table_allocate(engine->resource_table);
  gala_resource_t *buffer = gala_resource_table_lookup(engine->resource_table, buffer_handle);

  if (type == GALA_INDEX_BUFFER)
    buffer->type = GALA_RESOURCE_TYPE_INDEX_BUFFER;
  if (type == GALA_VERTEX_BUFFER)
    buffer->type = GALA_RESOURCE_TYPE_VERTEX_BUFFER;
  if (type == GALA_CONSTANT_BUFFER)
    buffer->type = GALA_RESOURCE_TYPE_CONSTANT_BUFFER;

  gala_assert_debug(buffer->type != GALA_RESOURCE_TYPE_UNKNOWN);

  buffer->meta = 0;
  buffer->internal = 0;

  cmd->buffer_handle = buffer_handle;

  gala_assert_debug((mutability == GALA_IMMUTABLE) ||
                    (mutability == GALA_DYNAMIC));

  cmd->mutability = mutability;

  if (mutability == GALA_IMMUTABLE)
    gala_assert_debug(data != NULL);

  cmd->size = size;
  cmd->data = data;

  return buffer_handle;
}

void gala_buffer_destroy(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  gala_buffer_handle_t handle)
{
  gala_assert_debug(engine != NULL);
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(handle != GALA_INVALID_BUFFER_HANDLE);

  gala_destroy_buffer_command_t *cmd =
    (gala_destroy_buffer_command_t *)
      gala_command_buffer_allocate(command_buffer,
                                   sizeof(gala_destroy_buffer_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_DESTROY_BUFFER;
  cmd->command.header.size = sizeof(gala_destroy_buffer_command);

  cmd->buffer_handle = handle;
}

void gala_buffer_update(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  gala_buffer_handle_t buffer,
  gala_uint32_t offset,
  gala_uint32_t length,
  const void *data)
{
  gala_assert_debug(engine != NULL);
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(buffer != GALA_INVALID_BUFFER_HANDLE);
  gala_assert_debug(data != NULL);

  gala_write_to_buffer_command_t *cmd =
    (gala_write_to_buffer_command_t *)
      gala_command_buffer_allocate(command_buffer,
                                   sizeof(gala_write_to_buffer_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_WRITE_TO_BUFFER;
  cmd->command.header.size = sizeof(gala_write_to_buffer_command_t);

  cmd->buffer_handle = buffer;

  cmd->offset = offset;
  cmd->length = length;
  cmd->data = data;
}

GALA_END_EXTERN_C
