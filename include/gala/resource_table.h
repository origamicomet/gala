//===-- gala/resource_table.h ---------------------------*- mode: C++11 -*-===//
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

#ifndef _GALA_RESOURCE_TABLE_H_
#define _GALA_RESOURCE_TABLE_H_

#include "gala/foundation.h"

#include "gala/resource.h"

GALA_BEGIN_EXTERN_C

// TODO(mtwilliams): Describe resource tables.
typedef struct gala_resource_table gala_resource_table_t;

/// \brief Creates a resource-table with reasonable defaults.
/// \returns A resource-table.
extern GALA_PUBLIC
gala_resource_table *gala_resource_table_create(void);

/// \brief Destroy @resource_table.
extern GALA_PUBLIC
void gala_resource_table_destroy(
  gala_resource_table *resource_table);

/// \brief Allocates a resource handle from @resource_table.
/// \returns A handle.
extern GALA_PUBLIC
gala_resource_handle_t gala_resource_table_allocate(
  gala_resource_table_t *resource_table);

/// \brief Frees @handle allocated from @resource_table.
/// \returns A handle.
extern GALA_PUBLIC
void gala_resource_table_free(
  gala_resource_table_t *resource_table,
  gala_resource_handle_t handle);

/// \brief Converts @handle to the associated resource.
/// \returns The associated resource.
extern GALA_PUBLIC
gala_resource_t *gala_resource_table_lookup(
  const gala_resource_table_t *resource_table,
  gala_resource_handle_t handle);

GALA_END_EXTERN_C

#endif // _GALA_RESOURCE_TABLE_H_
