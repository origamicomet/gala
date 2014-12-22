//===-- gala/types.h --------------------------------------------*- C++ -*-===//
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
/// \brief Defines primitive data types used by the Abstract Graphics Library.
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_TYPES_H_
#define _GALA_TYPES_H_

//============================================================================//

#include <gala/config.h>
#include <gala/compat.h>

//============================================================================//

typedef bool gala_bool_t;

#define GALA_TRUE true
#define GALA_FALSE false

typedef int8_t gala_int8_t;
typedef int16_t gala_int16_t;
typedef int32_t gala_int32_t;
typedef int64_t gala_int64_t;
typedef uint8_t gala_uint8_t;
typedef uint16_t gala_uint16_t;
typedef uint32_t gala_uint32_t;
typedef uint64_t gala_uint64_t;

typedef intptr_t gala_intptr_t;
typedef uintptr_t gala_uintptr_t;

typedef intmax_t gala_intmax_t;
typedef uintmax_t gala_uintmax_t;

#define GALA_INT8_MIN INT8_MIN
#define GALA_INT8_MAX INT8_MAX
#define GALA_INT16_MIN INT16_MIN
#define GALA_INT16_MAX INT16_MAX
#define GALA_INT32_MIN INT32_MIN
#define GALA_INT32_MAX INT32_MAX
#define GALA_INT64_MIN INT64_MIN
#define GALA_INT64_MAX INT64_MAX
#define GALA_UINT8_MAX UINT8_MAX
#define GALA_UINT16_MAX UINT16_MAX
#define GALA_UINT32_MAX UINT32_MAX
#define GALA_UINT64_MAX UINT64_MAX

#define GALA_INTPTR_MIN INTPTR_MIN
#define GALA_INTPTR_MAX INTPTR_MAX
#define GALA_UINTPTR_MAX UINTPTR_MAX

#define GALA_INTMAX_MIN INTMAX_MIN
#define GALA_INTMAX_MAX INTMAX_MAX
#define GALA_UINTMAX_MAX UINTMAX_MAX

#define GALA_PTRDIFF_MIN PTRDIFF_MIN
#define GALA_PTRDIFF_MAX PTRDIFF_MAX

#define GALA_SIZE_MAX SIZE_MAX

#define GALA_INT8_C INT8_C
#define GALA_INT16_C INT16_C
#define GALA_INT32_C INT32_C
#define GALA_INT64_C INT64_C
#define GALA_UINT8_C UINT8_C
#define GALA_UINT16_C UINT16_C
#define GALA_UINT32_C UINT32_C
#define GALA_UINT64_C UINT64_C

#define GALA_INTMAX_C INTMAX_C
#define GALA_UINTMAX_C UINTMAX_C

//============================================================================//

#endif // _GALA_TYPES_H_

//============================================================================//
