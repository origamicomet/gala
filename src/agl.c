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

#include "agl_private.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* 2. Runtime: */

bool agl_is_runtime_supported(
  const agl_runtime_t runtime)
{
  switch (runtime) {
  #if defined(AGL_PLATFORM_WINDOWS)
    case AGL_OPENGL:
    case AGL_D3D9:
    case AGL_D3D1x:
      return true;
    case AGL_OPENGL_ES:
    case AGL_GCM:
      return false;
  #else
    #error("agl_is_runtime_supported is not implemented, yet.")
  #endif
  }

  return false;
}

static const char* agl_runtime_path(const agl_runtime_t runtime) {
  switch (runtime) {
  #if defined(AGL_PLATFORM_WINDOWS)
    case AGL_OPENGL: return "aglr-opengl-" AGL_ARCHITECTURE AGL_BUILD_SUFFIX ".dll";
    case AGL_D3D9: return "aglr-d3d9-" AGL_ARCHITECTURE AGL_BUILD_SUFFIX ".dll";
    case AGL_D3D1x: return "aglr-d3d1x-" AGL_ARCHITECTURE AGL_BUILD_SUFFIX ".dll";
    case AGL_OPENGL_ES: case AGL_GCM: return NULL;
  #else
    #error("agl_runtime_path is not implemented, yet.")
  #endif
  }

  return NULL;
}

static agl_shared_lib_t *_runtime = NULL;
static agl_get_num_of_adapters_fn _get_num_of_adapters = NULL;
static agl_get_adapter_fn _get_adapter = NULL;
static agl_create_context_fn _create_context = NULL;
static agl_destroy_context_fn _destroy_context = NULL;
static agl_is_available_fn _is_available = NULL;
static agl_is_reflective_fn _is_reflective = NULL;

static void agl_unload_runtime() {
  if (_runtime)
    agl_shared_lib_close(_runtime);
  _runtime = NULL;
  _get_num_of_adapters = NULL;
  _get_adapter = NULL;
}

agl_err_t agl_use_runtime(
  const agl_runtime_t runtime)
{
  if (!agl_is_runtime_supported(runtime))
    return AGL_EINVALIDARG;

  agl_unload_runtime();

  _runtime = agl_shared_lib_open(agl_runtime_path(runtime));
  if (!_runtime)
    return AGL_EUNKNOWN;

  _get_num_of_adapters = (agl_get_num_of_adapters_fn)
    agl_shared_lib_sym(_runtime, "aglr_get_num_of_adapters");
  if (!_get_num_of_adapters)
    goto invalid_runtime;

  _get_adapter = (agl_get_adapter_fn)
    agl_shared_lib_sym(_runtime, "aglr_get_adapter");
  if (!_get_adapter)
    goto invalid_runtime;

  _create_context = (agl_create_context_fn)
    agl_shared_lib_sym(_runtime, "aglr_create_context");
  if (!_create_context)
    goto invalid_runtime;

  _destroy_context = (agl_destroy_context_fn)
    agl_shared_lib_sym(_runtime, "aglr_destroy_context");
  if (!_destroy_context)
    goto invalid_runtime;

  _is_available = (agl_is_available_fn)
    agl_shared_lib_sym(_runtime, "aglr_is_available");
  if (!_destroy_context)
    goto invalid_runtime;

  _is_reflective = (agl_is_reflective_fn)
    agl_shared_lib_sym(_runtime, "aglr_is_reflective");
  if (!_destroy_context)
    goto invalid_runtime;

  return AGL_ENONE;

invalid_runtime:
  agl_unload_runtime();
  return AGL_EUNKNOWN;
}

/* 3. Adapters and outputs: */

agl_err_t agl_get_num_of_adapters(
  size_t *num_of_adapters)
{
  agl_assert(debug, _runtime != NULL);
  agl_assert(debug, num_of_adapters != NULL);
  *num_of_adapters = _get_num_of_adapters();
  return AGL_ENONE;
}

const agl_adapter_t *agl_get_adapter(
  const agl_adapter_id_t id)
{
  agl_assert(debug, _get_adapter != NULL);
  return _get_adapter(id);
}

/* 5. Contexts: */

