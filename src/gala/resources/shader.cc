//===-- gala/shader.cc ----------------------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//

#include "gala/resources/shader.h"

#include "gala/engine.h"
#include "gala/commands.h"

GALA_BEGIN_EXTERN_C

static gala_resource_type_t gala_resource_type_for_shader(
  gala_shader_type_t type)
{
  switch (type) {
    case GALA_VERTEX_SHADER: return GALA_RESOURCE_TYPE_VERTEX_SHADER;
    case GALA_PIXEL_SHADER: return GALA_RESOURCE_TYPE_PIXEL_SHADER;
  }

  return GALA_RESOURCE_TYPE_UNKNOWN;
}

gala_shader_handle_t gala_shader_create(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  const gala_shader_desc_t *desc)
{
  gala_assert_debug(engine != NULL);
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(desc != NULL);

  gala_create_shader_command_t *cmd =
    (gala_create_shader_command_t *)
      gala_command_buffer_allocate(command_buffer,
                                   sizeof(gala_create_shader_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_CREATE_SHADER;
  cmd->command.header.size = sizeof(gala_create_shader_command_t);

  // REFACTOR(mtwilliams): This allocation dance.
  gala_shader_handle_t shader_handle = gala_resource_table_allocate(engine->resource_table);
  gala_resource_t *shader = gala_resource_table_lookup(engine->resource_table, shader_handle);

  shader->type = gala_resource_type_for_shader(desc->type);
  shader->meta = 0;
  shader->internal = 0;

  gala_assert_debug(shader->type != GALA_RESOURCE_TYPE_UNKNOWN);

  cmd->shader_handle = shader_handle;

  memcpy((void *)&cmd->desc, (const void *)desc, sizeof(gala_shader_desc_t));

  gala_assert_debug(desc->source != NULL);

  return shader_handle;
}

void gala_shader_destroy(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  gala_shader_handle_t handle)
{
  gala_assert_debug(engine != NULL);
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(handle != GALA_INVALID_SHADER_HANDLE);

  gala_destroy_shader_command_t *cmd =
    (gala_destroy_shader_command_t *)
      gala_command_buffer_allocate(command_buffer,
                                   sizeof(gala_destroy_shader_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_DESTROY_SHADER;
  cmd->command.header.size = sizeof(gala_destroy_shader_command);

  cmd->shader_handle = handle;
}

GALA_END_EXTERN_C
