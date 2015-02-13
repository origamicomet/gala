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
/// \brief
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_ADAPTER_H_
#define _GALA_ADAPTER_H_

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
  ///
  gala_adapter_type_t type;
  ///
  char desc[65];
} gala_adapter_t;

//===----------------------------------------------------------------------===//

/// \brief
/// \param adapter
/// \returns
///
extern
GALA_PUBLIC
void
gala_adapter_init(
  gala_adapter_t *adapter);

//===----------------------------------------------------------------------===//

/// \brief
/// \param adapter
/// \returns
///
extern
GALA_PUBLIC
void
gala_adapter_destroy(
  gala_adapter_t *adapter);

//===----------------------------------------------------------------------===//

/// \brief
/// \param adapter
/// \param buf
/// \param buf_sz
/// \returns
///
extern
GALA_PUBLIC
int
gala_adapter_to_s(
  const gala_adapter_t *adapter,
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

/// \copydoc ::gala_adapter_t
class GALA_PUBLIC Adapter {
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
  /// \copydoc ::gala_adapter_init
  static void init(::gala::Adapter *adapter) {
    ::gala_adapter_init(&adapter->__adapter__);
  }

  /// \copydoc ::gala_adapter_destroy
  void destroy() {
    ::gala_adapter_destroy(&this->__adapter__);
  }

 public:
  /// \copydoc ::gala_adapter_to_s
  int to_s(char buf[], const int buf_sz) const {
    return ::gala_adapter_to_s(&this->__adapter__, buf, buf_sz);
  }

 public:
  /// \copydoc ::gala_adapter_t::type
  ::gala::Adapter::Type type() const {
    return (::gala::Adapter::Type)this->__adapter__.type;
  }

  /// \copydoc ::gala_adapter_t::desc
  const char *desc() const {
    return &this->__adapter__.desc[0];
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
