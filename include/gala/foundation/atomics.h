//===-- gala/foundation/atomics.h -----------------------*- mode: C++11 -*-===//
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

#ifndef _GALA_FOUNDATION_ATOMICS_H_
#define _GALA_FOUNDATION_ATOMICS_H_

#include "gala/config.h"
#include "gala/linkage.h"

#include "gala/foundation/types.h"
#include "gala/foundation/support.h"

#if GALA_COMPILER == GALA_COMPILER_MSVC
  #include <intrin.h>
  #if GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86
    #pragma intrinsic(_InterlockedExchangeAdd)
    #pragma intrinsic(_InterlockedCompareExchange)
    #pragma intrinsic(_InterlockedCompareExchange64)
  #elif GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86_64
    #pragma intrinsic(_InterlockedExchangeAdd)
    #pragma intrinsic(_InterlockedExchangeAdd64)
    #pragma intrinsic(_InterlockedCompareExchange)
    #pragma intrinsic(_InterlockedCompareExchange64)
  #endif
#elif (GALA_COMPILER == GALA_COMPILER_GCC) || \
      (GALA_COMPILER == GALA_COMPILER_CLANG)
#endif

// TODO(mtwilliams): Document all of this.

GALA_BEGIN_EXTERN_C

GALA_INLINE gala_int32_t gala_atomic_load_i32(const volatile gala_int32_t *v) {
#if (GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86) || \
    (GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86_64)
  return *v;
#endif
}

GALA_INLINE gala_uint32_t gala_atomic_load_u32(const volatile gala_uint32_t *v) {
#if (GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86) || \
    (GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86_64)
  return *v;
#endif
}

GALA_INLINE gala_int64_t gala_atomic_load_i64(const volatile gala_int64_t *v) {
#if GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86
  #if GALA_COMPILER == GALA_COMPILER_MSVC
    gala_int64_t r;
    __asm {
      mov esi, v;
      mov ebx, eax;
      mov ecx, edx;
      lock cmpxchg8b [esi];
      mov dword ptr r, eax;
      mov dword ptr r[4], edx;
    }
    return r;
  #elif (GALA_COMPILER == GALA_COMPILER_GCC) || \
        (GALA_COMPILER == GALA_COMPILER_CLANG)
    gala_int64_t r;
    asm volatile("movl %%ebx, %%eax\n"
                 "movl %%ecx, %%edx\n"
                 "lock; cmpxchg8b %1"
                 : "=&A"(r)
                 : "m"(v));
    return r;
  #endif
#elif GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86_64
  return *v;
#endif
}

GALA_INLINE gala_uint64_t gala_atomic_load_u64(const volatile gala_uint64_t *v) {
#if GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86
  #if GALA_COMPILER == GALA_COMPILER_MSVC
    gala_uint64_t r;
    __asm {
      mov esi, v;
      mov ebx, eax;
      mov ecx, edx;
      lock cmpxchg8b [esi];
      mov dword ptr r, eax;
      mov dword ptr r[4], edx;
    }
    return r;
  #elif (GALA_COMPILER == GALA_COMPILER_GCC) || \
        (GALA_COMPILER == GALA_COMPILER_CLANG)
    gala_uint64_t r;
    asm volatile("movl %%ebx, %%eax\n"
                 "movl %%ecx, %%edx\n"
                 "lock; cmpxchg8b %1"
                 : "=&A"(r)
                 : "m"(v));
    return r;
  #endif
#elif GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86_64
  return *v;
#endif
}

GALA_INLINE void *gala_atomic_load_ptr(void ** const volatile v) {
#if (GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86) || \
    (GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86_64)
  return *v;
#endif
}

GALA_INLINE void gala_atomic_store_i32(volatile gala_int32_t *v, const gala_int32_t desired) {
#if (GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86) || \
    (GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86_64)
  *v = desired;
#endif
}

GALA_INLINE void gala_atomic_store_u32(volatile gala_uint32_t *v, const gala_uint32_t desired) {
#if (GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86) || \
    (GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86_64)
  *v = desired;
#endif
}

