//===-- gala/d3d11/engine.c -------------------------------------*- C++ -*-===//
//
//  Gala
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//    * Michael Williams <mike@origamicomet.com>
//
//===----------------------------------------------------------------------===//

#include "gala/d3d11/types.h"
#include "gala/d3d11/engine.h"

//===----------------------------------------------------------------------===//

#include "gala/commands.h"
#include "gala/d3d11/commands.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

void
gala_d3d11_engine_shutdown_and_destroy(
  gala_d3d11_engine_t *engine)
{
  gala_assert_debug(engine != NULL);
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  bitbyte_foundation_mutex_destroy(engine->resources.lock);
  engine->dxgi.factory->Release();
  engine->d3d11.immediate_context->Release();
  engine->d3d11.device->Release();
  FreeLibrary(engine->d3d11.dll);
#if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
  // This might help find some (stupid) bugs.
  engine->resources.lock = (bitbyte_foundation_mutex_t *)NULL;
  engine->dxgi.factory = (IDXGIFactory *)NULL;
  engine->d3d11.immediate_context = (ID3D11DeviceContext *)NULL;
  engine->d3d11.device = (ID3D11Device *)NULL;
  engine->d3d11.dll = (HMODULE)NULL;
#endif
#endif
  gala_engine_shutdown(&engine->__engine__);
  bitbyte_foundation_tier4_allocator_t *heap = bitbyte_foundation_tier4_heap();
  heap->free(heap, (void *)engine);
}

//===----------------------------------------------------------------------===//

gala_swap_chain_hndl_t
gala_d3d11_engine_create_swap_chain(
  gala_d3d11_engine_t *engine)
{
  gala_assert_debug(engine != NULL);
  bitbyte_foundation_mutex_lock(engine->resources.lock);
  const uint32_t slot = bitbyte_foundation_atomic_uint32_fetch_and_incr_relaxed(&engine->resources.swap_chains.count);
  gala_assertf(slot < GALA_D3D11_ENGINE_MAX_NUM_SWAP_CHAINS, "Exceeded maximum number of swap-chains!");
  struct gala_d3d11_swap_chain *swap_chain = &engine->resources.swap_chains.pool[slot];
  gala_swap_chain_init(&swap_chain->__swap_chain__);
  swap_chain->itf = (IDXGISwapChain *)NULL;
  swap_chain->rtv = (ID3D11RenderTargetView *)NULL;
  gala_swap_chain_hndl_t swap_chain_hndl = (gala_swap_chain_hndl_t)swap_chain;
  bitbyte_foundation_mutex_unlock(engine->resources.lock);
  return swap_chain_hndl;
}

//===----------------------------------------------------------------------===//

