//===-- gala/foundation/utilities.h ---------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief A collection of utilities.
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_FOUNDATION_UTILITIES_H_
#define _GALA_FOUNDATION_UTILITIES_H_

#if defined(_MSC_VER)
  #include <intrin.h>

  #pragma intrinsic(_BitScanForward)
  #pragma intrinsic(_BitScanForward64)
  #pragma intrinsic(_BitScanReverse)
  #pragma intrinsic(_BitScanReverse64)
#endif

#include "gala/foundation/types.h"
#include "gala/foundation/support.h"

/// \def GALA_MIN
/// \brief Computes minimum of `a` and `b`.
#define GALA_MIN(a, b) \
  (((a) > (b)) ? (b) : (a))

/// \def GALA_MAX
/// \brief Computes maximum of `a` and `b`.
#define GALA_MAX(a, b) \
  (((a) > (b)) ? (a) : (b))

/// \def GALA_BITS_TO_BYTES
/// \brief Computes the number of bytes required to represent `n` bits.
#define GALA_BITS_TO_BYTES(n) \
  (((n) + 7) / 8)

/// \def GALA_BYTES_TO_BITS
/// \brief Computes the number of bits represented by `n` bytes.
#define GALA_BYTES_TO_BITS(n) \
  ((n) * 8)

/// \def GALA_ALIGN_TO_BOUNDARY
/// \brief Aligns `n` to `alignment` bytes boundary.
#define GALA_ALIGN_TO_BOUNDARY(n, alignment) \
  ((((n) + (alignment) - 1) / (alignment)) * (alignment))

/// Counts number of leading zeros.
static GALA_INLINE gala_uint32_t gala_clzul(gala_uint32_t n) {
#if defined(_MSC_VER)
  gala_uint32_t bit;
  return _BitScanReverse((unsigned long *)&bit, n) ? (31 - bit) : 32;
#elif defined(__clang__) || defined(__GNUC__)
  return n ? __builtin_clzl(n) : 32;
#endif
}

/// Counts number of trailing zeros.
static GALA_INLINE gala_uint32_t gala_ctzul(gala_uint32_t n) {
#if defined(_MSC_VER)
  gala_uint32_t bit;
  return _BitScanForward((unsigned long *)&bit, n) ? bit : 32;
#elif defined(__clang__) || defined(__GNUC__)
  return n ? __builtin_ctzl(n) : 32;
#endif
}

#if defined(_MSC_VER)
  extern GALA_LOCAL const gala_uint8_t GALA_POPCNTUB_TABLE[256];
#endif

/// Counts the number of set bits.
static GALA_INLINE gala_uint32_t gala_popcntul(gala_uint32_t n) {
#if defined(_MSC_VER)
  const gala_uint8_t *bytes = (const gala_uint8_t *)&n;
  return GALA_POPCNTUB_TABLE[bytes[0]] + 
         GALA_POPCNTUB_TABLE[bytes[1]] + 
         GALA_POPCNTUB_TABLE[bytes[2]] + 
         GALA_POPCNTUB_TABLE[bytes[3]];
#elif defined(__clang__) || defined(__GNUC__)
  return __builtin_popcountl(n);
#endif
}

/// Counts the number of set bits.
static GALA_INLINE gala_uint32_t gala_popcntull(gala_uint64_t n) {
#if defined(_MSC_VER)
  const gala_uint8_t *bytes = (const gala_uint8_t *)&n;
  return GALA_POPCNTUB_TABLE[bytes[0]] + 
         GALA_POPCNTUB_TABLE[bytes[1]] + 
         GALA_POPCNTUB_TABLE[bytes[2]] + 
         GALA_POPCNTUB_TABLE[bytes[3]] +
         GALA_POPCNTUB_TABLE[bytes[4]] + 
         GALA_POPCNTUB_TABLE[bytes[5]] + 
         GALA_POPCNTUB_TABLE[bytes[6]] + 
         GALA_POPCNTUB_TABLE[bytes[7]];
#elif defined(__clang__) || defined(__GNUC__)
  return __builtin_popcountll(n);
#endif
}

/// \def GALA_IS_POWER_OF_TWO
/// \brief Quickly determines if `n` is a power of two.
#define GALA_IS_POWER_OF_TWO(n) \
  ((n) && !((n) & ((n) - 1)))

/// Quickly computes the base-2 logarithm of `n`.
static GALA_INLINE gala_uint32_t gala_log2ul(gala_uint32_t n) {
  return n ? (31 - gala_clzul(n)) : 0;
}

/// Quickly computes the base-2 logarithm with `n` rounded up to the nearest
/// power of two.
static GALA_INLINE gala_uint32_t gala_log2ul_ceil(gala_uint32_t n) {
  const gala_uint32_t logarithm = gala_log2ul(n);
  const gala_uint32_t non_power_of_two = (n & (n - 1));
  return logarithm + (non_power_of_two ? 1 : 0);
}

// TODO(mtwilliams): Fallback for _BitScanReverse64 on x86.
#if 0
  /// Quickly computes the base-2 logarithim of `n`.
  static GALA_INLINE gala_uint64_t gala_log2ull(gala_uint64_t n) {
  }
#endif

#endif // _GALA_FOUNDATION_UTILITIES_H_