GALA_INLINE void gala_atomic_store_i64(volatile gala_int64_t *v, const gala_int64_t desired) {
#if GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86
  #if GALA_COMPILER == GALA_COMPILER_MSVC
    __asm {
      mov esi, v;
      mov ebx, dword ptr desired;
      mov ecx, dword ptr desired[4];
    retry:
      cmpxchg8b [esi];
      jne retry;
    }
  #elif (GALA_COMPILER == GALA_COMPILER_GCC) || \
        (GALA_COMPILER == GALA_COMPILER_CLANG)
    gala_int64_t expected = *v;
    asm volatile("1:  cmpxchg8b %0\n"
                 "    jne 1b"
                 : "=m"(*v)
                 : "b"((u32)desired), "c"((u32)(desired >> 32)), "A"(expected));
  #endif
#elif GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86_64
  *v = desired;
#endif
}

GALA_INLINE void gala_atomic_store_u64(volatile gala_uint64_t *v, const gala_uint64_t desired) {
  gala_atomic_store_i64((gala_int64_t *)v, (gala_int64_t)desired);
}

GALA_INLINE void gala_atomic_store_ptr(void ** volatile v, void * const desired) {
#if (GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86) || \
    (GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86_64)
  *v = desired;
#endif
}

GALA_INLINE gala_int32_t gala_atomic_add_i32(volatile gala_int32_t *lhs, const gala_int32_t rhs) {
#if GALA_COMPILER == GALA_COMPILER_MSVC
  return _InterlockedExchangeAdd((volatile long *)lhs, (long)rhs);
#elif (GALA_COMPILER == GALA_COMPILER_GCC) || \
      (GALA_COMPILER == GALA_COMPILER_CLANG)
  return __sync_fetch_and_add(lhs, rhs);
#endif
}

GALA_INLINE gala_uint32_t gala_atomic_add_u32(volatile gala_uint32_t *lhs, const gala_uint32_t rhs) {
  return (gala_uint32_t)gala_atomic_add_i32((gala_int32_t *)lhs, (gala_int32_t)rhs);
}

GALA_INLINE gala_int64_t gala_atomic_add_i64(volatile gala_int64_t *lhs, const gala_int64_t rhs) {
#if GALA_COMPILER == GALA_COMPILER_MSVC
  #if GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86
    // TODO(mtwilliams): Use XADD?
    // http://git.kernel.org/cgit/linux/kernel/git/torvalds/linux.git/tree/arch/x86/include/asm/atomic.h?id=HEAD
    gala_int64_t r;
    __asm {
    retry:
      mov esi, lhs;
      mov eax, [esi];
      mov edx, [esi+4];
      mov ebx, dword ptr rhs;
      mov ecx, dword ptr rhs[4];
      add ebx, eax;
      adc ecx, edx;
      lock cmpxchg8b [esi];
      jne retry;
      mov dword ptr r, eax;
      mov dword ptr r[4], edx;
    }
    return r;
  #elif GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86_64
    return _InterlockedExchangeAdd64((volatile __int64 *)lhs, (__int64)rhs);
  #endif
#elif (GALA_COMPILER == GALA_COMPILER_GCC) || \
      (GALA_COMPILER == GALA_COMPILER_CLANG)
  return __sync_fetch_and_add(lhs, rhs);
#endif
}

GALA_INLINE gala_uint64_t gala_atomic_add_u64(volatile gala_uint64_t *lhs, const gala_uint64_t rhs) {
  return (gala_uint64_t)gala_atomic_add_i64((gala_int64_t *)lhs, (gala_int64_t)rhs);
}

GALA_INLINE gala_int32_t gala_atomic_sub_i32(volatile gala_int32_t *lhs, const gala_int32_t rhs) {
#if GALA_COMPILER == GALA_COMPILER_MSVC
  return _InterlockedExchangeAdd((volatile long *)lhs, -((long)rhs));
#elif (GALA_COMPILER == GALA_COMPILER_GCC) || \
      (GALA_COMPILER == GALA_COMPILER_CLANG)
  return __sync_fetch_and_sub(lhs, rhs);
#endif
}