void
gala_d3d11_engine_insert_init_swap_chain(
  const gala_d3d11_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  const gala_swap_chain_hndl_t swap_chain,
  const gala_swap_chain_desc_t *desc)
{
  gala_assert_debug(engine != NULL);

  gala_assert_debug(command_buffer != NULL);
  gala_d3d11_command_init_swap_chain_t *cmd =
    (gala_d3d11_command_init_swap_chain_t *)gala_command_buffer_insert_yielded(command_buffer, sizeof(gala_d3d11_command_init_swap_chain_t));
  cmd->__command__.type = (gala_command_type_t)GALA_D3D11_COMMAND_TYPE_INIT_SWAP_CHAIN;
  cmd->__command__.len = sizeof(gala_d3d11_command_init_swap_chain_t);

  gala_assert_debug(desc != NULL);
  gala_assert_debug((desc->width >= 1) && (desc->width % 2) == 0);
  cmd->swap_chain_desc.BufferDesc.Width = desc->width;
  gala_assert_debug((desc->height >= 1) && (desc->height % 2) == 0);
  cmd->swap_chain_desc.BufferDesc.Height = desc->height;
  if (desc->flags & GALA_SWAP_CHAIN_FULLSCREEN) {
    // FIXME(mtwilliams): Create windowed, THEN upgrade to fullscreen.
    cmd->swap_chain_desc.BufferDesc.RefreshRate.Numerator = desc->refresh_rate.numer;
    if (desc->refresh_rate.denom > 0) {
      cmd->swap_chain_desc.BufferDesc.RefreshRate.Denominator = desc->refresh_rate.denom;
    } else {
      cmd->swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
    }
    cmd->swap_chain_desc.Windowed = FALSE;
  } else {
    cmd->swap_chain_desc.BufferDesc.RefreshRate.Numerator = 0;
    cmd->swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
    cmd->swap_chain_desc.Windowed = TRUE;
  }
  // TODO(mtwilliams): Support more back-buffer formats than R8G8B8A8.
  gala_assert_debug(desc->format == GALA_PIXEL_FORMAT_R8G8B8A8);
  cmd->swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  cmd->swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
  cmd->swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;
  // TODO(mtwilliams): Expose multisampling.
  cmd->swap_chain_desc.SampleDesc.Count = 1;
  cmd->swap_chain_desc.SampleDesc.Quality = 0;
  cmd->swap_chain_desc.BufferUsage = DXGI_USAGE_BACK_BUFFER | DXGI_USAGE_RENDER_TARGET_OUTPUT;
  cmd->swap_chain_desc.BufferCount = (!!(desc->flags & GALA_SWAP_CHAIN_FULLSCREEN) ? 2 : 1);
  gala_assert_debug(desc->surface != NULL);
  gala_assert_debug(IsWindow((HWND)desc->surface));
  cmd->swap_chain_desc.OutputWindow = (HWND)desc->surface;
  cmd->swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
  // TODO(mtwilliams): Should we specify DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH?
  cmd->swap_chain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
  gala_assert_debug(swap_chain != GALA_INVALID_SWAP_CHAIN_HANDLE);
  bitbyte_foundation_mutex_lock(engine->resources.lock);
  gala_assert_debug(((gala_resource_t *)swap_chain)->type == GALA_RESOURCE_TYPE_SWAP_CHAIN);
  gala_assert_debug(((struct gala_d3d11_swap_chain *)swap_chain)->itf == (IDXGISwapChain *)NULL);
  cmd->swap_chain = &((struct gala_d3d11_swap_chain *)swap_chain)->itf;
  gala_assert_debug(((struct gala_d3d11_swap_chain *)swap_chain)->rtv == (ID3D11RenderTargetView *)NULL);
  cmd->rtv = &((struct gala_d3d11_swap_chain *)swap_chain)->rtv;
  bitbyte_foundation_mutex_unlock(engine->resources.lock);

  gala_command_buffer_insert_yielded_finish(command_buffer, (void *)cmd);
}

//===----------------------------------------------------------------------===//

void
gala_d3d11_engine_insert_present(
  const gala_d3d11_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  const gala_swap_chain_hndl_t swap_chain)
{
  gala_assert_debug(engine != NULL);

  gala_assert_debug(command_buffer != NULL);
  gala_d3d11_command_present_t *cmd =
    (gala_d3d11_command_present_t *)gala_command_buffer_insert_yielded(command_buffer, sizeof(gala_d3d11_command_present_t));
  cmd->__command__.type = (gala_command_type_t)GALA_D3D11_COMMAND_TYPE_PRESENT;
  cmd->__command__.len = sizeof(gala_d3d11_command_present_t);

  gala_assert_debug(swap_chain != GALA_INVALID_SWAP_CHAIN_HANDLE);
  bitbyte_foundation_mutex_lock(engine->resources.lock);
  // TODO(mtwilliams): Implement render target views.
  gala_assert_debug(((gala_resource_t *)swap_chain)->type == GALA_RESOURCE_TYPE_SWAP_CHAIN);
  gala_assert_debug(((struct gala_d3d11_swap_chain *)swap_chain)->itf != (IDXGISwapChain *)NULL);
  cmd->swap_chain = ((struct gala_d3d11_swap_chain *)swap_chain)->itf;
  bitbyte_foundation_mutex_unlock(engine->resources.lock);

  gala_command_buffer_insert_yielded_finish(command_buffer, (void *)cmd);
}

//===----------------------------------------------------------------------===//

