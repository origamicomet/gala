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

#ifndef _AGL_PRIVATE_H_
#define _AGL_PRIVATE_H_

#include <agl.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* 1. Assert: */

#if defined(AGL_COMPILER_MSVC)
  #define agl_raise() __debugbreak();
  #define fail_expr 0, 0
#else
  #define agl_raise() raise(SIGABRT);
  #define fail_expr 0
#endif

#if defined(AGL_PARANOID)
  #define agl_assert__paranoid(cond) \
    do { if (!(cond)) { agl_raise(); } } while(fail_expr)
#else
  #define agl_assert__paranoid(cond) \
    do { (void)sizeof(cond); } while (fail_expr)
#endif

#if defined(AGL_DEBUG_BUILD)
  #define agl_assert__debug(cond) \
    do { if (!(cond)) { agl_raise(); } } while(fail_expr)
  #define agl_assert__release(cond) \
    do { if (!(cond)) { agl_raise(); } } while(fail_expr)
#elif defined(AGL_RELEASE_BUILD)
  #define agl_assert__debug(cond) \
    do { (void)sizeof(cond); } while (fail_expr)
  #define agl_assert__release(cond) \
    do { if (!(cond)) { agl_raise(); } } while(fail_expr)
#else
  #error("Build type not specified!")
#endif

#define agl_assert(level, cond) agl_assert__##level##(cond)

/* 2. Atomics: */

extern uint agl_atomic_compare_and_swap(
  volatile uint *ptr,
  const uint old_value,
  const uint new_value);

extern uint agl_atomic_incr(
  volatile uint *ptr);

extern uint agl_atomic_decr(
  volatile uint *ptr);

/* 3. Shared libraries: */

typedef struct agl_shared_lib agl_shared_lib_t;

extern agl_shared_lib_t *agl_shared_lib_open(
  const char* path);

extern uintptr_t agl_shared_lib_sym(
  const agl_shared_lib_t *shared_lib,
  const char* symbol);

extern void agl_shared_lib_close(
  agl_shared_lib_t *shared_lib);

/* 4. Commands: */

typedef enum agl_command_type {
  AGL_IS_AVAILABLE_CMD  = 1u,
  AGL_IS_REFLECTIVE_CMD = 2u,
} agl_command_type_t;

typedef struct agl_command {
  agl_command_type_t type;
} agl_command_t;

typedef struct agl_is_available_cmd {
  agl_command_t cmd;
  const volatile agl_id_t *id;
  volatile uint *avail;
} agl_is_available_cmd_t;

typedef struct agl_is_reflective_cmd {
  agl_command_t cmd;
  const volatile agl_id_t *id;
  volatile uint *reflective;
} agl_is_reflective_cmd_t;

/*! 5. Command lists: */

extern bool agl_command_list_enqueue(
  agl_command_list_t *self,
  const void *cmd,
  const size_t cmd_sz);

extern void agl_command_list_for_each(
  const agl_command_list_t *self,
  void (*callback)(void *closure, const agl_command_t *cmd),
  void *closure);

/* 6. Runtimes: */

typedef size_t (*agl_get_num_of_adapters_fn)(void);

typedef const agl_adapter_t *(*agl_get_adapter_fn)(
  const agl_adapter_id_t id);

typedef agl_context_t *(*agl_create_context_fn)(
  const agl_adapter_id_t adapter);

typedef void (*agl_destroy_context_fn)(
  agl_context_t *context);

typedef bool (*agl_is_available_fn)(
  const agl_context_t *context,
  const volatile agl_id_t *id);

typedef bool (*agl_is_reflective_fn)(
  const agl_context_t *context,
  const volatile agl_id_t *id);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _AGL_PRIVATE_H_ */
