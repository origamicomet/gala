//===-- agl/types.h ---------------------------------------------*- C++ -*-===//
//
//  Abstract Graphics Library (AGL)
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//    * Michael Williams <mwilliams@bitbyte.ca>
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Defines primitive data types used by the Abstract Graphics Library.
///
//===----------------------------------------------------------------------===//

#ifndef _AGL_TYPES_H_
#define _AGL_TYPES_H_

//============================================================================//

#include <agl/config.h>
#include <agl/compat.h>

//============================================================================//

typedef bool agl_bool_t;

#define AGL_TRUE true
#define AGL_FALSE false

typedef int8_t agl_int8_t;
typedef int16_t agl_int16_t;
typedef int32_t agl_int32_t;
typedef int64_t agl_int64_t;
typedef uint8_t agl_uint8_t;
typedef uint16_t agl_uint16_t;
typedef uint32_t agl_uint32_t;
typedef uint64_t agl_uint64_t;

typedef intptr_t agl_intptr_t;
typedef uintptr_t agl_uintptr_t;

typedef intmax_t agl_intmax_t;
typedef uintmax_t agl_uintmax_t;

#define AGL_INT8_MIN INT8_MIN
#define AGL_INT8_MAX INT8_MAX
#define AGL_INT16_MIN INT16_MIN
#define AGL_INT16_MAX INT16_MAX
#define AGL_INT32_MIN INT32_MIN
#define AGL_INT32_MAX INT32_MAX
#define AGL_INT64_MIN INT64_MIN
#define AGL_INT64_MAX INT64_MAX
#define AGL_UINT8_MAX UINT8_MAX
#define AGL_UINT16_MAX UINT16_MAX
#define AGL_UINT32_MAX UINT32_MAX
#define AGL_UINT64_MAX UINT64_MAX

#define AGL_INTPTR_MIN INTPTR_MIN
#define AGL_INTPTR_MAX INTPTR_MAX
#define AGL_UINTPTR_MAX UINTPTR_MAX

#define AGL_INTMAX_MIN INTMAX_MIN
#define AGL_INTMAX_MAX INTMAX_MAX
#define AGL_UINTMAX_MAX UINTMAX_MAX

#define AGL_PTRDIFF_MIN PTRDIFF_MIN
#define AGL_PTRDIFF_MAX PTRDIFF_MAX

#define AGL_SIZE_MAX SIZE_MAX

#define AGL_INT8_C INT8_C
#define AGL_INT16_C INT16_C
#define AGL_INT32_C INT32_C
#define AGL_INT64_C INT64_C
#define AGL_UINT8_C UINT8_C
#define AGL_UINT16_C UINT16_C
#define AGL_UINT32_C UINT32_C
#define AGL_UINT64_C UINT64_C

#define AGL_INTMAX_C INTMAX_C
#define AGL_UINTMAX_C UINTMAX_C

//============================================================================//

#endif // _AGL_TYPES_H_

//============================================================================//
