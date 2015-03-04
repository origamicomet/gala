//===-- gala/d3d9.h ---------------------------------------------*- C++ -*-===//
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

#ifndef _GALA_D3D9_H_
#define _GALA_D3D9_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"

//===----------------------------------------------------------------------===//

#include "gala/backend.h"

//===----------------------------------------------------------------------===//

#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
  #endif
  #ifndef WIN32_EXTRA_LEAN
    #define WIN32_EXTRA_LEAN
  #endif

  #include <windows.h>
  #include <d3d9.h>

  #undef WIN32_EXTRA_LEAN
  #undef WIN32_LEAN_AND_MEAN

  #undef NEAR
  #undef FAR
  #undef near
  #undef far
  #undef NO_ERROR
  #undef ERROR
  #undef MK_SHIFT
  #undef MK_ALT
  #undef min
  #undef max
  #undef rad1
#else
  #error ("Direct3D 9 is not available on non-Windows systems!")
#endif

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_backend_d3d9 gala_backend_d3d9_t;

//===----------------------------------------------------------------------===//

/// \copydoc ::gala_backend_t
extern GALA_PUBLIC gala_backend_d3d9_t *
gala_backend_d3d9_init(void);

//===----------------------------------------------------------------------===//

/// \copydoc ::gala_backend_d3d9_t
extern GALA_PUBLIC void
gala_backend_d3d9_shutdown(
  gala_backend_d3d9_t *backend);

//===----------------------------------------------------------------------===//

/// \copydoc ::gala_backend_to_s
extern GALA_PUBLIC int
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
class GALA_PUBLIC D3D9Backend
  : public ::gala::Backend
{
 public:
  /// \copydoc ::gala_backend_d3d9_init
  static ::gala::D3D9Backend *init() {
    return (::gala::D3D9Backend *)::gala_backend_d3d9_init();
  }

  /// \copydoc ::gala_backend_d3d9_shutdown
  void shutdown() {
    ::gala_backend_d3d9_shutdown((::gala_backend_d3d9_t *)&this->__backend__);
  }

 public:
  /// \copydoc ::gala_backend_d3d9_to_s
  int to_s(char buf[], const int buf_sz) const {
    // TODO(mike): Move to src/gala/d3d9.c
    return snprintf(buf, buf_sz, "#<gala::D3D9Backend:%.16" PRIxPTR ">", this);
  }
};

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_D3D9_H_

//============================================================================//
