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

#if (AGL_PLATFORM == AGL_PLATFORM_WINDOWS)
  #include <agl.d3d9.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ========================================================================== */
/*  Integration:                                                              */
/*   * Errors & Error Handling                                                */
/*   * Memory Management                                                      */
/*   * Backends                                                               */
/*   * Initialization & Deinitialization                                      */
/* ========================================================================== */

/* ==========================================================================
    Errors & Error Handling (agl_error_t):
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
    Memory Management (agl_allocator_t):
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

/* ==========================================================================
    Backends (agl_backend_t):
   ========================================================================== */

/* ... */

/* ==========================================================================
    Initialization & Deinitialization (agl_initialize, agl_deinitialize):
   ========================================================================== */

agl_initialize_fn agl_initialize_ = NULL;
agl_deinitialize_fn agl_deinitialize_ = NULL;

/* ========================================================================== */

void agl_initialize(
  const agl_backend_t backend)
{
  switch (backend) {
  #if (AGL_PLATFORM == AGL_PLATFORM_WINDOWS)
    case AGL_BACKEND_D3D9: {
      agl_initialize_         = &agl_initialize_d3d9;
      agl_deinitialize_       = &agl_deinitialize_d3d9;
      agl_context_alloc_      = &agl_context_alloc_d3d9;
      agl_context_free_       = &agl_context_free_d3d9;
      agl_context_create_     = &agl_context_create_d3d9;
      agl_context_destroy_    = &agl_context_destroy_d3d9;
      agl_swap_chain_alloc_   = &agl_swap_chain_alloc_d3d9;
      agl_swap_chain_free_    = &agl_swap_chain_free_d3d9;
      agl_swap_chain_create_  = &agl_swap_chain_create_d3d9;
      agl_swap_chain_destroy_ = &agl_swap_chain_destroy_d3d9;
      agl_swap_chain_present_ = &agl_swap_chain_present_d3d9;
    } break;
  #endif
    default: {
      agl_error(AGL_EUNKNOWN);
    } break;
  }

  agl_initialize_();
}

