/*===-- gala/swap_chain.h ---------------------------------------*- C++ -*-===*/
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

#ifndef _GALA_SWAP_CHAIN_H_
#define _GALA_SWAP_CHAIN_H_

/*============================================================================*/

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"

/*===----------------------------------------------------------------------===*/

#include "gala/resource.h"

/*============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*===----------------------------------------------------------------------===*/

/*! ... */
typedef struct gala_swap_chain {
  gala_resource_t __resource__;
} gala_swap_chain_t;

/*! ... */
typedef gala_resource_hndl_t gala_swap_chain_hndl_t;

/*! \def GALA_INVALID_SWAP_CHAIN_HANDLE
 *  \brief ...
 */
#define GALA_INVALID_SWAP_CHAIN_HANDLE \
  GALA_INVALID_RESOURCE_HANDLE

/*===----------------------------------------------------------------------===*/

/*! \brief
 *  \param swap_chain
 */
extern GALA_PUBLIC void
gala_swap_chain_init(
  gala_swap_chain_t *swap_chain);

//===----------------------------------------------------------------------===//

/*! \brief
 *  \param swap_chain
 */
extern GALA_PUBLIC void
gala_swap_chain_destroy(
  gala_swap_chain_t *swap_chain);

/*===----------------------------------------------------------------------===*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*============================================================================*/

#ifdef __cplusplus

/*===----------------------------------------------------------------------===*/

namespace gala {

/*===----------------------------------------------------------------------===*/

/*! ... */
class GALA_PUBLIC SwapChain {
 public:
  /*! \copydoc ::gala_swap_chain_hndl_t */
  typedef ::gala_swap_chain_hndl_t Handle;

 public:
  /*! \copydoc ::gala_swap_chain_init */
  static void init(::gala::SwapChain *swap_chain);

  /*! \copydoc ::gala_swap_chain_destroy */
  void destroy();

 private:
  ::gala_swap_chain_t __swap_chain__;
};

/*===----------------------------------------------------------------------===*/

} /* gala */

/*===----------------------------------------------------------------------===*/

#endif /* __cplusplus */

/*============================================================================*/

#endif /* _GALA_SWAP_CHAIN_H_ */

/*============================================================================*/
