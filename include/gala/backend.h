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
typedef struct gala_backend {
  ///
  size_t num_adapters;
  ///
  const struct gala_adapter *const *adapters;
} gala_backend_t;

//===----------------------------------------------------------------------===//

/// \brief
/// \param backend
/// \returns
///
extern
GALA_PUBLIC
void
gala_backend_init(
  gala_backend_t *backend);

//===----------------------------------------------------------------------===//

/// \brief
/// \param backend
/// \param buf
/// \param buf_sz
/// \returns
///
extern
GALA_PUBLIC
int
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
  /// \copydoc ::gala_backend_init
  static void init(::gala::Backend *backend) {
    ::gala_backend_init(&backend->__backend__);
  }

 public:
  /// \copydoc ::gala_backend_to_s
  int to_s(char buf[], const int buf_sz) const {
    return ::gala_backend_to_s(&this->__backend__, buf, buf_sz);
  }

 public:
  /// \copydoc ::gala_backend_t::num_adapters
  size_t num_adapters() const {
    return this->__backend__.num_adapters;
  }

  // /// \copydoc ::gala_backend_t::adapters
  // const class ::gala::Adapter *const *adapters() const {
  //   return (const class ::gala::Adapter *const *)this->__backend__.adapters;
  // }

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
