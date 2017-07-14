//===-- gala/foundation/types.h -------------------------*- mode: C++11 -*-===//
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

#ifndef _GALA_FOUNDATION_TYPES_H_
#define _GALA_FOUNDATION_TYPES_H_

#include "gala/config.h"
#include "gala/linkage.h"

// TODO(mtwilliams): Don't rely on `stdint.h`.
// TODO(mtwilliams): Provide fallbacks for shitty compilers.
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <float.h>

GALA_BEGIN_EXTERN_C // {

typedef size_t gala_size_t;

typedef uintptr_t gala_uintptr_t;
typedef size_t gala_size_t;
typedef ptrdiff_t gala_ptrdiff_t;

typedef int8_t gala_int8_t;
typedef uint8_t gala_uint8_t;
typedef int16_t gala_int16_t;
typedef uint16_t gala_uint16_t;
typedef int32_t gala_int32_t;
typedef uint32_t gala_uint32_t;
typedef int64_t gala_int64_t;
typedef uint64_t gala_uint64_t;

typedef float gala_float32_t;
typedef double gala_float64_t;

typedef bool gala_bool_t;

typedef gala_uint64_t gala_fence_t;

GALA_END_EXTERN_C // }

GALA_BEGIN_NAMESPACE // {

typedef gala_int8_t i8;
typedef gala_uint8_t u8;
typedef gala_int16_t i16;
typedef gala_uint16_t u16;
typedef gala_int32_t i32;
typedef gala_uint32_t u32;
typedef gala_int64_t i64;
typedef gala_uint64_t u64;

typedef gala_float32_t f32;
typedef gala_float64_t f64;

GALA_END_NAMESPACE // }

#endif // _GALA_FOUNDATION_TYPES_H_
