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

/* ========================================================================== */
/*  Integration:                                                              */
/*   * Errors & Error Handling                                                */
/*   * Memory Management                                                      */
/* ========================================================================== */

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
    Allocator (agl_allocator_t):
   ========================================================================== */

static agl_allocator_t *_agl_allocator = NULL;

agl_allocator_t *agl_allocator()
{
  return _agl_allocator;
}

void agl_set_allocator(
  agl_allocator_t *allocator)
{
  agl_assert(debug, allocator != NULL);
  _agl_allocator = allocator;
}

/* ========================================================================== */

void *agl_alloc(const size_t num_of_bytes, const size_t alignment) {
  agl_assert(debug, _agl_allocator != NULL);
  void *ptr = _agl_allocator->alloc(_agl_allocator, num_of_bytes, alignment);
  if (!ptr) agl_error(AGL_EOUTOFMEMORY);
  return ptr;
}

void *agl_realloc(void *ptr, const size_t num_of_bytes, const size_t alignment) {
  agl_assert(debug, _agl_allocator != NULL);
  ptr = _agl_allocator->realloc(_agl_allocator, ptr, num_of_bytes, alignment);
  if (!ptr && (num_of_bytes > 0)) agl_error(AGL_EOUTOFMEMORY);
  return ptr;
}

void agl_free(void *ptr) {
  agl_assert(debug, _agl_allocator != NULL);
  agl_assert(paranoid, ptr != NULL);
  _agl_allocator->free(_agl_allocator, ptr);
}

/* ========================================================================== */
/*  Common/Types:                                                             */
/*   * Pixel Formats                                                          */
/* ========================================================================== */

/* ==========================================================================
    Pixel Formats (agl_pixel_format_t):
   ========================================================================== */

/* ... */

/* ========================================================================== */
/*  Infrastructure:                                                           */
/*   * Adapters                                                               */
/*   * Outputs                                                                */
/*   * Display Modes                                                          */
/* ========================================================================== */

/* ==========================================================================
    Adapters (agl_adapter_t):
   ========================================================================== */

/* ... */

/* ==========================================================================
    Outputs (agl_output_t):
   ========================================================================== */

/* ... */

/* ==========================================================================
    Display Modes (agl_display_mode_t):
   ========================================================================== */

/* ... */

/* ========================================================================== */
/*  Runtime:                                                                  */
/*   * Contexts                                                               */
/*   * Command Lists                                                          */
/*   * Requests                                                               */
/*   * Resources                                                              */
/* ========================================================================== */

/* ==========================================================================
    Contexts (agl_context_t):
   ========================================================================== */

/* ... */

/* ==========================================================================
    Command Lists (agl_command_list_t):
   ========================================================================== */

struct agl_command *agl_command_list_enqueue(
  agl_command_list_t *command_list,
  const size_t command_len)
{
  agl_assert(paranoid, command_list != NULL);
  while ((command_list->end - command_list->current) < command_len) {
    if (!command_list->exhausted(command_list))
      agl_error(AGL_EOUTOFMEMORY); }
  struct agl_command *cmd = (struct agl_command *)command_list->current;
  command_list->current += command_len;
  return cmd;
}

const struct agl_command *agl_command_list_dequeue(
  const agl_command_list_t *command_list,
  const struct agl_command *cmd)
{
  agl_assert(paranoid, command_list != NULL);
  agl_assert(paranoid, (((uintptr_t)cmd) >= command_list->begin) || (cmd == NULL));
  agl_assert(paranoid, (((uintptr_t)cmd) <= command_list->current) || (cmd == NULL));
  if (cmd == NULL)
    return NULL;
  uintptr_t cmd_ = ((uintptr_t)cmd) + agl_command_length(cmd);
  return ((cmd_ == command_list->current) ? NULL : (const struct agl_command *)cmd_);
}

/* ==========================================================================
    Requests (agl_request_t):
   ========================================================================== */

/* ... */