agl_err_t agl_create_context(
  const agl_adapter_id_t adapter,
  agl_context_t **context)
{
  agl_assert(debug, _runtime != NULL);
  if (adapter >= _get_num_of_adapters())
    return AGL_EINVALIDARG;
  *context = _create_context(adapter);
  return ((*context) ? AGL_ENONE : AGL_ERUNTIME);
}

typedef struct agl_dispatch_context {
  agl_context_t *context;
  uint skipped;
} agl_dispatch_context_t;

static void agl_dispatch_for_each(void *closure, const agl_command_t *cmd) {
  agl_dispatch_context_t *ctx = (agl_dispatch_context_t*)closure;
  switch (cmd->type) {
    case AGL_IS_AVAILABLE_CMD: {
      const agl_is_available_cmd_t *cmd =
        (const agl_is_available_cmd_t*)cmd;
      const uint avail = _is_available(ctx->context, cmd->id) ? 1u : 0u;
      agl_atomic_compare_and_swap(cmd->avail, AGL_UNANSWERED, avail);
    } break;

    case AGL_IS_REFLECTIVE_CMD: {
      const agl_is_reflective_cmd_t *cmd =
        (const agl_is_reflective_cmd_t*)cmd;
      const uint reflective = _is_reflective(ctx->context, cmd->id) ? 1u : 0u;
      agl_atomic_compare_and_swap(cmd->reflective, AGL_UNANSWERED, reflective);
    } break;

    default: {
      /* agl_atomic_incr(&ctx->skipped); */
      ctx->skipped++;
    } break;
  }
}

agl_err_t agl_dispatch(
  agl_context_t *context,
  const agl_command_list_t *command_list)
{
  agl_assert(debug, _runtime != NULL);
  agl_assert(debug, context != NULL);
  agl_assert(debug, command_list != NULL);

  agl_dispatch_context_t ctx;
  ctx.context = context;
  ctx.skipped = 0;
  agl_command_list_for_each(command_list, &agl_dispatch_for_each, (void*)&ctx);
  return ((ctx.skipped > 0) ? AGL_ERUNTIME : AGL_ENONE);
}

agl_err_t agl_destroy_context(
  agl_context_t *context)
{
  agl_assert(debug, _runtime != NULL);
  agl_assert(debug, context != NULL);
  _destroy_context(context);
  return AGL_ENONE;
}

/* 6. Resources: */

agl_err_t agl_is_available(
  agl_command_list_t *command_list,
  const volatile agl_id_t *id,
  volatile uint *avail)
{
  agl_assert(debug, _runtime != NULL);
  agl_assert(debug, id != NULL);
  agl_assert(debug, avail != NULL);

  *avail = AGL_UNANSWERED;

  agl_is_available_cmd_t cmd;
  cmd.cmd.type = AGL_IS_AVAILABLE_CMD;
  cmd.id = id;
  cmd.avail = avail;

  if (!agl_command_list_enqueue(command_list, (const void*)&cmd, sizeof(agl_is_available_cmd_t)))
    return AGL_ECOMMANDLISTEXHAUSTED;

  return AGL_ENONE;
}

bool agl_is_available_sync(
  agl_context_t *context,
  const volatile agl_id_t *id)
{
  agl_assert(debug, _runtime != NULL);
  agl_assert(debug, context != NULL);
  agl_assert(debug, id != NULL);
  return _is_available(context, id);
}

agl_err_t agl_is_reflective(
  agl_command_list_t *command_list,
  volatile agl_id_t *id,
  volatile uint *reflective)
{
  agl_assert(debug, _runtime != NULL);
  agl_assert(debug, id != NULL);
  agl_assert(debug, reflective != NULL);

  *reflective = AGL_UNANSWERED;

  agl_is_reflective_cmd_t cmd;
  cmd.cmd.type = AGL_IS_AVAILABLE_CMD;
  cmd.id = id;
  cmd.reflective = reflective;

  if (!agl_command_list_enqueue(command_list, (const void*)&cmd, sizeof(agl_is_reflective_cmd_t)))
    return AGL_ECOMMANDLISTEXHAUSTED;

  return AGL_ENONE;
}

bool agl_is_reflective_sync(
  agl_context_t *context,
  volatile agl_id_t *id)
{
  agl_assert(debug, _runtime != NULL);
  agl_assert(debug, context != NULL);
  agl_assert(debug, id != NULL);
  return _is_reflective(context, id);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
