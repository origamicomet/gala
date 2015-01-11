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
  /// Software
  GALA_ADAPTER_SOFTWARE = 1,
  /// Hardware
  GALA_ADAPTER_HARDWARE = 2,
  /// Proxy
  GALA_ADAPTER_PROXY = 3,
} gala_adapter_type_t;

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_adapter {
  ///
  gala_adapter_type_t type;
  ///
  size_t num_outputs;
  ///
  const struct gala_output **outputs;
} gala_adapter_t;

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//===----------------------------------------------------------------------===//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace gala {

//===----------------------------------------------------------------------===//

/// \copydoc ::gala_adapter_t
class Adapter
{
 private:
  Adapter();
  Adapter(const Adapter &adapter);
  Adapter &operator=(const Adapter &adapter);
  ~Adapter();

 public:
  /// \copydoc ::gala_adapter_type_t
  typedef ::gala_adapter_type_t Type;

  /// \copydoc ::GALA_ADAPTER_SOFTWARE
  static const Type Software = (Type)::GALA_ADAPTER_SOFTWARE;
  /// \copydoc ::GALA_ADAPTER_HARDWARE
  static const Type Hardware = (Type)::GALA_ADAPTER_HARDWARE;
  /// \copydoc ::GALA_ADAPTER_PROXY
  static const Type Proxy = (Type)::GALA_ADAPTER_PROXY;

 public:
  /// \copydoc ::gala_adapter_t::type
  const Type type() const { return (Type)__adapter__.type; }
  /// \copydoc ::gala_adapter_t::num_outputs
  const size_t num_outputs() const { return __adapter__.num_outputs; }
  /// \copydoc ::gala_adapter_t::outputs
  const class Output **outputs() const { return (const class Output **)__adapter__.outputs; }

 private:
  ::gala_adapter_t __adapter__;
};

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_ADAPTER_H_

//============================================================================//
