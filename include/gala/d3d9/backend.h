//===-- gala/d3d9/backend.h -------------------------------------*- C++ -*-===//
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

#ifndef _GALA_D3D9_BACKEND_H_
#define _GALA_D3D9_BACKEND_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"

//===----------------------------------------------------------------------===//

#include "gala/backend.h"

//===----------------------------------------------------------------------===//

#include "gala/system.h"
#include <D3D9.h>

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_backend_d3d9 {
  gala_backend_t __backend__;
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  HMODULE _hDll;
#endif
  IDirect3D9 *_D3D9;
} gala_backend_d3d9_t;

//===----------------------------------------------------------------------===//

/// \brief
/// \param backend
/// \returns
///
extern
GALA_PUBLIC
void
gala_backend_d3d9_init(
  gala_backend_d3d9_t **backend);

//===----------------------------------------------------------------------===//

/// \brief
/// \param backend
/// \returns
///
extern
GALA_PUBLIC
void
gala_backend_d3d9_shutdown(
  gala_backend_d3d9_t *backend);

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
gala_backend_d3d9_to_s(
  const gala_backend_d3d9_t *backend,
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

/// \copydoc ::gala_backend_d3d9_t
class GALA_PUBLIC D3D9Backend : public ::gala::Backend {
 public:
  /// \copydoc ::gala_backend_d3d9_init
  static void init(::gala::D3D9Backend **backend) {
    ::gala_backend_d3d9_init((::gala_backend_d3d9_t **)backend);
  }

  /// \copydoc ::gala_backend_d3d9_shutdown
  void shutdown() {
    ::gala_backend_d3d9_shutdown((::gala_backend_d3d9_t *)&this->__backend__);
  }

 public:
  /// \copydoc ::gala_backend_d3d9_to_s
  int to_s(char buf[], const int buf_sz) const {
    return ::gala_backend_d3d9_to_s((::gala_backend_d3d9_t *)&this->__backend__, buf, buf_sz);
  }
};

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_D3D9_BACKEND_H_

//============================================================================//
