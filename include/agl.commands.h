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

#ifndef _AGL_COMMANDS_H_
#define _AGL_COMMANDS_H_

#include <agl.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ========================================================================== */
/*  Commands:                                                                 */
/*   * Resource                                                               */
/*     * Swap Chain                                                           */
/* ========================================================================== */

/* ==========================================================================
    Commands (agl_command_t):
   ========================================================================== */

typedef enum agl_command_type {
  AGL_COMMAND_TYPE_RESOURCE_CREATE    = 1,
  AGL_COMMAND_TYPE_RESOURCE_DESTROY   = 2,
  AGL_COMMAND_TYPE_SWAP_CHAIN_PRESENT = 3
} agl_command_type_t;

typedef struct agl_command {
  agl_command_type_t type;
} agl_command_t;

/* ========================================================================== */

/*! */
extern AGL_API size_t agl_command_length(
  const agl_command_t *cmd);

/* ==========================================================================
    Commands > Resource:
   ========================================================================== */

typedef struct agl_resource_create_cmd {
  agl_command_t cmd;
  agl_resource_t *resource;
} agl_resource_create_cmd_t;

typedef struct agl_resource_destroy_cmd {
  agl_command_t cmd;
  agl_resource_t *resource;
} agl_resource_destroy_cmd_t;

/* ==========================================================================
    Commands > Resource > Swap Chain:
   ========================================================================== */

typedef struct agl_swap_chain_present_cmd {
  agl_command_t cmd;
  agl_swap_chain_t *swap_chain;
} agl_swap_chain_present_cmd_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _AGL_COMMANDS_H_ */
