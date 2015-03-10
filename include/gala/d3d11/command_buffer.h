/*===-- gala/d3d11/command_buffer.h -----------------------------*- C++ -*-===*/
/*
 *  Gala
 *
 *  This file is distributed under the terms described in LICENSE.
 *
 *  Author(s):
 *
 *    * Michael Williams <mike@origamicomet.com>
 *                                                                            */
/*===----------------------------------------------------------------------===*/
/*!
 *  \file
 *  \brief
 *                                                                            */
/*===----------------------------------------------------------------------===*/

#ifndef _GALA_D3D11_COMMAND_BUFFER_H_
#define _GALA_D3D11_COMMAND_BUFFER_H_

/*============================================================================*/

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"

/*===----------------------------------------------------------------------===*/

#include "gala/command_buffer.h"

/*============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*===----------------------------------------------------------------------===*/

/*! */
typedef struct gala_d3d11_command_buffer {
  /* TODO(mtwilliams): Move into */
  gala_command_buffer_t __command_buffer__;
} gala_d3d11_command_buffer_t;

/*===----------------------------------------------------------------------===*/

/*! */
extern GALA_PUBLIC void
gala_d3d11_command_buffer_insert_init_swap_chain(
  gala_command_buffer_t *command_buffer,
  gala_swap_chain_handle_t );

/*===----------------------------------------------------------------------===*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*============================================================================*/

#ifdef __cplusplus

/*===----------------------------------------------------------------------===*/

namespace gala {

/*===----------------------------------------------------------------------===*/

/*! \copydoc ::gala::CommandBuffer */
class GALA_PUBLIC D3D11CommandBuffer : public ::gala::CommandBuffer {
 public:
  /*! \copydoc ::gala_d3d11_command_buffer_insert_init_swap_chain */
  void insert_init_swap_chain(
    const ::gala::SwapChain::Handle swap_chain_handle,
    const ::gala::SwapChain::Description &swap_chain_desc);
};

/*===----------------------------------------------------------------------===*/

} /* gala */

/*===----------------------------------------------------------------------===*/

#endif /* __cplusplus */

/*============================================================================*/

#endif /* _GALA_D3D11_COMMAND_BUFFER_H_ */

/*============================================================================*/
