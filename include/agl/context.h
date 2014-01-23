/* ========================================================================== */
/*                                                                            */
/* This file is part of the Abstract Graphics Library.                        */
/*                                                                            */
/* Author(s):                                                                 */
/*                                                                            */
/*   Michael Williams <devbug@bitbyte.ca>                                     */
/*                                                                            */
/* This is free and unencumbered software released into the public domain.    */
/*                                                                            */
/* Anyone is free to copy, modify, publish, use, compile, sell, or distribute */
/* this software, either in source code form or as a compiled binary, for any */
/* purpose, commercial or non-commercial, and by any means.                   */
/*                                                                            */
/* In jurisdictions that recognize copyright laws, the author or authors of   */
/* this software dedicate any and all copyright interest in the software to   */
/* the public domain. We make this dedication for the benefit of the public   */
/* large and to the detriment of our heirs and successors. We intend this     */
/* dedication to be an overt act of relinquishment in perpetuity of all       */
/* present and future rights to this software under copyright law.            */
/*                                                                            */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    */
/* THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER   */
/* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,      */
/* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR      */
/* OTHER DEALINGS IN THE SOFTWARE.                                            */
/*                                                                            */
/* For more information, please refer to <http://unlicense.org/>              */
/*                                                                            */
/* ========================================================================== */
/*! @file include/agl/context.h
     ...                                                                      */
/* ========================================================================== */

#ifndef _AGL_CONTEXT_H_
#define _AGL_CONTEXT_H_

#include <agl/config.h>
#include <agl/types.h>
#include <agl/backend.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ========================================================================== */
/*  Context:                                                                  */
/*   * agl_context_create                                                     */
/*   * agl_context_destroy                                                    */
/* ========================================================================== */

typedef struct agl_context agl_context_t;

/* ========================================================================== */
/*  agl_context_create:                                                       */
/* ========================================================================== */

extern AGL_EXPORT agl_context_t *agl_context_create(agl_backend_t *backend);

/* ========================================================================== */
/*  agl_context_destroy:                                                      */
/* ========================================================================== */

extern AGL_EXPORT void agl_context_destroy(agl_context_t *context);

/* ========================================================================== */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _AGL_CONTEXT_H_ */
