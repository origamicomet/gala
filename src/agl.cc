/*
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org/>
 */

#include <agl.h>
#include <agl.private.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ==========================================================================
    Errors (agl_error_t):
   ========================================================================== */

static agl_error_handler_fn _agl_error_handler = NULL;

agl_error_handler_fn agl_error_handler()
{
  return _agl_error_handler;
}

void agl_set_error_handler(
  agl_error_handler_fn handler)
{
  agl_assert(debug, handler != NULL);
  _agl_error_handler = handler;
}

/* ========================================================================== */

void agl_error(
  const agl_err_t error)
{
  agl_assert(debug, _agl_error_handler != NULL);
  _agl_error_handler(error);
  raise(SIGABRT);
}

/* ==========================================================================
    Requests (agl_request_t):
   ========================================================================== */

/* ... */

/* ==========================================================================
    Command Lists (agl_command_list_t):
   ========================================================================== */

agl_command_t *agl_command_list_enqueue(
  agl_command_list_t *command_list,
  const size_t command_len)
{
  agl_assert(paranoid, command_list != NULL);
  while ((command_list->end - command_list->current) < command_len) {
    if (!command_list->exhausted(command_list))
      agl_error(AGL_EOUTOFMEMORY); }
  agl_command_t *cmd = (agl_command_t *)command_list->current;
  command_list->current += command_len;
  return cmd;
}

const agl_command_t *agl_command_list_dequeue(
  const agl_command_list_t *command_list,
  const agl_command_t *cmd)
{
  agl_assert(paranoid, command_list != NULL);
  agl_assert(paranoid, (((uintptr_t)cmd) >= command_list->begin) || (cmd == NULL));
  agl_assert(paranoid, (((uintptr_t)cmd) <= command_list->current) || (cmd == NULL));
  if (cmd == NULL)
    return NULL;
  uintptr_t cmd_ = ((uintptr_t)cmd) + agl_command_length_from_type(cmd->type);
  return ((cmd_ == command_list->current) ? NULL : (const agl_command_t *)cmd_);
}

/* ==========================================================================
    Resources (agl_resource_t):
   ========================================================================== */

agl_resource_t *agl_resource_create(
  const agl_resource_type_t type)
{
  agl_assert(paranoid, type != AGL_RESOURCE_TYPE_UNKNOWN);
  agl_resource_t *resource = (agl_resource_t *)malloc(sizeof(agl_resource_t));
  resource->_type = type;
  resource->_ops = 1;
  resource->_internal = ((uintptr_t)NULL);
  return resource;
}

void agl_resource_destroy(
  agl_resource_t *resource)
{
  agl_assert(paranoid, resource != NULL);
  free((void *)resource);
}

/* ========================================================================== */

void agl_resource_queue_for_create(
  agl_resource_t *resource,
  agl_command_list_t *cmds)
{
  agl_assert(paranoid, resource != NULL);
  agl_assert(paranoid, cmds != NULL);
  agl_atomic_incr(&resource->_ops);
  agl_resource_create_cmd_t *cmd = (agl_resource_create_cmd_t *)
    agl_command_list_enqueue(cmds, sizeof(agl_resource_create_cmd_t));
  cmd->cmd.type = AGL_COMMAND_TYPE_RESOURCE_CREATE;
  cmd->resource = resource;
}

void agl_resource_queue_for_destroy(
  agl_resource_t *resource,
  agl_command_list_t *cmds)
{
  agl_assert(paranoid, resource != NULL);
  agl_assert(paranoid, cmds != NULL);
  agl_atomic_incr(&resource->_ops);
  agl_resource_destroy_cmd_t *cmd = (agl_resource_destroy_cmd_t *)
    agl_command_list_enqueue(cmds, sizeof(agl_resource_destroy_cmd_t));
  cmd->cmd.type = AGL_COMMAND_TYPE_RESOURCE_DESTROY;
  cmd->resource = resource;
}

/* ========================================================================== */

agl_resource_type_t agl_resource_type(
  const agl_resource_t *resource)
{
  agl_assert(debug, resource != NULL);
  return resource->_type;
}

uint agl_resource_ops(
  const agl_resource_t *resource)
{
  agl_assert(debug, resource != NULL);
  return resource->_ops;
}

/* ========================================================================== */

bool agl_resource_is_available(
  const agl_resource_t *resource)
{
  agl_assert(debug, resource != NULL);
  return (agl_atomic_compr_and_swap_ptr(
    (volatile uintptr_t *)&resource->_internal,
    ((uintptr_t)NULL), ((uintptr_t)NULL)
  ) != ((uintptr_t)NULL));
}

bool agl_resource_is_reflective(
  const agl_resource_t *resource)
{
  agl_assert(debug, resource != NULL);
  return (agl_atomic_compr_and_swap_ptr(
    (volatile uint *)&resource->_ops,
    0, 0
  ) == 0);
}

bool agl_resource_is_available(
  const agl_resource_t *resource)
{
  if (!resource)
    return false;
  return false;
}

/* ==========================================================================
    Commands (agl_command_t):
   ========================================================================== */

size_t agl_command_length_from_type(
  const agl_command_type_t type)
{
  switch (type) {
    case AGL_COMMAND_TYPE_RESOURCE_CREATE: return sizeof(agl_resource_create_cmd_t);
    case AGL_COMMAND_TYPE_RESOURCE_DESTROY: return sizeof(agl_resource_destroy_cmd_t);
  agl_error(AGL_EUNKNOWN);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
