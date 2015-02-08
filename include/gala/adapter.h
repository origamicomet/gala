//===-- gala/adapter.h ------------------------------------------*- C++ -*-===//
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
/// \brief TODO(mike): Document this file.
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_ADAPTER_H_
#define _GALA_ADAPTER_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"
#include "gala/error.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef enum gala_adapter_type {
  /// Unknown.
  GALA_ADAPTER_UNKNOWN = 0,
  /// Software.
  GALA_ADAPTER_SOFTWARE = 1,
  /// Hardware.
  GALA_ADAPTER_HARDWARE = 2,
  /// Proxy.
  GALA_ADAPTER_PROXY = 3
} gala_adapter_type_t;

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_adapter {
  /// \copydoc ::gala_adapter_type_t
  gala_adapter_type_t type;
  /// TOOD(mike): Document this.
  char desc[65];
  /// TODO(mike): Document this.
  size_t num_outputs;
  /// TODO(mike): Document this.
  const struct gala_output **outputs;
  /// The backend this belongs to.
  struct gala_backend *_backend;
} gala_adapter_t;

//===----------------------------------------------------------------------===//

/// \brief
/// \param adapter
/// \param buf
/// \param buf_sz
/// \param error_details
/// \returns
///
extern
GALA_PUBLIC
gala_error_t gala_adapter_to_s(
  const gala_adapter_t *adapter,
  char *buf,
  const size_t buf_sz,
  const gala_error_details_t **error_details);

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace gala {

//===----------------------------------------------------------------------===//

/// \copydoc ::gala_adapter_t
class Adapter {
 public:
  /// \copydoc ::gala_adapter_type_t
  enum Type {
    /// \copydoc ::GALA_ADAPTER_UNKNOWN
    kUnknown = ::GALA_ADAPTER_UNKNOWN,
    /// \copydoc ::GALA_ADAPTER_SOFTWARE
    kSoftware = ::GALA_ADAPTER_SOFTWARE,
    /// \copydoc ::GALA_ADAPTER_HARDWARE
    kHardware = ::GALA_ADAPTER_HARDWARE,
    /// \copydoc ::GALA_ADAPTER_PROXY
    kProxy = ::GALA_ADAPTER_PROXY
  };

 public:
  /// \copydoc ::gala_adapter_to_s
  ::gala::Error to_s(
    char *buf,
    const size_t buf_sz,
    const ::gala::ErrorDetails **error_details = NULL) const
  {
    return (::gala::Error)::gala_adapter_to_s(&__adapter__,
                                              buf, buf_sz,
                                              (const ::gala_error_details_t **)error_details);
  }

 public:
  /// \copydoc ::gala_adapter_t::type
  ::gala::Adapter::Type type() const {
    return (::gala::Adapter::Type)__adapter__.type;
  }

 public:
  ::gala_adapter_t __adapter__;
};

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_ADAPTER_H_

//============================================================================//
