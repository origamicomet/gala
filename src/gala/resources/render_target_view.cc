//===-- gala/resources/render_target_view.cc ------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//

#include "gala/resources/render_target_view.h"

#include "gala/engine.h"
#include "gala/commands.h"

GALA_BEGIN_EXTERN_C

gala_render_target_view_handle_t gala_render_target_view_create(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  const gala_render_target_view_desc_t *desc)
{
  gala_assert_debug(engine != NULL);
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(desc != NULL);

  gala_create_render_target_view_command_t *cmd = (gala_create_render_target_view_command_t *)gala_command_buffer_allocate(command_buffer, sizeof(gala_create_render_target_view_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_CREATE_RENDER_TARGET_VIEW;
  cmd->command.header.size = sizeof(gala_create_render_target_view_command);

  // REFACTOR(mtwilliams): This allocation dance.
  gala_render_target_view_handle_t render_target_view_handle = gala_resource_table_allocate(engine->resource_table);
  gala_resource_t *render_target_view = gala_resource_table_lookup(engine->resource_table, render_target_view_handle);

  render_target_view->type = GALA_RESOURCE_TYPE_RENDER_TARGET_VIEW;
  render_target_view->meta = 0;
  render_target_view->internal = 0;

  cmd->render_target_view_handle = render_target_view_handle;

  gala_assert_debug((desc->dimensionality == GALA_ONE_DIMENSIONAL) ||
                    (desc->dimensionality == GALA_TWO_DIMENSIONAL));

  memcpy((void *)&cmd->desc, (const void *)desc, sizeof(gala_render_target_view_desc_t));

  return render_target_view_handle;
}

void gala_render_target_view_destroy(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  gala_render_target_view_handle_t handle)
{
  gala_assert_debug(engine != NULL);
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(handle != GALA_INVALID_RENDER_TARGET_VIEW_HANDLE);

  gala_destroy_render_target_view_command_t *cmd =
    (gala_destroy_render_target_view_command_t *)gala_command_buffer_allocate(command_buffer, sizeof(gala_destroy_render_target_view_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_DESTROY_RENDER_TARGET_VIEW;
  cmd->command.header.size = sizeof(gala_destroy_render_target_view_command);

  cmd->render_target_view_handle = handle;
}

GALA_END_EXTERN_C
