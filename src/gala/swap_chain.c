/*===-- gala/swap_chain.c ---------------------------------------*- C++ -*-===*/
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

#include "gala/swap_chain.h"

/*============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*===----------------------------------------------------------------------===*/

void
gala_swap_chain_init(
  gala_swap_chain_t *swap_chain)
{
  gala_assert_debug(swap_chain != NULL);
  swap_chain->__resource__.type = GALA_RESOURCE_TYPE_SWAP_CHAIN;
}

//===----------------------------------------------------------------------===//

void
gala_swap_chain_destroy(
  gala_swap_chain_t *swap_chain)
{
  gala_assert_debug(swap_chain != NULL);
#if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
  /* This might help find some (stupid) bugs. */
  swap_chain->__resource__.type = GALA_RESOURCE_TYPE_INVALID;
#endif
}

/*===----------------------------------------------------------------------===*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*============================================================================*/

#ifdef __cplusplus

/*===----------------------------------------------------------------------===*/

namespace gala {

/*===----------------------------------------------------------------------===*/

void SwapChain::init(::gala::SwapChain *swap_chain) {
  ::gala_swap_chain_init(&swap_chain->__swap_chain__);
}

/*===----------------------------------------------------------------------===*/

void SwapChain::destroy() {
  ::gala_swap_chain_destroy(&this->__swap_chain__);
}

/*===----------------------------------------------------------------------===*/

} /* gala */

/*===----------------------------------------------------------------------===*/

#endif /* __cplusplus */

/*============================================================================*/
