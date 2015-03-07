//===-- gala/d3d11/backend.h ------------------------------------*- C++ -*-===//
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

#ifndef _GALA_D3D11_BACKEND_H_
#define _GALA_D3D11_BACKEND_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"

//===----------------------------------------------------------------------===//

#include "gala/backend.h"

//===----------------------------------------------------------------------===//

#include "gala/d3d11/adapter.h"
#include "gala/d3d11/engine.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_d3d11_backend gala_d3d11_backend_t;

//===----------------------------------------------------------------------===//

/// \brief
/// \param backend
/// \returns
///
extern GALA_PUBLIC void
gala_d3d11_backend_init(
  gala_d3d11_backend_t **backend);

//===----------------------------------------------------------------------===//

/// \brief
/// \param backend
/// \returns
///
extern GALA_PUBLIC void
gala_d3d11_backend_shutdown(
  gala_d3d11_backend_t *backend);

//===----------------------------------------------------------------------===//

/// \brief
/// \param backend
/// \param params
/// \param engine
/// \returns
///
extern GALA_PUBLIC void
gala_d3d11_backend_create_and_init_engine(
  const gala_d3d11_backend_t *backend,
  const gala_engine_creation_params_t *params,
  gala_d3d11_engine_t **engine);

//===----------------------------------------------------------------------===//

/// \brief
/// \param backend
/// \returns
extern GALA_PUBLIC size_t
gala_d3d11_backend_num_adapters(
  const gala_d3d11_backend_t *backend);

//===----------------------------------------------------------------------===//

/// \brief
/// \param backend
/// \param idx
/// \returns
extern GALA_PUBLIC gala_d3d11_adapter_t *
gala_d3d11_backend_adapter(
  const gala_d3d11_backend_t *backend,
  const size_t idx);

//===----------------------------------------------------------------------===//

/// \brief
/// \param backend
/// \param buf
/// \param buf_sz
/// \returns
///
extern GALA_PUBLIC int
gala_d3d11_backend_to_s(
  const gala_d3d11_backend_t *backend,
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

/// \copydoc ::gala_d3d11_backend_t
class GALA_PUBLIC D3D11Backend : public ::gala::Backend {
 public:
  /// \copydoc ::gala_d3d11_backend_init
  static void init(::gala::D3D11Backend **backend);

  /// \copydoc ::gala_d3d11_backend_shutdown
  void shutdown();

 public:
  /// \copyodd ::gala_d3d11_backend_create_and_init_engine
  void create_and_init_engine(
    const ::gala_engine_creation_params_t &params,
    ::gala::D3D11Engine **engine) const;

 public:
  /// \copyodc ::gala_d3d11_num_adapters
  size_t num_adapters() const;

  /// \copyodc ::gala_d3d11_adapter
  ::gala::D3D11Adapter *adapter(const size_t idx) const;

 public:
  /// \copydoc ::gala_d3d11_backend_to_s
  int to_s(char buf[], const int buf_sz) const;
};

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_D3D11_BACKEND_H_

//============================================================================//
