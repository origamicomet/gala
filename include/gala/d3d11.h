//===-- gala/d3d11.h ------------------------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//
//
// TODO(mtwilliams): Document the purpose of this file.
//
//===----------------------------------------------------------------------===//

#ifndef _GALA_D3D11_H_
#define _GALA_D3D11_H_

#include "gala/backend.h"

GALA_BEGIN_EXTERN_C

extern GALA_PUBLIC
void gala_d3d11_init(void);

extern GALA_PUBLIC
void gala_d3d11_shutdown(void);

GALA_END_EXTERN_C

#endif // _GALA_D3D11_H_
