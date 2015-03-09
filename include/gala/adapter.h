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

//===----------------------------------------------------------------------===//

#include "gala/output.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef enum gala_adapter_type {
  /// Invalid.
  GALA_ADAPTER_TYPE_INVALID = 0,
  /// Software.
  GALA_ADAPTER_TYPE_SOFTWARE = 1,
  /// Hardware accelerated.
  GALA_ADAPTER_TYPE_HARDWARE = 2,
  /// Proxying, i.e. nVidia PerfHUD.
  GALA_ADAPTER_TYPE_PROXY = 3,
  /// \internal Force at least uint32_t storage and alignment.
  GALA_ADAPTER_TYPE_FORCE_UINT32 = 0x7fffffff
} gala_adapter_type_t;

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_adapter {
  /// \copydoc ::gala_adapter_type_t
  gala_adapter_type_t type;
} gala_adapter_t;

//===----------------------------------------------------------------------===//

/// \def GAlA_DEFAULT_ADAPTER
/// \brief
///
#define GAlA_DEFAULT_ADAPTER \
  ((gala_adapter_t *)NULL)

//===----------------------------------------------------------------------===//

/// \brief
/// \param adapter
/// \returns
///
extern GALA_PUBLIC void
gala_adapter_init(
  gala_adapter_t *adapter);

//===----------------------------------------------------------------------===//

/// \brief
/// \param adapter
///
extern GALA_PUBLIC void
gala_adapter_destroy(
  gala_adapter_t *adapter);

//===----------------------------------------------------------------------===//

/// \brief
/// \param adapter
/// \param buf
/// \param buf_sz
/// \returns
///
extern GALA_PUBLIC int
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
    /// \copydoc ::GALA_ADAPTER_TYPE_INVALID
    kInvalid = ::GALA_ADAPTER_TYPE_INVALID,
    /// \copydoc ::GALA_ADAPTER_TYPE_SOFTWARE
    kSoftware = ::GALA_ADAPTER_TYPE_SOFTWARE,
    /// \copydoc ::GALA_ADAPTER_TYPE_HARDWARE
    kHardware = ::GALA_ADAPTER_TYPE_HARDWARE,
    /// \copydoc ::GALA_ADAPTER_TYPE_PROXY
    kProxy = ::GALA_ADAPTER_TYPE_PROXY
  };

 public:
  /// \copydoc ::gala_adapter_init
  static void init(::gala::Adapter *adapter);

  /// \copydoc ::gala_adapter_destroy
  void destroy();

 public:
  /// \copydoc ::gala_adapter_to_s
  int to_s(char buf[], const int buf_sz) const;

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