void agl_deinitialize()
{
  agl_deinitialize_();

  agl_initialize_         = NULL;
  agl_deinitialize_       = NULL;
  agl_context_alloc_      = NULL;
  agl_context_free_       = NULL;
  agl_context_create_     = NULL;
  agl_context_destroy_    = NULL;
  agl_swap_chain_alloc_   = NULL;
  agl_swap_chain_free_    = NULL;
  agl_swap_chain_create_  = NULL;
  agl_swap_chain_destroy_ = NULL;
  agl_swap_chain_present_ = NULL;
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

size_t _agl_num_of_adapters = 0;
const agl_adapter_t *_agl_adapters = NULL;

size_t agl_adapter_count()
{
  return _agl_num_of_adapters;
}

const agl_adapter_t *agl_adapter_get(
  const size_t adapter_id)
{
  agl_assert(debug, adapter_id < _agl_num_of_adapters);
  return &_agl_adapters[adapter_id];
}

const agl_adapter_t *agl_adapter_primary()
{
  for (size_t adapter_id = 0; adapter_id < _agl_num_of_adapters; ++adapter_id) {
    if (_agl_adapters[adapter_id].primary)
      return &_agl_adapters[adapter_id];
  } return NULL;
}

const struct agl_output *agl_adapter_primary_output(
  const agl_adapter_t *adapter)
{
  agl_assert(debug, adapter != NULL);
  for (size_t output_id = 0; output_id < adapter->num_of_outputs; ++output_id) {
    if (adapter->outputs[output_id].primary)
      return &adapter->outputs[output_id];
  } return NULL;
}

/* ==========================================================================
    Outputs (agl_output_t):
   ========================================================================== */

const struct agl_display_mode *agl_output_find_closest_matching_display_mode(
  const agl_output_t *output,
  const struct agl_display_mode *templ)
{
  agl_assert(debug, output != NULL);
  agl_assert(debug, templ != NULL);
  for (size_t display_mode_id = 0; display_mode_id < output->num_of_display_modes; ++display_mode_id) {
    const struct agl_display_mode *display_mode =
      &output->display_modes[display_mode_id];
    if ((templ->format != AGL_PIXEL_FORMAT_UNKNOWN) &&
        (display_mode->format != templ->format))
      { continue; }
    if ((templ->width != 0) &&
        (display_mode->width != templ->width))
      { continue; }
    if ((templ->height != 0) &&
        (display_mode->height != templ->height))
      { continue; }
    if ((templ->refresh_rate != 0) &&
        (display_mode->refresh_rate != templ->refresh_rate))
      { continue; }
    return display_mode;
  } return NULL;
}

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

agl_context_alloc_fn agl_context_alloc_ = NULL;
agl_context_free_fn agl_context_free_ = NULL;
agl_context_create_fn agl_context_create_ = NULL;
agl_context_destroy_fn agl_context_destroy_ = NULL;

/* ========================================================================== */

agl_context_t *agl_context_create(
  const agl_adapter_t *adapter)
{
  agl_assert(debug, adapter != NULL);
  agl_context_t *context = agl_context_alloc_();
  context->adapter = adapter;
  agl_context_create_(context);
  return context;
}

void agl_context_destroy(
  agl_context_t *context)
{
  agl_assert(debug, context != NULL);
  agl_context_destroy_(context);
  agl_context_free_(context);
}

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

/* ========================================================================== */

void agl_command_list_execute(
  const agl_command_list_t *command_list,
  agl_context_t *context)
{
  agl_assert(debug, command_list != NULL);
  agl_assert(debug, context != NULL);

  const agl_command_t *cmd = agl_command_list_dequeue(command_list, NULL);
  while (cmd) {
    switch (cmd->type) {
      case AGL_RESOURCE_CREATE_CMD: {
        const agl_resource_create_cmd_t *cmd_ =
          (const agl_resource_create_cmd_t *)cmd;
        switch (cmd_->resource->type) {
          case AGL_RESOURCE_TYPE_SWAP_CHAIN:
            agl_swap_chain_create_((agl_swap_chain_t *)cmd_->resource, context); break;
          default:
            agl_error(AGL_EUNKNOWN); break;
        } agl_atomic_decr(&cmd_->resource->ops);
      } break;
      case AGL_RESOURCE_DESTROY_CMD: {
        const agl_resource_destroy_cmd_t *cmd_ =
          (const agl_resource_destroy_cmd_t *)cmd;
        switch (cmd_->resource->type) {
          case AGL_RESOURCE_TYPE_SWAP_CHAIN:
            agl_swap_chain_destroy_((agl_swap_chain_t *)cmd_->resource, context); break;
          default:
            agl_error(AGL_EUNKNOWN); break;
        } agl_atomic_decr(&cmd_->resource->ops);
      } break;
      case AGL_SWAP_CHAIN_PRESENT_CMD: {
        const agl_swap_chain_present_cmd_t *cmd_ =
          (const agl_swap_chain_present_cmd_t *)cmd;
        agl_swap_chain_create_(cmd_->swap_chain, context);
        agl_atomic_decr(&cmd_->swap_chain->resource.ops);
      } break;
      default: {
        agl_error(AGL_EUNKNOWN);
      } break;
    }

    cmd = agl_command_list_dequeue(command_list, cmd);
  }
}

/* ==========================================================================
    Requests (agl_request_t):
   ========================================================================== */

/* ... */

/* ==========================================================================
    Resources (agl_resource_t):
   ========================================================================== */

void agl_resource_init(agl_resource_t *resource) {
  agl_assert(paranoid, resource != NULL);
  resource->type = AGL_RESOURCE_TYPE_UNKNOWN;
  resource->ops = 0;
  resource->flags = 0;
}

/* ========================================================================== */

agl_resource_type_t agl_resource_type(
  const agl_resource_t *resource)
{
  agl_assert(debug, resource != NULL);
  return resource->type;
}

uint agl_resource_ops(
  const agl_resource_t *resource)
{
  agl_assert(debug, resource != NULL);
  return resource->ops;
}

/* ========================================================================== */

void agl_resource_queue_for_create(
  agl_resource_t *resource,
  agl_command_list_t *cmds)
{
  agl_assert(paranoid, resource != NULL);
  agl_assert(paranoid, cmds != NULL);
  agl_atomic_incr(&resource->ops);
  agl_resource_create_cmd_t *cmd = (agl_resource_create_cmd_t *)
    agl_command_list_enqueue(cmds, sizeof(agl_resource_create_cmd_t));
  cmd->cmd.type = AGL_RESOURCE_CREATE_CMD;
  cmd->resource = resource;
}

void agl_resource_queue_for_destroy(
  agl_resource_t *resource,
  agl_command_list_t *cmds)
{
  agl_assert(paranoid, resource != NULL);
  agl_assert(paranoid, cmds != NULL);
  agl_atomic_incr(&resource->ops);
  agl_resource_destroy_cmd_t *cmd = (agl_resource_destroy_cmd_t *)
    agl_command_list_enqueue(cmds, sizeof(agl_resource_destroy_cmd_t));
  cmd->cmd.type = AGL_RESOURCE_DESTROY_CMD;
  cmd->resource = resource;
}

/* ========================================================================== */

bool agl_resource_is_available(
  const agl_resource_t *resource)
{
  agl_assert(debug, resource != NULL);
  const uint flags = *((volatile uintptr_t *)&resource->flags);
  return !!(flags & AGL_RESOURCE_IS_AVAILABLE_BIT);
}

bool agl_resource_is_reflective(
  const agl_resource_t *resource)
{
  agl_assert(debug, resource != NULL);
  return (agl_atomic_compr_and_swap(
    (volatile uint *)&resource->ops,
    0, 0) == 0);
}

/* ==========================================================================
    Resources > Swap Chains:
   ========================================================================== */

agl_swap_chain_alloc_fn agl_swap_chain_alloc_ = NULL;
agl_swap_chain_free_fn agl_swap_chain_free_ = NULL;
agl_swap_chain_create_fn agl_swap_chain_create_ = NULL;
agl_swap_chain_destroy_fn agl_swap_chain_destroy_ = NULL;
agl_swap_chain_present_fn agl_swap_chain_present_ = NULL;

/* ========================================================================== */

agl_swap_chain_t *agl_swap_chain_create(
  agl_context_t *context,
  agl_command_list_t *cmds,
  agl_surface_hndl_t surface,
  agl_pixel_format_t format,
  uint32_t width,
  uint32_t height,
  bool fullscreen,
  bool verical_sync)
{
  agl_assert(debug, context != NULL);
  agl_assert(debug, cmds != NULL);
  agl_assert(debug, surface != ((agl_surface_hndl_t)0));
  agl_assert(debug, width > 0);
  agl_assert(debug, height > 0);

  agl_swap_chain_t *swap_chain = agl_swap_chain_alloc_();
  agl_resource_init(&swap_chain->resource);
  swap_chain->resource.type = AGL_RESOURCE_TYPE_SWAP_CHAIN;

  swap_chain->surface = surface;
  swap_chain->format = format;
  swap_chain->width = width;
  swap_chain->height = height;

  if (fullscreen)
    swap_chain->resource.flags |= AGL_SWAP_CHAIN_IS_FULLSCREEN;
  else
    swap_chain->resource.flags |= AGL_SWAP_CHAIN_IS_WINDOWED;

  if (verical_sync)
    swap_chain->resource.flags |= AGL_SWAP_CHAIN_IS_VERTICALLY_SYNCHRONIZED;

  agl_resource_queue_for_create(&swap_chain->resource, cmds);
  return swap_chain;
}

void agl_swap_chain_destroy(
  agl_swap_chain_t *swap_chain,
  agl_command_list_t *cmds)
{
  agl_assert(debug, swap_chain != NULL);
  agl_assert(debug, cmds != NULL);

  agl_resource_queue_for_destroy(&swap_chain->resource, cmds);
}

/* ========================================================================== */

agl_surface_hndl_t agl_swap_chain_surface(
const agl_swap_chain_t *swap_chain)
{
  agl_assert(debug, swap_chain != NULL);
  return swap_chain->surface;
}

agl_pixel_format_t agl_swap_chain_format(
  const agl_swap_chain_t *swap_chain)
{
  agl_assert(debug, swap_chain != NULL);
  return swap_chain->format;
}

uint32_t agl_swap_chain_width(
  const agl_swap_chain_t *swap_chain)
{
  agl_assert(debug, swap_chain != NULL);
  return swap_chain->width;
}

uint32_t agl_swap_chain_height(
  const agl_swap_chain_t *swap_chain)
{
  agl_assert(debug, swap_chain != NULL);
  return swap_chain->height;
}

/* ========================================================================== */

void agl_swap_chain_resize(
  agl_swap_chain_t *swap_chain,
  agl_command_list_t *cmds,
  uint32_t width,
  uint32_t height)
{
  agl_assert(debug, swap_chain != NULL);
  agl_assert(debug, cmds != NULL);
  agl_error(AGL_EUNKNOWN);
}

void agl_swap_chain_window(
  agl_swap_chain_t *swap_chain,
  agl_command_list_t *cmds)
{
  agl_assert(debug, swap_chain != NULL);
  agl_assert(debug, cmds != NULL);
  agl_error(AGL_EUNKNOWN);
}

void agl_swap_chain_fullscreen(
  agl_swap_chain_t *swap_chain,
  agl_command_list_t *cmds)
{
  agl_assert(debug, swap_chain != NULL);
  agl_assert(debug, cmds != NULL);
  agl_error(AGL_EUNKNOWN);
}

void agl_swap_chain_vertically_synchronize(
  agl_swap_chain_t *swap_chain,
  agl_command_list_t *cmds,
  bool synchronize)
{
  agl_assert(debug, swap_chain != NULL);
  agl_error(AGL_EUNKNOWN);
}

void agl_swap_chain_present(
  agl_swap_chain_t *swap_chain,
  agl_command_list_t *cmds)
{
  agl_assert(debug, swap_chain != NULL);
  agl_assert(debug, cmds != NULL);
  agl_atomic_incr(&swap_chain->resource.ops);
  agl_swap_chain_present_cmd_t *cmd = (agl_swap_chain_present_cmd_t *)
    agl_command_list_enqueue(cmds, sizeof(agl_swap_chain_present_cmd_t));
  cmd->cmd.type = AGL_SWAP_CHAIN_PRESENT_CMD;
  cmd->swap_chain = swap_chain;
}

/* ========================================================================== */

bool agl_swap_chain_is_windowed(
  const agl_swap_chain_t *swap_chain)
{
  agl_assert(debug, swap_chain != NULL);
  return !!(swap_chain->resource.flags & AGL_SWAP_CHAIN_IS_WINDOWED);
}

bool agl_swap_chain_is_fullscreen(
  const agl_swap_chain_t *swap_chain)
{
  agl_assert(debug, swap_chain != NULL);
  return !!(swap_chain->resource.flags & AGL_SWAP_CHAIN_IS_FULLSCREEN);
}

bool agl_swap_chain_is_vertically_synchronized(
  const agl_swap_chain_t *swap_chain)
{
  agl_assert(debug, swap_chain != NULL);
  return !!(swap_chain->resource.flags & AGL_SWAP_CHAIN_IS_VERTICALLY_SYNCHRONIZED);
}

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
  agl_assert(paranoid, cmd != NULL);
  switch (cmd->type) {
    case AGL_RESOURCE_CREATE_CMD:
      return sizeof(agl_resource_create_cmd_t);
    case AGL_RESOURCE_DESTROY_CMD:
      return sizeof(agl_resource_destroy_cmd_t);
    case AGL_SWAP_CHAIN_PRESENT_CMD:
      return sizeof(agl_swap_chain_present_cmd_t);
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
