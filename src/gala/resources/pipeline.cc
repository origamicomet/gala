//===-- gala/pipeline.cc --------------------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//

#include "gala/resources/pipeline.h"

#include "gala/engine.h"
#include "gala/commands.h"

GALA_BEGIN_EXTERN_C

gala_pipeline_handle_t gala_pipeline_create(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  const gala_pipeline_desc_t *desc)
{
  gala_assert_debug(engine != NULL);
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(desc != NULL);

  gala_create_pipeline_command_t *cmd =
    (gala_create_pipeline_command_t *)
      gala_command_buffer_allocate(command_buffer,
                                   sizeof(gala_create_pipeline_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_CREATE_PIPELINE;
  cmd->command.header.size = sizeof(gala_create_pipeline_command_t);

  // REFACTOR(mtwilliams): This allocation dance.
  gala_pipeline_handle_t pipeline_handle = gala_resource_table_allocate(engine->resource_table);
  gala_resource_t *pipeline = gala_resource_table_lookup(engine->resource_table, pipeline_handle);

  pipeline->type = GALA_RESOURCE_TYPE_PIPELINE;
  pipeline->meta = 0;
  pipeline->internal = 0;

  cmd->pipeline_handle = pipeline_handle;
  memcpy((void *)&cmd->desc, (const void *)desc, sizeof(gala_pipeline_desc_t));

  return pipeline_handle;
}

void gala_pipeline_destroy(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  gala_pipeline_handle_t handle)
{
  gala_assert_debug(engine != NULL);
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(handle != GALA_INVALID_PIPELINE_HANDLE);

  gala_destroy_pipeline_command_t *cmd =
    (gala_destroy_pipeline_command_t *)
      gala_command_buffer_allocate(command_buffer,
                                   sizeof(gala_destroy_pipeline_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_DESTROY_PIPELINE;
  cmd->command.header.size = sizeof(gala_destroy_pipeline_command);

  cmd->pipeline_handle = handle;
}

GALA_END_EXTERN_C
