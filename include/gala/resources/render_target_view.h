//===-- gala/resources/render_target_view.h -------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_RESOURCES_RENDER_TARGET_VIEW_H_
#define _GALA_RESOURCES_RENDER_TARGET_VIEW_H_

#include "gala/resource.h"

GALA_BEGIN_EXTERN_C

typedef gala_resource_handle_t gala_render_target_view_handle_t;

typedef struct gala_render_target_view_desc {
  // ...
} gala_render_target_view_desc_t;

/// \def GALA_INVALID_RENDER_TARGET_VIEW_HANDLE
/// \copydoc GALA_INVALID_RESOURCE_HANDLE
#define GALA_INVALID_RENDER_TARGET_VIEW_HANDLE \
  GALA_INVALID_RESOURCE_HANDLE

GALA_END_EXTERN_C

#endif // _GALA_RESOURCES_RENDER_TARGET_VIEW_H_
