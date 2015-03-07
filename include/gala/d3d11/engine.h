//===-- gala/d3d11/engine.h -------------------------------------*- C++ -*-===//
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

#ifndef _GALA_D3D11_ENGINE_H_
#define _GALA_D3D11_ENGINE_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"

//===----------------------------------------------------------------------===//

#include "gala/engine.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_d3d11_engine gala_d3d11_engine_t;

//===----------------------------------------------------------------------===//

/// \brief
/// \param engine
/// \returns
///
extern GALA_PUBLIC void
gala_d3d11_engine_shutdown_and_destroy(
  gala_d3d11_engine_t *engine);

//===----------------------------------------------------------------------===//

/// \brief
/// \param engine
/// \param buf
/// \param buf_sz
/// \returns
///
extern GALA_PUBLIC int
gala_d3d11_engine_to_s(
  const gala_d3d11_engine_t *engine,
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

/// \copydoc ::gala_d3d11_engine_t
class GALA_PUBLIC D3D11Engine : public ::gala::Engine {
 public:
  /// \copydoc ::gala_d3d11_engine_shutdown_and_destroy
  void shutdown_and_destroy();

 public:
  /// \copydoc ::gala_d3d11_engine_to_s
  int to_s(char buf[], const int buf_sz) const;
};

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_D3D11_ENGINE_H_

//============================================================================//
