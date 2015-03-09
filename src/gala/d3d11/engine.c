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
  engine->dxgi.factory->Release();
  engine->d3d11.immediate_context->Release();
  engine->d3d11.device->Release();
  FreeLibrary(engine->d3d11.dll);
#if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
  // This might help find some (stupid) bugs.
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

void
gala_d3d11_engine_execute(
  gala_d3d11_engine_t *engine,
  const gala_command_buffer_t *commands)
{
  gala_assert_debug(engine != NULL);
  gala_assert_debug(commands->start <= commands->current);

  uintptr_t current = commands->start;
  do {
    const gala_command_t *command = (const gala_command_t *)current;
    switch (command->type) {
      case GALA_COMMAND_TYPE_NOP: {
        // Do nothing.
      } break;
      case GALA_COMMAND_TYPE_FENCE_ON_SUBMISSION: {
        const gala_command_fence_t *fence = (const gala_command_fence_t *)command;
        bitbyte_foundation_atomic_uint64_store_relaxed(fence->writeback, fence->fence);
      } break;
      case GALA_COMMAND_TYPE_FENCE_ON_COMPLETION: {
        // TODO(mtwilliams): Implement FENNCE_ON_COMPLETION.
      } break;
    }
    current += command->len;
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