GALA_INLINE gala_uint32_t gala_atomic_sub_u32(volatile gala_uint32_t *lhs, const gala_uint32_t rhs) {
  return (gala_uint32_t)gala_atomic_sub_i32((gala_int32_t *)lhs, (gala_int32_t)rhs);
}

GALA_INLINE gala_int64_t gala_atomic_sub_i64(volatile gala_int64_t *lhs, const gala_int64_t rhs) {
#if GALA_COMPILER == GALA_COMPILER_MSVC
  #if GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86
    gala_int64_t r;
    __asm {
    retry:
      mov esi, lhs;
      mov eax, [esi];
      mov edx, [esi+4];
      mov ebx, dword ptr rhs;
      mov ecx, dword ptr rhs[4];
      sub ebx, eax;
      sbb ecx, edx;
      lock cmpxchg8b [esi];
      jne retry;
      mov dword ptr r, eax;
      mov dword ptr r[4], edx;
    }
    return r;
  #elif GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86_64
    return _InterlockedExchangeAdd64((volatile __int64 *)lhs, -((__int64)rhs));
  #endif
#elif (GALA_COMPILER == GALA_COMPILER_GCC) || \
      (GALA_COMPILER == GALA_COMPILER_CLANG)
  return __sync_fetch_and_sub(lhs, rhs);
#endif
}

GALA_INLINE gala_uint64_t gala_atomic_sub_u64(volatile gala_uint64_t *lhs, const gala_uint64_t rhs) {
  return (gala_uint64_t)gala_atomic_sub_i64((gala_int64_t *)lhs, (gala_int64_t)rhs);
}

GALA_INLINE gala_int32_t gala_atomic_cmp_and_xchg_i32(volatile gala_int32_t *v, const gala_int32_t expected, const gala_int32_t desired) {
#if GALA_COMPILER == GALA_COMPILER_MSVC
  return _InterlockedCompareExchange((volatile long *)v, (long)desired, (long)expected);
#elif (GALA_COMPILER == GALA_COMPILER_GCC) || \
      (GALA_COMPILER == GALA_COMPILER_CLANG)
  return __sync_val_compare_and_swap(v, expected, desired);
#endif
}

GALA_INLINE gala_uint32_t gala_atomic_cmp_and_xchg_u32(volatile gala_uint32_t *v, const gala_uint32_t expected, const gala_uint32_t desired) {
  return (gala_uint32_t)gala_atomic_cmp_and_xchg_i32((gala_int32_t *)v, (gala_int32_t)expected, (gala_int32_t)desired);
}

GALA_INLINE gala_int64_t gala_atomic_cmp_and_xchg_i64(volatile gala_int64_t *v, const gala_int64_t expected, const gala_int64_t desired) {
#if GALA_COMPILER == GALA_COMPILER_MSVC
  return _InterlockedCompareExchange64((volatile __int64 *)v, (__int64)desired, (__int64)expected);
#elif (GALA_COMPILER == GALA_COMPILER_GCC) || \
      (GALA_COMPILER == GALA_COMPILER_CLANG)
  return __sync_val_compare_and_swap(v, expected, desired);
#endif
}

GALA_INLINE gala_uint64_t gala_atomic_cmp_and_xchg_u64(volatile gala_uint64_t *v, const gala_uint64_t expected, const gala_uint64_t desired) {
  return (gala_uint64_t)gala_atomic_cmp_and_xchg_i64((gala_int64_t *)v, (gala_int64_t)expected, (gala_int64_t)desired);
}

GALA_INLINE void *gala_atomic_cmp_and_xchg_ptr(void ** volatile v, const void *expected, const void *desired) {
#if GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86
  return (void *)gala_atomic_cmp_and_xchg_u32((gala_uint32_t *)v, (gala_uint32_t)expected, (gala_uint32_t)desired);
#elif GALA_ARCHITECTURE == GALA_ARCHITECTURE_X86_64
  return (void *)gala_atomic_cmp_and_xchg_u64((gala_uint64_t *)v, (gala_uint64_t)expected, (gala_uint64_t)desired);
#endif
}

GALA_END_EXTERN_C

#endif // _GALA_FOUNDATION_ATOMICS_H_
