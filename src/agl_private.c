/*
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org/>
 */

#include "agl_private.h"

#if defined(AGL_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #define WIN32_EXTRA_LEAN
  #define NOMINMAX
  #include <Windows.h>
  #undef NOMINMAX
  #undef WIN32_EXTRA_LEAN
  #undef WIN32_LEAN_AND_MEAN

  #if defined(AGL_COMPILER_MSVC)
    #include <intrin.h>
    #if defined(AGL_ARCHITECTURE_X86_64)
      #pragma intrinsic(_InterlockedIncrement64)
      #pragma intrinsic(_InterlockedDecrement64)
      #pragma intrinsic(_InterlockedCompareExchange64)
    #elif defined(AGL_ARCHITECTURE_X86)
      #pragma intrinsic(_InterlockedIncrement)
      #pragma intrinsic(_InterlockedDecrement)
      #pragma intrinsic(_InterlockedCompareExchange)
    #endif
  #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* 2. Atomics: */

uint agl_atomic_compare_and_swap(volatile uint *ptr, const uint ov, const uint nv) {
#if defined(AGL_ARCHITECTURE_X86_64)
  #if defined(AGL_PLATFORM_WINDOWS)
    #if defined(AGL_COMPILER_MSVC)
      return _InterlockedCompareExchange64(ptr, nv, ov);
    #else
      return InterlockedCompareExchange64(ptr, nv, ov);
    #endif
  #else
    #error("agl_atomic_compare_and_swap is not implemented, yet!")
  #endif
#elif defined(AGL_ARCHITECTURE_X86)
  #if defined(AGL_PLATFORM_WINDOWS)
    #if defined(AGL_COMPILER_MSVC)
      return _InterlockedCompareExchange((volatile long*)ptr, (long)nv, (long)ov);
    #else
      return InterlockedCompareExchange((volatile long*)ptr, (long)nv, (long)ov);
    #endif
  #else
    #error("agl_atomic_compare_and_swap is not implemented, yet!")
  #endif
#else
  #error("agl_atomic_compare_and_swap is not implemented, yet!")
#endif
}

uint agl_atomic_incr(volatile uint *ptr) {
#if defined(AGL_ARCHITECTURE_X86_64)
  #if defined(AGL_PLATFORM_WINDOWS)
    #if defined(AGL_COMPILER_MSVC)
      return _InterlockedIncrement64(ptr);
    #else
      return InterlockedIncrement64(ptr);
    #endif
  #else
    #error("agl_atomic_incr is not implemented, yet!")
  #endif
#elif defined(AGL_ARCHITECTURE_X86)
  #if defined(AGL_PLATFORM_WINDOWS)
    #if defined(AGL_COMPILER_MSVC)
      return _InterlockedIncrement((volatile long*)ptr);
    #else
      return InterlockedIncrement((volatile long*)ptr);
    #endif
  #else
    #error("agl_atomic_incr is not implemented, yet!")
  #endif
#else
  #error("agl_atomic_incr is not implemented, yet!")
#endif
}

uint agl_atomic_decr(volatile uint *ptr) {
#if defined(AGL_ARCHITECTURE_X86_64)
  #if defined(AGL_PLATFORM_WINDOWS)
    #if defined(AGL_COMPILER_MSVC)
      return _InterlockedDecrement64(ptr);
    #else
      return InterlockedDecrement64(ptr);
    #endif
  #else
    #error("agl_atomic_decr is not implemented, yet!")
  #endif
#elif defined(AGL_ARCHITECTURE_X86)
  #if defined(AGL_PLATFORM_WINDOWS)
    #if defined(AGL_COMPILER_MSVC)
      return _InterlockedDecrement((volatile long*)ptr);
    #else
      return InterlockedDecrement((volatile long*)ptr);
    #endif
  #else
    #error("agl_atomic_decr is not implemented, yet!")
  #endif
#else
  #error("agl_atomic_decr is not implemented, yet!")
#endif
}

/* 3. Shared libraries: */

agl_shared_lib_t *agl_shared_lib_open(const char* path) {
  agl_assert(paranoid, path != NULL);
#if defined(AGL_PLATFORM_WINDOWS)
  return (agl_shared_lib_t*)LoadLibraryA(path);
#else
  #error("agl_shared_lib_open is not implemented, yet!")
#endif
}

uintptr_t agl_shared_lib_sym(const agl_shared_lib_t *shared_lib, const char* symbol) {
  agl_assert(paranoid, shared_lib != NULL);
  agl_assert(paranoid, symbol != NULL);
#if defined(AGL_PLATFORM_WINDOWS)
  return (uintptr_t)GetProcAddress(((HMODULE)shared_lib), symbol);
#else
  #error("agl_shared_lib_open is not implemented, yet!")
#endif
}

void agl_shared_lib_close(agl_shared_lib_t *shared_lib) {
  agl_assert(paranoid, shared_lib != NULL);
#if defined(AGL_PLATFORM_WINDOWS)
  FreeLibrary((HMODULE)shared_lib);
#else
  #error("agl_shared_lib_open is not implemented, yet!")
#endif
}

/* 5. Command lists: */

static bool agl_command_list_accommodate(
  agl_command_list *self,
  const size_t cmd_sz)
{
  agl_assert(paranoid, self != NULL);

  if ((self->end - self->current) > cmd_sz)
    return true;

  if (!self->exhausted)
    return false;

  return self->exhausted(self, self->end - self->current + cmd_sz);
}

bool agl_command_list_enqueue(
  agl_command_list_t *self,
  const void *cmd,
  const size_t cmd_sz)
{
  agl_assert(paranoid, self != NULL);
  agl_assert(paranoid, cmd != NULL);

  if (!agl_command_list_accommodate(self, cmd_sz))
    return false;

  memcpy((void*)self->current, cmd, cmd_sz);
  self->current += cmd_sz;

  return true;
}

static size_t agl_command_size(const agl_command_type_t cmd) {
  switch (cmd) {
    case AGL_IS_AVAILABLE_CMD: return sizeof(agl_is_available_cmd_t);
    case AGL_IS_REFLECTIVE_CMD: return sizeof(agl_is_reflective_cmd_t); }
  return 0;
}

void agl_command_list_for_each(
  const agl_command_list_t *self,
  void (*callback)(void *closure, const agl_command_t *cmd),
  void *closure)
{
  agl_assert(paranoid, self != NULL);
  agl_assert(paranoid, callback != NULL);

  uintptr_t current = self->start;
  while (current < self->current) {
    const agl_command_t *cmd = (const agl_command_t*)current;
    callback(closure, cmd);
    current += agl_command_size(cmd->type);
  }
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
