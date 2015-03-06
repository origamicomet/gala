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

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_d3d9_backend gala_d3d9_backend_t;

//===----------------------------------------------------------------------===//

/// \brief
/// \param backend
/// \returns
///
extern GALA_PUBLIC void
gala_d3d9_backend_init(
  gala_d3d9_backend_t **backend);

//===----------------------------------------------------------------------===//

/// \brief
/// \param backend
/// \returns
///
extern GALA_PUBLIC void
gala_d3d9_backend_shutdown(
  gala_d3d9_backend_t *backend);

//===----------------------------------------------------------------------===//

/// \brief
/// \param backend
/// \param buf
/// \param buf_sz
/// \returns
///
extern GALA_PUBLIC int
gala_d3d9_backend_to_s(
  const gala_d3d9_backend_t *backend,
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

/// \copydoc ::gala_d3d9_backend_t
class GALA_PUBLIC D3D9Backend : public ::gala::Backend {
 public:
  /// \copydoc ::gala_d3d9_backend_init
  static void init(::gala::D3D9Backend **backend);

  /// \copydoc ::gala_d3d9_backend_shutdown
  void shutdown();

 public:
  /// \copydoc ::gala_d3d9_backend_to_s
  int to_s(char buf[], const int buf_sz) const;
};

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_D3D9_BACKEND_H_

//============================================================================//
