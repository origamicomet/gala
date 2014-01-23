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
/*! @file include/agl/shared_library.h
     Provides a cross-platform interface for shared libraries.                */
/* ========================================================================== */

#ifndef _AGL_SHARED_LIBRARY_H_
#define _AGL_SHARED_LIBRARY_H_

#include <agl/config.h>
#include <agl/types.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ========================================================================== */
/*  Shared Library:                                                           */
/*   * agl_shared_library_open                                                */
/*   * agl_shared_library_symbol                                              */
/*   * agl_shared_library_close                                               */
/* ========================================================================== */

/* ========================================================================== */
/*  Shared Library:                                                           */
/* ========================================================================== */

typedef struct agl_shared_library agl_shared_lib_t, agl_shared_library_t;

/* ========================================================================== */
/*  agl_shared_library_open:                                                  */
/* ========================================================================== */

#define agl_shared_lib_open agl_shared_library_open
extern AGL_EXPORT agl_shared_library_t *agl_shared_library_open(
  const char *name);

/* ========================================================================== */
/*  agl_shared_library_symbol:                                                */
/* ========================================================================== */

#define agl_shared_lib_symbol agl_shared_library_symbol
extern AGL_EXPORT void *agl_shared_library_symbol(
  const agl_shared_library_t *shared_library,
  const char *name);

/* ========================================================================== */
/*  agl_shared_library_close:                                                  */
/* ========================================================================== */

#define agl_shared_library_close agl_shared_library_close
extern AGL_EXPORT void agl_shared_library_close(
  agl_shared_library_t *shared_library);

/* ========================================================================== */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _AGL_SHARED_LIBRARY_H_ */
