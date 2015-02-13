//===-- gala/swap_chain_d3d9_win32.h ----------------------------*- C++ -*-===//
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
/// \brief TODO(mike): Document this file.
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_SWAP_CHAIN_D3D9_WIN32_H_
#define _GALA_SWAP_CHAIN_D3D9_WIN32_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"
#include "gala/error.h"
#include "gala/swap_chain.h"

//===----------------------------------------------------------------------===//

#define _WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d9.h>

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_swap_chain_d3d9 {
  /// \copydoc ::gala_swap_chain_t
  gala_swap_chain_t __swap_chain__;
  /// TODO(mike): Document this.
  IDirect3DSwapChain9 *Direct3DSwapChain9;
} gala_swap_chain_d3d9_t;

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#endif // _GALA_SWAP_CHAIN_D3D9_WIN32_H_

//============================================================================//
