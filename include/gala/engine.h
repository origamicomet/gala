//===-- gala/engine.h -----------------------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//
//
// TODO(mtwilliams): Document the purpose of this file.
//
//===----------------------------------------------------------------------===//

#ifndef _GALA_ENGINE_H_
#define _GALA_ENGINE_H_

#include "gala/foundation.h"

#include "gala/backend.h"

#include "gala/resource.h"
#include "gala/resources.h"
#include "gala/resource_table.h"

#include "gala/command.h"
#include "gala/commands.h"
#include "gala/command_buffer.h"

GALA_BEGIN_EXTERN_C

typedef enum gala_engine_type {
  /// Invalid.
  GALA_ENGINE_TYPE_INVALID = 0,

  /// Software.
  GALA_ENGINE_TYPE_SOFTWARE = 1,

  /// Hardware.
  GALA_ENGINE_TYPE_HARDWARE = 2,

  /// \internal Force gala_uint32_t storage and alignment.
  GALA_ENGINE_TYPE_FORCE_UINT32 = 0x7fffffff
} gala_engine_type_t;

typedef enum gala_engine_flags {
  /// Enable debugging functionality.
  GALA_ENGINE_DEBUG = (1 << 0),
} gala_engine_flags_t;

typedef struct gala_engine_creation_params {
  ///
  gala_engine_type_t type;

  ///
  uint32_t flags;
} gala_engine_creation_params_t;

/// \brief
typedef struct gala_engine {
  struct {
    gala_backend_t backend;
    gala_engine_type_t type;
    gala_uint32_t flags;
  } meta;

  /// \copydoc ::gala_resource_table_t
  struct gala_resource_table *resource_table;

  /// \brief Executes the command buffer.
  void (*execute)(struct gala_engine *engine,
                  const struct gala_command_buffer *command_buffer);
} gala_engine_t;

GALA_END_EXTERN_C

#endif // _GALA_ENGINE_H_
