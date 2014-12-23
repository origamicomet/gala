//===-- gala/adapter_d3d9.h -------------------------------------*- C++ -*-===//
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

#ifndef _GALA_ADAPTER_D3D9_H_
#define _GALA_ADAPTER_D3D9_H_

//============================================================================//

#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__

//============================================================================//

#include "gala/adapter.h"

//===----------------------------------------------------------------------===//

#define _WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d9.h>

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_adapter_d3d9 {
  gala_adapter_t __adapter__;
  ///
  D3DADAPTER_IDENTIFIER9 identifier;
} gala_adapter_d3d9_t;

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//===----------------------------------------------------------------------===//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace gala {
namespace d3d9 {

//===----------------------------------------------------------------------===//

/// \copydoc ::gala_adapter_d3d9_t
class Adapter
{
 private:
  Adapter();
  Adapter(const Adapter &adapter);
  Adapter &operator=(const Adapter &adapter);
  ~Adapter();

 public:
  operator ::gala::Adapter *() { return (::gala::Adapter *)this; }
  operator const ::gala::Adapter *() const { return (const ::gala::Adapter *)this; }

 public:
  /// \copydoc ::gala_adapter_d3d9_t::identifier
  const D3DADAPTER_IDENTIFIER9 *identifier() const { return &__adapter_d3d9__.identifier; }

 private:
  ::gala_adapter_d3d9_t __adapter_d3d9__;
};

//===----------------------------------------------------------------------===//

} // d3d9
} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_ADAPTER_D3D9_H_

//============================================================================//

#endif // BITBYTE_FOUNDATION_TIER0_SYSTEM = __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__

//============================================================================//
