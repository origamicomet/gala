//===-- gala/engine.h ------------------------------------------*- C++ -*-===//
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
/// \brief
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_ENGINE_H_
#define _GALA_ENGINE_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"

//===----------------------------------------------------------------------===//

#include "gala/adapter.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef enum gala_engine_type {
  /// Invalid.
  GALA_ENGINE_TYPE_INVALID = 0,
  /// Software.
  GALA_ENGINE_TYPE_SOFTWARE = 1,
  /// Hardware.
  GALA_ENGINE_TYPE_HARDWARE = 2,
  /// \internal Force at least uint32_t storage and alignment.
  GALA_ENGINE_TYPE_FORCE_UINT32 = 0x7fffffff
} gala_engine_type_t;

//===----------------------------------------------------------------------===//

/// \brief
///
typedef enum gala_engine_flags {
  /// Enable debugging functionality.
  GALA_ENGINE_DEBUG = (1 << 0),
} gala_engine_flags_t;

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_engine_creation_params {
  ///
  gala_engine_type_t type;
  ///
  uint32_t flags;
  ///
  gala_adapter_t *adapter;
} gala_engine_creation_params_t;

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_engine {
  /// \copydoc ::gala_engine_type_t
  gala_engine_type_t type;
  /// \copydoc ::gala_engine_flags_t
  uint32_t flags;
} gala_engine_t;

//===----------------------------------------------------------------------===//

/// \brief
/// \param engine
/// \returns
///
extern GALA_PUBLIC void
gala_engine_init(
  gala_engine_t *engine);

//===----------------------------------------------------------------------===//

/// \brief
/// \param engine
/// \returns
///
extern GALA_PUBLIC void
gala_engine_shutdown(
  gala_engine_t *engine);

//===----------------------------------------------------------------------===//

/// \brief
/// \param engine
/// \param buf
/// \param buf_sz
/// \returns
///
extern GALA_PUBLIC int
gala_engine_to_s(
  const gala_engine_t *engine,
  char buf[],
  const int buf_sz);

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace gala {

//===----------------------------------------------------------------------===//

/// \copydoc ::gala_engine_t
class GALA_PUBLIC Engine {
 public:
  /// \copydoc ::gala_engine_type_t
  enum Type {
    /// \copydoc ::GALA_ENGINE_TYPE_INVALID
    kInvalid = ::GALA_ENGINE_TYPE_INVALID,
    /// \copydoc ::GALA_ENGINE_TYPE_SOFTWARE
    kSoftware = ::GALA_ENGINE_TYPE_SOFTWARE,
    /// \copydoc ::GALA_ENGINE_TYPE_HARDWARE
    kHardware = ::GALA_ENGINE_TYPE_HARDWARE
  };

  /// \copydoc ::gala_engine_flags_t
  enum Flags {
    /// \copydoc ::GALA_ENGINE_DEBUG
    kDebug = ::GALA_ENGINE_DEBUG
  };

 public:
  /// \copydoc ::gala_engine_init
  static void init(::gala::Engine *engine);

  /// \copydoc ::gala_engine_shutdown
  void shutdown();

 public:
  /// \copydoc ::gala_engine_to_s
  int to_s(char buf[], const int buf_sz) const;

 public:
  ::gala_engine_t __engine__;
};

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_ENGINE_H_

//============================================================================//
