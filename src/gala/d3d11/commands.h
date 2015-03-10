/*===-- gala/d3d11/commands.h -----------------------------------*- C++ -*-===*/
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

#ifndef _GALA_D3D11_COMMANDS_H_
#define _GALA_D3D11_COMMANDS_H_

/*============================================================================*/

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"

/*===----------------------------------------------------------------------===*/

#include "gala/command.h"
#include "gala/commands.h"

/*============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*===----------------------------------------------------------------------===*/

/*! ... */
typedef enum gala_d3d11_command_type {
  /*! Initializes a swap-chain. */
  GALA_D3D11_COMMAND_TYPE_INIT_SWAP_CHAIN = 1 | (1 << 31u),
} gala_d3d11_command_type_t;

/*===----------------------------------------------------------------------===*/

/*! ... */
typedef struct gala_d3d11_command_init_swap_chain {
  struct gala_command __command__;
  DXGI_SWAP_CHAIN_DESC swap_chain_desc;
  IDXGISwapChain **swap_chain;
  ID3D11RenderTargetView **rtv;
} gala_d3d11_command_init_swap_chain_t;

/*===----------------------------------------------------------------------===*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*============================================================================*/

#endif /* _GALA_D3D11_COMMANDS_H_ */

/*============================================================================*/
