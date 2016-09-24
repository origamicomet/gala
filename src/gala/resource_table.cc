//===-- gala/resource_table.cc --------------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//

#include "gala/resource_table.h"

GALA_BEGIN_EXTERN_C

struct gala_resource_table {
  gala_resource_t *resources;

  gala_uint32_t allocated;
  gala_uint32_t freed;

  gala_uint32_t size;
};

// TODO(mtwilliams): Don't use `malloc` and `free`?

void gala_resource_table_init(void)
{
  gala_resource_table *resource_table =
    (gala_resource_table_t *)malloc(sizeof(gala_resource_table_t));

  gala_assert_debug(resource_table != NULL);

  resource_table->resources = (gala_resource_t *)malloc(sizeof(gala_resource_t) * 65535);

  // We reuse `resource_table->resources` to store a free-list.
  resource_table->allocated = 0;
  resource_table->freed = GALA_INVALID_RESOURCE_HANDLE;

  resource_table->size = 65535;
}

void gala_resource_table_destroy(
  gala_resource_table *resource_table)
{
  gala_assert_debug(resource_table != NULL);

  free((void *)resource_table->resources);
  free((void *)resource_table);
}

gala_resource_handle_t gala_resource_table_allocate(
  gala_resource_table_t *resource_table)
{
  gala_assert_debug(resource_table != NULL);

try_allocate:
  const gala_uint32_t freed = gala_atomic_load_u32(&resource_table->freed);
  const gala_uint32_t allocated = gala_atomic_load_u32(&resource_table->allocated);

  if (freed == GALA_INVALID_RESOURCE_HANDLE) {
    // No holes in our table; just bump `allocated`.
    const gala_uint32_t handle = gala_atomic_add_u32(&resource_table->allocated, 1);
    gala_assert_development(handle < resource_table->size);
    return handle;
  } else {
    // Have a hole! Try to grab the slot via our free-list.
    const gala_uint32_t next =
      gala_atomic_load_u32((gala_uint32_t *)&resource_table->resources[freed]);

    if (gala_atomic_cmp_and_xchg_u32(&resource_table->freed, freed, next) != freed)
      // Lost to another thread :(
      goto try_allocate;

    // Got it!
    return freed;
  }
}

void gala_resource_table_free(
  gala_resource_table_t *resource_table,
  gala_resource_handle_t handle)
{
  gala_assert_debug(resource_table != NULL);
  gala_assert_debug(handle != GALA_INVALID_RESOURCE_HANDLE);

  const gala_uint32_t allocated = gala_atomic_load_u32(&resource_table->allocated);

  if (handle == (allocated - 1)) {
    // Last allocated slot; try to bump `allocated`.
    if (gala_atomic_cmp_and_xchg_u32(&resource_table->allocated, allocated, allocated - 1) == allocated)
      return;
  }

  // Not (or no longer) the last allocated slot; put into free-list.
try_free:
  const gala_uint32_t next = gala_atomic_load_u32(&resource_table->freed);
  gala_atomic_store_u32((gala_uint32_t *)&resource_table->resources[handle], next);
  if (gala_atomic_cmp_and_xchg_u32(&resource_table->freed, next, handle) != next)
    // Lost to another thread :(
    goto try_free;
}

gala_resource_t *gala_resource_table_lookup(
  const gala_resource_table_t *resource_table,
  gala_resource_handle_t handle)
{
  gala_assert_debug(resource_table != NULL);
  gala_assert_debug(handle != GALA_INVALID_RESOURCE_HANDLE);

  return &resource_table->resources[handle];
}

GALA_END_EXTERN_C
