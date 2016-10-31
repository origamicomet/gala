//===-- gala/resources/swap_chain.cc --------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//

#include "gala/resources/swap_chain.h"

#include "gala/engine.h"
#include "gala/commands.h"

GALA_BEGIN_EXTERN_C

gala_swap_chain_handle_t gala_swap_chain_create(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  const gala_swap_chain_desc_t *desc)
{
  gala_assert_debug(engine != NULL);
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(desc != NULL);

  gala_create_swap_chain_command_t *cmd = (gala_create_swap_chain_command_t *)gala_command_buffer_allocate(command_buffer, sizeof(gala_create_swap_chain_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_CREATE_SWAP_CHAIN;
  cmd->command.header.size = sizeof(gala_create_swap_chain_command);

  // REFACTOR(mtwilliams): This allocation dance.
  gala_swap_chain_handle_t swap_chain_handle = gala_resource_table_allocate(engine->resource_table);
  gala_resource_t *swap_chain = gala_resource_table_lookup(engine->resource_table, swap_chain_handle);

  swap_chain->type = GALA_RESOURCE_TYPE_SWAP_CHAIN;
  swap_chain->meta = 0;
  swap_chain->internal = 0;

  cmd->swap_chain_handle = swap_chain_handle;
  memcpy((void *)&cmd->desc, (const void *)desc, sizeof(gala_swap_chain_desc_t));

  return swap_chain_handle;
}

void gala_swap_chain_destroy(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  gala_swap_chain_handle_t handle)
{
  gala_assert_debug(engine != NULL);
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(handle != GALA_INVALID_SWAP_CHAIN_HANDLE);

  gala_destroy_swap_chain_command_t *cmd =
    (gala_destroy_swap_chain_command_t *)gala_command_buffer_allocate(command_buffer, sizeof(gala_destroy_swap_chain_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_DESTROY_SWAP_CHAIN;
  cmd->command.header.size = sizeof(gala_destroy_swap_chain_command);

  cmd->swap_chain_handle = handle;
}

void gala_swap_chain_resize(
  gala_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  gala_swap_chain_handle_t handle,
  gala_uint32_t width,
  gala_uint32_t height)
{
  gala_assert_debug(engine != NULL);
  gala_assert_debug(command_buffer != NULL);
  gala_assert_debug(handle != GALA_INVALID_SWAP_CHAIN_HANDLE);
  gala_assert_debug((width >= 1) && (height >= 1));

  gala_resize_swap_chain_command_t *cmd =
    (gala_resize_swap_chain_command_t *)gala_command_buffer_allocate(command_buffer, sizeof(gala_resize_swap_chain_command_t));

  cmd->command.header.type = GALA_COMMAND_TYPE_DESTROY_SWAP_CHAIN;
  cmd->command.header.size = sizeof(gala_destroy_swap_chain_command);

  cmd->swap_chain_handle = handle;
  cmd->width = width;
  cmd->height = height;
}

GALA_END_EXTERN_C
