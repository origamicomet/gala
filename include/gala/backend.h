//===-- gala/backend.h ------------------------------------------*- C++ -*-===//
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

#ifndef _GALA_BACKEND_H_
#define _GALA_BACKEND_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef enum gala_backend_type {
  /// Invalid.
  GALA_BACKEND_TYPE_INVALID = 0,
  /// Null.
  GALA_BACKEND_TYPE_NULL = 1,
  /// Direct3D9(Ex).
  GALA_BACKEND_TYPE_D3D9 = 2,
  /// \internal Force at least uint32_t storage and alignment.
  GALA_BACKEND_TYPE_FORCE_UINT32 = 0x7fffffff
} gala_backend_type_t;

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_backend {
  /// \copydoc ::gala_backend_type_t
  gala_backend_type_t type;
} gala_backend_t;

//===----------------------------------------------------------------------===//

/// \brief
/// \param backend
/// \returns
///
extern GALA_PUBLIC void
gala_backend_init(
  gala_backend_t *backend);

//===----------------------------------------------------------------------===//

/// \brief
/// \param backend
/// \returns
///
extern GALA_PUBLIC void
gala_backend_shutdown(
  gala_backend_t *backend);

//===----------------------------------------------------------------------===//

/// \brief
/// \param backend
/// \param buf
/// \param buf_sz
/// \returns
///
extern GALA_PUBLIC int
gala_backend_to_s(
  const gala_backend_t *backend,
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

/// \copydoc ::gala_backend_t
class GALA_PUBLIC Backend {
 public:
  /// \copydoc ::gala_backend_type_t
  enum Type {
    /// \copydoc ::GALA_BACKEND_TYPE_INVALID
    kUnknown = ::GALA_BACKEND_TYPE_INVALID,
    /// \copydoc ::GALA_BACKEND_TYPE_NULL
    kNull = ::GALA_BACKEND_TYPE_NULL,
    /// \copydoc ::GALA_BACKEND_TYPE_D3D9
    kDirect3D9 = ::GALA_BACKEND_TYPE_D3D9
  };

 public:
  /// \copydoc ::gala_backend_init
  static void init(::gala::Backend *backend) {
    ::gala_backend_init(&backend->__backend__);
  }

  /// \copydoc ::gala_backend_shutdown
  void shutdown() {
    ::gala_backend_shutdown(&this->__backend__);
  }

 public:
  /// \copydoc ::gala_backend_to_s
  int to_s(char buf[], const int buf_sz) const {
    return snprintf(buf, buf_sz, "#<gala::Backend:%.16" PRIxPTR ">", this);
  }

 public:
  ::gala_backend_t __backend__;
};

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_BACKEND_H_

//============================================================================//
