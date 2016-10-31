//===-- gala/fence.h ------------------------------------*- mode: C++11 -*-===//
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

#ifndef _GALA_FENCE_H_
#define _GALA_FENCE_H_

#include "gala/foundation.h"

GALA_BEGIN_EXTERN_C

// Defined in `gala/command_buffer.h`
typedef struct gala_command_buffer gala_command_buffer_t;

extern GALA_PUBLIC
void gala_fence_on_submission(
  gala_command_buffer_t *command_buffer,
  gala_fence_t *fence,
  gala_fence_t writeback);

extern GALA_PUBLIC
void gala_fence_on_completion(
  gala_command_buffer_t *command_buffer,
  gala_fence_t *fence,
  gala_fence_t writeback);

GALA_END_EXTERN_C

#endif // _GALA_FENCE_H_
