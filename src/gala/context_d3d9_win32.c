//===-- gala/context_d3d9_win32.c -------------------------------*- C++ -*-===//
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

#include "gala/context_d3d9_win32.h"

//===----------------------------------------------------------------------===//

#include "gala/pixel_format_d3d9_win32.h"
#include "gala/swap_chain_d3d9_win32.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

gala_error_t gala_context_create_swap_chain_d3d9(
  gala_context_t *context_,
  const gala_swap_chain_opts_t *opts,
  gala_swap_chain_t **swap_chain_,
  const gala_error_details_t **error_details)
{
  gala_assert(context_ != NULL);
  gala_assert(opts != NULL);
  gala_assert(swap_chain_ != NULL);

  gala_context_d3d9_t *context = (gala_context_d3d9_t *)context_;

  D3DPRESENT_PARAMETERS PresentParameters;
  PresentParameters.BackBufferWidth = opts->width;
  PresentParameters.BackBufferHeight = opts->height;
  PresentParameters.BackBufferFormat = gala_pixel_format_to_d3d9(opts->format);
  gala_assertf((PresentParameters.BackBufferFormat == GALA_PIXEL_FORMAT_R8G8B8) ||
               (PresentParameters.BackBufferFormat != GALA_PIXEL_FORMAT_R8G8B8A8),
               "Unsupported back-buffer format.");
  PresentParameters.BackBufferCount = 1;
  PresentParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
  PresentParameters.MultiSampleQuality = 0;
  PresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
  PresentParameters.hDeviceWindow = opts->hWnd;
  gala_assertf(opts->hWnd != NULL, "No window specified.");
  PresentParameters.Windowed = !opts->fullscreen;
  PresentParameters.EnableAutoDepthStencil = FALSE;
  PresentParameters.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
  PresentParameters.Flags = 0;
  PresentParameters.FullScreen_RefreshRateInHz = opts->refresh_rate.numer;
  gala_assertf((opts->refresh_rate.denom <= 1), "Unsupported refresh rate.");
  PresentParameters.PresentationInterval = opts->vsync ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;

  gala_swap_chain_d3d9_t *swap_chain = (gala_swap_chain_d3d9_t *)calloc(sizeof(gala_swap_chain_d3d9_t), 1);
  swap_chain->__swap_chain__._backend = context->__context__._backend;

  const HRESULT hrCreateAdditionalSwapChain =
    context->Direct3DDevice9->CreateAdditionalSwapChain(&PresentParameters,
                                                        &swap_chain->Direct3DSwapChain9);

  gala_assertf(hrCreateAdditionalSwapChain == D3D_OK,
               "Unable to create additional swap-chain! (hresult=%x)",
               hrCreateAdditionalSwapChain);

  *swap_chain_ = (gala_swap_chain_t *)swap_chain;
  if (error_details)
    *error_details = NULL;
  return GALA_ERROR_NONE;
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//
