/*===-- gala/resource.h -----------------------------------------*- C++ -*-===*/
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

#ifndef _GALA_RESOURCE_H_
#define _GALA_RESOURCE_H_

/*============================================================================*/

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"

/*============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*===----------------------------------------------------------------------===*/

/*! ... */
typedef enum gala_resource_type {
  /*! Invalid. */
  GALA_RESOURCE_TYPE_INVALID = 0,
  /*! Swap-chain. */
  GALA_RESOURCE_TYPE_SWAP_CHAIN = 1,
  /*! Render Target View. */
  GALA_RESOURCE_TYPE_RENDER_TARGET_VIEW = 2,
  /*! Depth-stencil Target View. */
  GALA_RESOURCE_TYPE_DEPTH_STENCIL_TARGET_VIEW = 3,
  /*! \internal Force at least uint32_t storage and alignment. */
  GALA_RESOURCE_TYPE_FORCE_UINT32 = 0x7fffffff
} gala_resource_type_t;

/*===----------------------------------------------------------------------===*/

/*! ... */
typedef struct gala_resource {
  /*! ... */
  gala_resource_type_t type;
} gala_resource_t;

/*===----------------------------------------------------------------------===*/

/*! ... */
typedef uintptr_t gala_resource_hndl_t;

/*! \def GALA_INVALID_RESOURCE_HANDLE
 *  \brief ...
 */
#define GALA_INVALID_RESOURCE_HANDLE \
  ((gala_resource_hndl_t)NULL)

/*===----------------------------------------------------------------------===*/

/*! ... */
typedef gala_resource_hndl_t gala_swap_chain_hndl_t;

/*! \def GALA_INVALID_SWAP_CHAIN_HANDLE
 *  \brief ...
 */
#define GALA_INVALID_SWAP_CHAIN_HANDLE \
  GALA_INVALID_RESOURCE_HANDLE

/*===----------------------------------------------------------------------===*/

/*! ... */
typedef gala_resource_hndl_t gala_render_target_view_hndl_t;

/*! \def GALA_INVALID_RENDER_TARGET_VIEW_HANDLE
 *  \brief ...
 */
#define GALA_INVALID_RENDER_TARGET_VIEW_HANDLE \
  GALA_INVALID_RESOURCE_HANDLE

/*===----------------------------------------------------------------------===*/

/*! ... */
typedef gala_resource_hndl_t gala_depth_stencil_target_view_hndl_t;

/*! \def GALA_INVALID_DEPTH_STENCIL_TARGET_VIEW_HANDLE
 *  \brief ...
 */
#define GALA_INVALID_DEPTH_STENCIL_TARGET_VIEW_HANDLE \
  GALA_INVALID_RESOURCE_HANDLE

/*===----------------------------------------------------------------------===*/

#ifdef __cplusplus
}
#endif // __cplusplus

/*============================================================================*/

#ifdef __cplusplus

/*===----------------------------------------------------------------------===*/

namespace gala {

/*===----------------------------------------------------------------------===*/

/*! \copydoc ::gala_resource_t */
struct GALA_PUBLIC Resource : public ::gala_resource_t {
  /*! \copydoc ::gala_resource_type_t */
  enum Type {
    /*! \copydoc ::GALA_RESOURCE_TYPE_INVALID */
    kInvalid = ::GALA_RESOURCE_TYPE_INVALID,
    /*! \copydoc ::GALA_RESOURCE_TYPE_SWAP_CHAIN */
    kSwapChain = ::GALA_RESOURCE_TYPE_SWAP_CHAIN,
    /*! \copydoc ::GALA_RESOURCE_TYPE_RENDER_TARGET_VIEW */
    kRenderTargetView = ::GALA_RESOURCE_TYPE_RENDER_TARGET_VIEW,
    /*! \copydoc ::GALA_RESOURCE_TYPE_DEPTH_STENCIL_TARGET_VIEW */
    kDepthStencilTargetView = ::GALA_RESOURCE_TYPE_DEPTH_STENCIL_TARGET_VIEW
  };

  /*! \copydoc ::gala_resource_hndl_t */
  typedef ::gala_resource_hndl_t Handle;
};

/*===----------------------------------------------------------------------===*/

/*! ... */
struct GALA_PUBLIC RenderTargetView : public ::gala::Resource {
  /*! \copydoc ::gala_render_target_view_hndl_t */
  typedef ::gala_render_target_view_hndl_t Handle;
};

/*===----------------------------------------------------------------------===*/

/*! ... */
struct GALA_PUBLIC DepthStencilTargetView : public ::gala::Resource {
  /*! \copydoc ::gala_depth_stencil_target_view_hndl_t */
  typedef ::gala_depth_stencil_target_view_hndl_t Handle;
};

/*===----------------------------------------------------------------------===*/

} // gala

/*===----------------------------------------------------------------------===*/

#endif // __cplusplus

/*============================================================================*/

#endif // _GALA_RESOURCE_H_

/*============================================================================*/
