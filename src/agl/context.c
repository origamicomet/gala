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
 #  include <agl/context.h>
/* ========================================================================== */

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

#ifdef _MSC_VER
  #define alloca _alloca
#endif

#include <agl/log.h>
#include <agl/assert.h>
#include <agl/shared_library_.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ========================================================================== */
/*  Context:                                                                  */
/*   * agl_context_create                                                     */
/*   * agl_context_destroy                                                    */
/* ========================================================================== */

struct agl_context {
  agl_shared_lib_t *shared_lib_associated_with_backend;
};

/* ========================================================================== */
/*  agl_context_create:                                                       */
/* ========================================================================== */

static const char *backend_to_associated_shared_lib(const agl_backend_t backend) {
  switch (backend) {
    case AGL_BACKEND_D3D9:
      return "agl_backend_d3d9";
    case AGL_BACKEND_D3D11:
      return "agl_backend_d3d11";
    case AGL_BACKEND_OPENGL:
      return "agl_backend_opengl";
    case AGL_BACKEND_MANTLE:
      return "agl_backend_mantle";
    case AGL_BACKEND_GLES2:
      return "agl_backend_gles2";
    case AGL_BACKEND_GLES3:
      return "agl_backend_gles3";
  }
}

agl_context_t *agl_context_create(const agl_backend_t backend) {
  const char *name; {
    const size_t len = snprintf(
      NULL, 0, "%s.%s",
      backend_to_associated_shared_lib(backend),
      agl_shared_lib_extension()) + 1;
    name = (const char *)alloca(len);
    snprintf(
      (char *)name, len, "%s.%s",
      backend_to_associated_shared_lib(backend),
      agl_shared_lib_extension()); }
  agl_shared_lib_t *shared_lib = agl_shared_lib_open(name);
  if (!shared_lib)
    return NULL;
  agl_context_t *context = (agl_context_t *)malloc(sizeof(agl_context_t));
  context->shared_lib_associated_with_backend = shared_lib;
  return context;
}

/* ========================================================================== */
/*  agl_context_destroy:                                                      */
/* ========================================================================== */

void agl_context_destroy(agl_context_t *context) {
  agl_assert(debug, context != NULL);
  agl_shared_lib_close(context->shared_lib_associated_with_backend);
  free((void *)context);
}

/* ========================================================================== */

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* ========================================================================== */
