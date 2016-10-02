//===-- gala.h ------------------------------------------*- mode: C++11 -*-===//
//
//                             _____     _
//                            |   __|___| |___
//                            |  |  | .'| | .'|
//                            |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief A low-level abstraction layer for rendering.
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_H_
#define _GALA_H_

#include "gala/config.h"
#include "gala/linkage.h"

#include "gala/foundation.h"

#include "gala/command.h"
#include "gala/commands.h"
#include "gala/command_buffer.h"

#include "gala/resource.h"
#include "gala/resources/swap_chain.h"
#include "gala/resource_table.h"

#include "gala/backend.h"

#include "gala/d3d11.h"

GALA_BEGIN_EXTERN_C

extern GALA_PUBLIC void _gala__();
extern GALA_PUBLIC const char *__gala_version__();
extern GALA_PUBLIC gala_uint32_t __gala_revision__();

GALA_END_EXTERN_C

#endif // _GALA_H_
