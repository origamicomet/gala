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
 #  include <agl/shared_library_.h>
/* ========================================================================== */

#include <agl/assert.h>

#if defined(_WIN32)
  #include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ========================================================================== */
/*  Shared Library:                                                           */
/* ========================================================================== */

struct agl_shared_library {};

/* ========================================================================== */
/*  agl_shared_library_open:                                                  */
/* ========================================================================== */

agl_shared_library_t *agl_shared_library_open(
  const char *name)
{
  agl_assert(debug, name != NULL);
#if defined(_WIN32)
  return (agl_shared_library_t *)
    LoadLibraryA(name);
#endif
}

/* ========================================================================== */
/*  agl_shared_library_symbol:                                                */
/* ========================================================================== */

void *agl_shared_library_symbol(
  const agl_shared_library_t *shared_library,
  const char *name)
{
  agl_assert(debug, shared_library != NULL);
  agl_assert(debug, name != NULL);
#if defined(_WIN32)
  return (void *)GetProcAddress((HMODULE)shared_library, name);
#endif
}

/* ========================================================================== */
/*  agl_shared_library_close:                                                  */
/* ========================================================================== */

void agl_shared_library_close(
  agl_shared_library_t *shared_library)
{
  agl_assert(debug, shared_library != NULL);
#if defined(_WIN32)
  FreeLibrary((HMODULE)shared_library);
#endif
}

/* ========================================================================== */

#ifdef __cplusplus
}
#endif /* __cplusplus */
