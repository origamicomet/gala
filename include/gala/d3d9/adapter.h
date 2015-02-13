//===-- gala/d3d9/adapter.h -------------------------------------*- C++ -*-===//
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

#ifndef _GALA_D3D9_ADAPTER_H_
#define _GALA_D3D9_ADAPTER_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"

//===----------------------------------------------------------------------===//

#include "gala/adapter.h"

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
typedef struct gala_adapter_d3d9 {
  gala_adapter_t __adapter__;
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  UINT _uiAdapter;
  D3DADAPTER_IDENTIFIER9 _Identifier;
#endif
} gala_adapter_d3d9_t;

//===----------------------------------------------------------------------===//

/// \brief
/// \param adapter
/// \returns
///
extern
GALA_PUBLIC
void
gala_adapter_d3d9_destroy(
  gala_adapter_d3d9_t *adapter);

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
gala_adapter_d3d9_to_s(
  const gala_adapter_d3d9_t *adapter,
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

/// \copydoc ::gala_adapter_d3d9_t
class GALA_PUBLIC D3D9Adapter : public ::gala::Adapter {
 public:
  /// \copydoc ::gala_adapter_d3d9_destroy
  void destroy() {
    ::gala_adapter_d3d9_destroy((::gala_adapter_d3d9_t *)&this->__adapter__);
  }

 public:
  /// \copydoc ::gala_adapter_d3d9_to_s
  int to_s(char buf[], const int buf_sz) const {
    return ::gala_adapter_d3d9_to_s((::gala_adapter_d3d9_t *)&this->__adapter__, buf, buf_sz);
  }
};

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_D3D9_ADAPTER_H_

//============================================================================//
