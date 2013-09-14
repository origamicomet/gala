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
    Resources (agl_resource_t):
   ========================================================================== */

agl_resource_t *agl_resource_create(
  const agl_resource_type_t type)
{
  if (type == AGL_RESOURCE_TYPE_UNKNOWN)
    return NULL;
  /* TODO (mtwilliams): Lock-free pool or free-list. */
  agl_resource_t *resource = (agl_resource_t *)malloc(sizeof(agl_resource_t));
  resource->_type = type;
  resource->_refs = 1u;
  resource->_ops = 0u;
  resource->_internal = NULL;
  return resource;
}

agl_resource_type_t agl_resource_type(
  const agl_resource_t *resource)
{
  if (!resource)
    return AGL_RESOURCE_TYPE_UNKNOWN;
  return resource->_type;
}

uint agl_resource_ops(
  const agl_resource_t *resource)
{
  if (!resource)
    return 0;
  return resource->_ops;
}

void agl_resource_ref(
  agl_resource_t *resource)
{
  if (!resource)
    return;
  agl_atomic_incr(&resource->_refs);
}

void agl_resource_deref(
  agl_resource_t *resource)
{
  if (!resource)
    return;
  if (agl_atomic_decr(&resource->_refs) > 0)
    return;
  free((void *)resource);
}

bool agl_resource_is_available(
  const agl_resource_t *resource)
{
  if (!resource)
    return false;
  return false;
}

bool agl_resource_is_reflective(
  const agl_resource_t *resource)
{
  if (!resource)
    return false;
  return false;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
