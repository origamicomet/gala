//===-- gala/d3d11/adapter.h ------------------------------------*- C++ -*-===//
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

#ifndef _GALA_D3D11_ADAPTER_H_
#define _GALA_D3D11_ADAPTER_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"

//===----------------------------------------------------------------------===//

#include "gala/adapter.h"

//===----------------------------------------------------------------------===//

#include "gala/d3d11/output.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_d3d11_adapter gala_d3d11_adapter_t;

//===----------------------------------------------------------------------===//

/// \brief
/// \param adapter
/// \returns
///
extern GALA_PUBLIC void
gala_d3d11_adapter_destroy(
  gala_d3d11_adapter_t *adapter);

//===----------------------------------------------------------------------===//

/// \brief
/// \param adapter
/// \returns
///
extern GALA_PUBLIC size_t
gala_d3d11_adapter_num_outputs(
  const gala_d3d11_adapter_t *adapter);

//===----------------------------------------------------------------------===//

/// \brief
/// \param adapter
/// \param idx
/// \returns
///
extern GALA_PUBLIC gala_d3d11_output_t *
gala_d3d11_adapter_output(
  const gala_d3d11_adapter_t *adapter,
  const size_t idx);

//===----------------------------------------------------------------------===//

/// \brief
/// \param adapter
/// \param buf
/// \param buf_sz
/// \returns
///
extern GALA_PUBLIC int
gala_d3d11_adapter_to_s(
  const gala_d3d11_adapter_t *adapter,
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

/// \copydoc ::gala_d3d11_adapter_t
class GALA_PUBLIC D3D11Adapter : public ::gala::Adapter {
 public:
  /// \copydoc ::gala_d3d11_adapter_destroy
  void destroy();

 public:
  /// \copydoc ::gala_d3d11_adapter_num_outputs
  size_t num_outputs() const;

  /// \copydoc ::gala_d3d11_adapter_output
  ::gala::D3D11Output *output(const size_t idx) const;

 public:
  /// \copydoc ::gala_d3d11_adapter_to_s
  int to_s(char buf[], const int buf_sz) const;
};

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_D3D11_ADAPTER_H_

//============================================================================//
