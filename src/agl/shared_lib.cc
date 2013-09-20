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

#include <agl/shared_lib.h>

#if (AGL_PLATFORM == AGL_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #define WIN32_EXTRA_LEAN
  #include <Windows.h>
  #undef WIN32_EXTRA_LEAN
  #undef WIN32_LEAN_AND_MEAN
#else
  #error ("Unknown or unsupported platform!")
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ==========================================================================
    Shared Libraries (agl_shared_lib_t):
   ========================================================================== */

agl_shared_lib_t *agl_shared_lib_open(
  const char *path)
{
#if (AGL_PLATFORM == AGL_PLATFORM_WINDOWS)
  HMODULE lib = LoadLibraryA(path);
  if (!lib)
    return NULL;
  return ((agl_shared_lib_t *)lib);
#else
  #error ("Unknown or unsupported platform!")
#endif
}

void *agl_shared_lib_sym(
  agl_shared_lib_t *shared_lib,
  const char *name)
{
#if (AGL_PLATFORM == AGL_PLATFORM_WINDOWS)
  return ((void *)GetProcAddress((HMODULE)shared_lib, name));
#else
  #error ("Unknown or unsupported platform!")
#endif
}

uint agl_shared_lib_close(
  agl_shared_lib_t *shared_lib)
{
#if (AGL_PLATFORM == AGL_PLATFORM_WINDOWS)
  FreeLibrary(((HMODULE)shared_lib));
#else
  #error ("Unknown or unsupported platform!")
#endif
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