void
gala_d3d11_engine_insert_clear_render_target_view(
  const gala_d3d11_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  const gala_resource_hndl_t render_target_view,
  const float rgba[4])
{
  gala_assert_debug(engine != NULL);

  gala_assert_debug(command_buffer != NULL);
  gala_d3d11_command_clear_render_target_view_t *cmd =
    (gala_d3d11_command_clear_render_target_view_t *)gala_command_buffer_insert_yielded(command_buffer, sizeof(gala_d3d11_command_clear_render_target_view_t));
  cmd->__command__.type = (gala_command_type_t)GALA_D3D11_COMMAND_TYPE_CLEAR_RENDER_TARGET_VIEW;
  cmd->__command__.len = sizeof(gala_d3d11_command_clear_render_target_view_t);

  gala_assert_debug(render_target_view != GALA_INVALID_RESOURCE_HANDLE);
  bitbyte_foundation_mutex_lock(engine->resources.lock);
  // TODO(mtwilliams): Implement render target views.
  gala_assert_debug(((gala_resource_t *)render_target_view)->type == GALA_RESOURCE_TYPE_SWAP_CHAIN);
  gala_assert_debug(((struct gala_d3d11_swap_chain *)render_target_view)->rtv != (ID3D11RenderTargetView *)NULL);
  cmd->rtv = ((struct gala_d3d11_swap_chain *)render_target_view)->rtv;
  bitbyte_foundation_mutex_unlock(engine->resources.lock);
  memcpy((void *)&cmd->rgba[0], (const void *)&rgba[0], 4 * sizeof(float));

  gala_command_buffer_insert_yielded_finish(command_buffer, (void *)cmd);
}

//===----------------------------------------------------------------------===//

void
gala_d3d11_engine_execute(
  gala_d3d11_engine_t *engine,
  const gala_command_buffer_t *commands)
{
  gala_assert_debug(engine != NULL);
  gala_assert_debug(commands->start <= commands->current);

  uintptr_t current = commands->start;
  do {
    const gala_command_t *cmd = (const gala_command_t *)current;
    switch (cmd->type) {
      case GALA_COMMAND_TYPE_NOP: {
        // Do nothing.
      } break;
      case GALA_COMMAND_TYPE_FENCE_ON_SUBMISSION: {
        const gala_command_fence_t *fence = (const gala_command_fence_t *)cmd;
        bitbyte_foundation_atomic_uint64_store_relaxed(fence->writeback, fence->fence);
      } break;
      case GALA_COMMAND_TYPE_FENCE_ON_COMPLETION: {
        const gala_command_fence_t *fence = (const gala_command_fence_t *)cmd;
        ID3D11Query *query; {
          D3D11_QUERY_DESC qd;
          qd.Query = D3D11_QUERY_EVENT;
          qd.MiscFlags = 0x00000000ul;
          const HRESULT hr = engine->d3d11.device->CreateQuery(&qd, &query);
          gala_assertf(hr == S_OK, "Unable to create query object; ID3D11Device::CreateQuery failed (%x)!", hr);
        }
        engine->d3d11.immediate_context->End(query);
        // HACK(mtwilliams): Poll until the GPU is complete.
        // NOTE(mtwilliams): This isn't truely asynchronous. There might still
        // be another way to achieve this, though.
        while (engine->d3d11.immediate_context->GetData(query, NULL, 0, 0) == S_FALSE);
        query->Release();
        bitbyte_foundation_atomic_uint64_store_relaxed(fence->writeback, fence->fence);
      } break;
      case GALA_D3D11_COMMAND_TYPE_INIT_SWAP_CHAIN: {
        const gala_d3d11_command_init_swap_chain_t *init_swap_chain = (const gala_d3d11_command_init_swap_chain_t *)cmd;
        bitbyte_foundation_mutex_lock(engine->resources.lock);
        /* *init_swap_chain->swap_chain = */ {
          const HRESULT hr = engine->dxgi.factory->CreateSwapChain(engine->d3d11.device,
                                                                   (DXGI_SWAP_CHAIN_DESC *)&init_swap_chain->swap_chain_desc,
                                                                   init_swap_chain->swap_chain);
          gala_assertf(hr == S_OK, "Unable to initalize swap-chain; IDXGIFactory::CreateSwapChain failed (%x)!", hr);
        }
        /* *init_swap_chain->rtv = */ {
          ID3D11Texture2D* back_buffer; {
            const HRESULT hr = (*init_swap_chain->swap_chain)->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&back_buffer);
            gala_assertf(hr == S_OK, "Unable to initalize swap-chain; IDXGISwapChain::GetBuffer failed (%x)!", hr);
          }
          D3D11_RENDER_TARGET_VIEW_DESC rtvd;
          rtvd.Format = init_swap_chain->swap_chain_desc.BufferDesc.Format;
          rtvd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
          rtvd.Texture2D.MipSlice = 0;
          const HRESULT hr = engine->d3d11.device->CreateRenderTargetView((ID3D11Resource *)back_buffer, &rtvd, init_swap_chain->rtv);
          gala_assertf(hr == S_OK, "Unable to initalize swap-chain; ID3D11Device::CreateRenderTargetView failed (%x)!", hr);
          back_buffer->Release();
        }
        bitbyte_foundation_mutex_unlock(engine->resources.lock);
      } break;
      case GALA_D3D11_COMMAND_TYPE_PRESENT: {
        const gala_d3d11_command_present_t *present = (const gala_d3d11_command_present_t *)cmd;
        // TODO(mtwilliams): Expose vertical-sync flag.
        // TODO(mtwilliams): Expose DXGI_PRESENT_DO_NOT_WAIT?
        const HRESULT hr = present->swap_chain->Present(0, 0);
        gala_assertf(hr == S_OK, "Unable to present swap-chain; IDXGISwapChain::Present failed (%x)!", hr);
      } break;
      case GALA_D3D11_COMMAND_TYPE_CLEAR_RENDER_TARGET_VIEW: {
        const gala_d3d11_command_clear_render_target_view_t *clear_render_target_view = (const gala_d3d11_command_clear_render_target_view_t *)cmd;
        engine->d3d11.immediate_context->ClearRenderTargetView(clear_render_target_view->rtv, &clear_render_target_view->rgba[0]);
      } break;
    }
    current += cmd->len;
  } while (current < commands->current);
}

