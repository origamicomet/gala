//===-- gala/d3d11/engine.h -------------------------------------*- C++ -*-===//
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
///
/// \file
/// \brief
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_D3D11_ENGINE_H_
#define _GALA_D3D11_ENGINE_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"

//===----------------------------------------------------------------------===//

#include "gala/engine.h"

//===----------------------------------------------------------------------===//

#include "gala/d3d11/swap_chain.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_d3d11_engine gala_d3d11_engine_t;

//===----------------------------------------------------------------------===//

/// \brief
/// \param engine
/// \returns
///
extern GALA_PUBLIC void
gala_d3d11_engine_shutdown_and_destroy(
  gala_d3d11_engine_t *engine);

//===----------------------------------------------------------------------===//

/// \brief
/// \param engine
/// \returns
///
extern GALA_PUBLIC gala_swap_chain_hndl_t
gala_d3d11_engine_create_swap_chain(
  gala_d3d11_engine_t *engine);

//===----------------------------------------------------------------------===//

/// \brief
/// \param engine
/// \param command_buffer
/// \param swap_chain
/// \param desc
/// \returns
///
extern GALA_PUBLIC void
gala_d3d11_engine_insert_init_swap_chain(
  const gala_d3d11_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  const gala_swap_chain_hndl_t swap_chain,
  const gala_swap_chain_desc_t *desc);

//===----------------------------------------------------------------------===//

/// \brief
/// \param engine
/// \param command_buffer
/// \param render_target_view
/// \param rgba
/// \returns
///
extern GALA_PUBLIC void
gala_d3d11_engine_insert_clear_render_target_view(
  const gala_d3d11_engine_t *engine,
  gala_command_buffer_t *command_buffer,
  const gala_resource_hndl_t render_target_view,
  const float rgba[4]);

//===----------------------------------------------------------------------===//

/// \brief
/// \param engine
/// \param commands
///
extern GALA_PUBLIC void
gala_d3d11_engine_execute(
  gala_d3d11_engine_t *engine,
  const gala_command_buffer_t *commands);

//===----------------------------------------------------------------------===//

/// \brief
/// \param engine
/// \param buf
/// \param buf_sz
/// \returns
///
extern GALA_PUBLIC int
gala_d3d11_engine_to_s(
  const gala_d3d11_engine_t *engine,
  char buf[],
  const int buf_sz);

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace gala {

//===----------------------------------------------------------------------===//

/// \copydoc ::gala_d3d11_engine_t
class GALA_PUBLIC D3D11Engine : public ::gala::Engine {
 public:
  /// \copydoc ::gala_d3d11_engine_shutdown_and_destroy
  void shutdown_and_destroy();

 public:
  /// \copydoc ::gala_d3d11_engine_create_swap_chain
  ::gala::SwapChain::Handle create_swap_chain();

 public:
  /// \copydoc ::gala_d3d11_engine_insert_init_swap_chain
  void insert_init_swap_chain(
    ::gala::CommandBuffer *command_buffer,
    ::gala::SwapChain::Handle swap_chain,
    const ::gala::SwapChain::Description &desc) const;

  /// \copydoc ::gala_d3d11_engine_insert_clear_render_target_view
  void insert_clear_render_target_view(
    ::gala::CommandBuffer *command_buffer,
    ::gala::Resource::Handle render_target_view,
    const float rgba[4]) const;

 public:
  /// \copydoc ::gala_d3d11_engine_execute
  void execute(const gala::CommandBuffer &commands);

 public:
  /// \copydoc ::gala_d3d11_engine_to_s
  int to_s(char buf[], const int buf_sz) const;
};

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_D3D11_ENGINE_H_

//============================================================================//
