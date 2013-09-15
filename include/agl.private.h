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

#ifndef _AGL_PRIVATE_H_
#define _AGL_PRIVATE_H_

#include <agl.h>
#include <agl.commands.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ==========================================================================
    Errors (agl_error_t):
   ========================================================================== */

/*! */
void agl_error(
  const agl_err_t error);

/* ==========================================================================
    Allocator (agl_allocator_t):
   ========================================================================== */

void *agl_alloc(
  const size_t num_of_bytes,
  const size_t alignment);

void *agl_realloc(
  void *ptr,
  const size_t num_of_bytes,
  const size_t alignment);

void agl_free(
  void *ptr);

/* ==========================================================================
    Requests (agl_request_t):
   ========================================================================== */

/* ... */

/* ==========================================================================
    Command Lists (agl_command_list_t):
   ========================================================================== */

/*! Reserves `command_len` bytes for a command.
  @params[in] command_list The command-list to "enqueue" into.
  @params[in] command_len  The number of bytes required for the command.
  @returns A pointer to command (of `command_len` bytes) that is "enqueued" in
           the command-list.
  @warning May raise an AGL_EOUTOFMEMORY error if the command-list is exhausted
           and cannot be resized to accomodate the command. */
agl_command_t *agl_command_list_enqueue(
  agl_command_list_t *command_list,
  const size_t command_len);

/*! Returns the next command in a command list.
  @params[in] command_list The command-list to "dequeue" from.
  @params[in] cmd          A previously "dequeued" command, or NULL.
  @returns A pointer to the next command that is "enqueued" in the command-list,
           or NULL if there are no more commands. If `cmd` is NULL then the
           first command is returned or NULL if there are no commands. */
const agl_command_t *agl_command_list_dequeue(
  const agl_command_list_t *command_list,
  const agl_command_t *cmd);

/* ==========================================================================
    Resources (agl_resource_t):
   ========================================================================== */

/*! Creates a new resource.
  @param[in] type The type of resource to create.
  @returns AGL_INVALID_RESOURCE if the resource could not be created; or a
           non-AGL_INVALID_RESOURCE if the resource was created.
  @warning Succesful creation doesn't imply or guarantee existence. An
           initialization command like agl_texture_storage_2d() might be
           nessecary. */
agl_resource_t *agl_resource_create(
  const agl_resource_type_t type);

/*! Destroys a resource.
  @param[in] resource The resource to destroy.
  @warning Doesn't touch _internal (that's handled per-type). */
void agl_resource_destroy(
  agl_resource_t *resource);

/* ========================================================================== */

/*! Enqueues a command to create the internal representation of a resource.
  @param[in] resource The resource.
  @param[in] cmds     The command-list to enqueue the command to. */
void agl_resource_queue_for_create(
  agl_resource_t *resource,
  agl_command_list_t *cmds);

/*! Enqueues a command to destroy the internal representation of a resource.
  @param[in] resource The resource.
  @param[in] cmds     The command-list to enqueue the command to. */
void agl_resource_queue_for_destroy(
  agl_resource_t *resource,
  agl_command_list_t *cmds);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _AGL_PRIVATE_H_ */