//===----------------------------------------------------------------------===//

int gala_d3d11_engine_to_s(
  const gala_d3d11_engine_t *engine,
  char buf[],
  const int buf_sz)
{
  gala_assert_debug(engine != NULL);
  return snprintf(buf, buf_sz, "#<gala_d3d11_engine_t:%.16" PRIxPTR " ID3D11Device=%.16" PRIxPTR ">", engine, engine->d3d11.device);
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace gala {

//===----------------------------------------------------------------------===//

void D3D11Engine::shutdown_and_destroy() {
  ::gala_d3d11_engine_shutdown_and_destroy((::gala_d3d11_engine_t *)&this->__engine__);
}

//===----------------------------------------------------------------------===//

::gala::SwapChain::Handle D3D11Engine::create_swap_chain() {
  return (::gala::SwapChain::Handle)::gala_d3d11_engine_create_swap_chain((::gala_d3d11_engine_t *)&this->__engine__);
}

//===----------------------------------------------------------------------===//

void D3D11Engine::insert_init_swap_chain(
  ::gala::CommandBuffer *command_buffer,
  const ::gala::SwapChain::Handle swap_chain,
  const ::gala::SwapChain::Description &desc) const
{
  ::gala_d3d11_engine_insert_init_swap_chain((::gala_d3d11_engine_t *)&this->__engine__,
                                        command_buffer->underlying(),
                                        (::gala_swap_chain_hndl_t)swap_chain,
                                        (const ::gala_swap_chain_desc_t *)&desc);
}

//===----------------------------------------------------------------------===//

void D3D11Engine::insert_present(
  ::gala::CommandBuffer *command_buffer,
  ::gala::SwapChain::Handle swap_chain) const
{
  ::gala_d3d11_engine_insert_present((::gala_d3d11_engine_t *)&this->__engine__,
                                     command_buffer->underlying(),
                                     (::gala_swap_chain_hndl_t)swap_chain);
}

//===----------------------------------------------------------------------===//

void D3D11Engine::insert_clear_render_target_view(
  ::gala::CommandBuffer *command_buffer,
  ::gala::Resource::Handle render_target_view,
  const float rgba[4]) const
{
  ::gala_d3d11_engine_insert_clear_render_target_view((::gala_d3d11_engine_t *)&this->__engine__,
                                                      command_buffer->underlying(),
                                                      (::gala_resource_hndl_t)render_target_view,
                                                      rgba);
}

//===----------------------------------------------------------------------===//

void D3D11Engine::execute(const gala::CommandBuffer &commands) {
  ::gala_d3d11_engine_execute((::gala_d3d11_engine_t *)&this->__engine__, commands.underlying());
}

//===----------------------------------------------------------------------===//

int D3D11Engine::to_s(char buf[], const int buf_sz) const {
  const ::gala_d3d11_engine_t *engine = (const ::gala_d3d11_engine_t *)this;
  return snprintf(buf, buf_sz, "#<gala::D3D11Engine:%.16" PRIxPTR " ID3D11Device=%.16" PRIxPTR ">", engine, engine->d3d11.device);
}

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
