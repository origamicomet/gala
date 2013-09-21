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

#include "framework.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static void update() {
}

static void render(agl_swap_chain_t *swap_chain, agl_command_list_t *cmds) {
  agl_swap_chain_present(swap_chain, cmds);
}

int main(int argc, const char *argv[]) {
#if (AGL_PLATFORM == AGL_PLATFORM_WINDOWS)
  agl_backend_t backend = AGL_BACKEND_D3D9;
#else
  agl_backend_t backend = AGL_BACKEND_NULL;
#endif
  for (int i = 1; i < argc; ++i)
    if (strncmp("--backend=", argv[i], 10) == 0)
      backend = agl_backend_from_str(&argv[i][10]);
  return agl_sample_run(backend, "Eigengrau", 1280, 720, &update, &render);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
