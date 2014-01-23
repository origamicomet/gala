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
 #  include <agl/backend.h>
/* ========================================================================== */

#include <agl/assert.h>
#include <agl/shared_library_.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct agl_backend {
  agl_shared_library_t *sl;
};

/* ========================================================================== */
/*  agl_backend_create:                                                       */
/* ========================================================================== */

agl_backend_t *agl_backend_create(const agl_backend_id_t id) {
  char shared_library_path[256] = { 0, };
  switch (id) {
    case AGL_BACKEND_D3D9:
      strcat(&shared_library_path[0], "agl_backend_d3d9"); break;
    case AGL_BACKEND_D3D11:
      strcat(&shared_library_path[0], "agl_backend_d3d11"); break;
    case AGL_BACKEND_OPENGL:
      strcat(&shared_library_path[0], "agl_backend_opengl"); break;
    case AGL_BACKEND_MANTLE:
      strcat(&shared_library_path[0], "agl_backend_mantle"); break;
    case AGL_BACKEND_GLES2:
      strcat(&shared_library_path[0], "agl_backend_gles2"); break;
    case AGL_BACKEND_GLES3:
      strcat(&shared_library_path[0], "agl_backend_gles3"); break;
    default:
      return NULL; }
  strcat(&shared_library_path[0], ".");
  strcat(&shared_library_path[0], agl_shared_library_extension());
  agl_shared_library_t *shared_library =
    agl_shared_library_open(&shared_library_path[0]);
  if (!shared_library)
    return NULL;
  // FIXME(mtwilliams): Use a user-specified allocator.
  agl_backend_t *backend = (agl_backend_t *)malloc(sizeof(agl_backend_t));
  backend->sl = shared_library;
  return backend;
}

/* ========================================================================== */
/*  agl_backend_destroy:                                                      */
/* ========================================================================== */

void agl_backend_destroy(agl_backend_t *backend) {
  agl_assert(debug, backend != NULL);
  agl_assert(paranoid, backend->sl != NULL);
  agl_shared_library_close(backend->sl);
  free((void *)backend);
}

/* ========================================================================== */

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* ========================================================================== */
