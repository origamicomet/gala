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

#ifndef _AGL_RUNTIME_H_
#define _AGL_RUNTIME_H_

#include "agl_private.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* 1. Resources: */

typedef enum agl_resource_type {
} agl_resource_type_t;

typedef struct agl_resource {
  agl_resource_type_t type;
  uint ops;
} agl_resource_t;

extern agl_resource_t *agl_resource_from_id(
  const volatile agl_id_t *id);

extern agl_id_t agl_id_from_resource(
  const agl_resource_t *resource);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _AGL_RUNTIME_H_ */