/* ==========================================================================
    Resources (agl_resource_t):
   ========================================================================== */

agl_resource_t *agl_resource_create(
  const agl_resource_type_t type)
{
  agl_assert(paranoid, type != AGL_RESOURCE_TYPE_UNKNOWN);
  agl_resource_t *resource = (agl_resource_t *)agl_alloc(
    sizeof(agl_resource_t), agl_alignof(agl_resource_t));
  resource->_type = type;
  resource->_ops = 1;
  resource->_internal = ((uintptr_t)NULL);
  return resource;
}

void agl_resource_destroy(
  agl_resource_t *resource)
{
  agl_assert(paranoid, resource != NULL);
  agl_free((void *)resource);
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

/* ========================================================================== */

/* QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ */
bool agl_resource_is_a_query(
  const agl_resource_t *resource)
{
  agl_assert(debug, resource != NULL);
  return (resource->_type == AGL_RESOURCE_TYPE_QUERY);
}

/* ==========================================================================
    Queries (agl_query_t):
   ========================================================================== */

agl_resource_t *agl_query_create(
  const agl_query_type_t type,
  agl_command_list_t *cmds)
{
  agl_assert(debug, cmds != NULL);
  agl_resource_t *resource =
    (agl_resource_t *)agl_resource_create(AGL_RESOURCE_TYPE_QUERY);
  resource->_internal = (uintptr_t)agl_alloc(
    sizeof(agl_query_t), agl_alignof(agl_query_t));
  agl_query_t *query = (agl_query_t *)resource->_internal;
#if (AGL_BACKEND == AGL_BACKEND_OPENGL)
  query->id = 0;
#else
  #error ("Unknown or unsupported backend!")
#endif
  query->type = type;
  agl_resource_queue_for_create(resource, cmds);
  return resource;
}

void agl_query_destroy(
  agl_resource_t *query,
  agl_command_list_t *cmds)
{
  agl_assert(debug, query != NULL);
  agl_assert(debug, cmds != NULL);
  agl_resource_queue_for_destroy(query, cmds);
}

/* ========================================================================== */

void agl_query_begin(
  agl_resource_t *query,
  agl_command_list_t *cmds)
{
  agl_assert(debug, query != NULL);
  agl_assert(debug, cmds != NULL);
  agl_atomic_incr(&query->_ops);
  agl_query_begin_cmd_t *cmd = (agl_query_begin_cmd_t *)
    agl_command_list_enqueue(cmds, sizeof(agl_query_begin_cmd_t));
  cmd->cmd.type = AGL_COMMAND_TYPE_QUERY_BEGIN;
  cmd->query = query;
}

void agl_query_end(
  agl_resource_t *query,
  agl_command_list_t *cmds)
{
  agl_assert(debug, query != NULL);
  agl_assert(debug, cmds != NULL);
  agl_atomic_incr(&query->_ops);
  agl_query_end_cmd_t *cmd = (agl_query_end_cmd_t *)
    agl_command_list_enqueue(cmds, sizeof(agl_query_end_cmd_t));
  cmd->cmd.type = AGL_COMMAND_TYPE_QUERY_END;
  cmd->query = query;
}
/* QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ */


/* ========================================================================== */
/*  Commands:                                                                 */
/*   * Resource Commands                                                      */
/* ========================================================================== */

/* ==========================================================================
    Commands (agl_command_t):
   ========================================================================== */

size_t agl_command_length(
  const agl_command_t *cmd)
{
  switch (cmd->type) {
    case AGL_COMMAND_TYPE_RESOURCE_CREATE:
      return sizeof(agl_resource_create_cmd_t);
    case AGL_COMMAND_TYPE_RESOURCE_DESTROY:
      return sizeof(agl_resource_destroy_cmd_t);
    default:
      agl_error(AGL_EUNKNOWN);
  }
}

/* ==========================================================================
    Resource Commands:
   ========================================================================== */

/* ... */

#ifdef __cplusplus
}
#endif /* __cplusplus */
