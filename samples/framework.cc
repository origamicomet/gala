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

#include <stdlib.h>
#include <stdio.h>

#if (AGL_PLATFORM == AGL_PLATFORM_WINDOWS)
  #include <malloc.h>
  #include <windows.h>
#elif (AGL_PLATFORM_IS_POSIX(AGL_PLATFORM))
  #include <malloc.h>
#else
  #error ("Unknown or unsupported platform!")
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const char *agl_err_to_string(const agl_err_t error) {
  switch (error) {
    case AGL_ENONE: return "AGL_ENONE";
    case AGL_EINVALIDARG: return "AGL_EINVALIDARG";
    case AGL_EUNKNOWN: return "AGL_EUNKNOWN";
    case AGL_EOUTOFMEMORY: return "AGL_EOUTOFMEMORY";
  } return "";
}

static void error_handler(const agl_err_t error) {
  fprintf(stderr, "agl error: %s\n", agl_err_to_string(error));
  exit(EXIT_FAILURE);
}

static void *_alloc(agl_allocator_t *, const size_t num_of_bytes, const size_t alignment) {
#if (AGL_PLATFORM == AGL_PLATFORM_WINDOWS)
  #if (AGL_COMPILER == AGL_COMPILER_MSVC)
    return __aligned_malloc(num_of_bytes, alignment);
  #elif (AGL_COMPILER == AGL_COMPILER_GCC)
    return __mingw_aligned_malloc(num_of_bytes, alignment);
  #else
    #error ("Unknown or unsupported compiler!")
  #endif
#elif (AGL_PLATFORM_IS_POSIX(AGL_PLATFORM))
  return memalign(alignment, num_of_bytes);
#else
  #error ("Unknown or unsupported platform!")
#endif
}

static void *_realloc(agl_allocator_t *, void *ptr, const size_t num_of_bytes, const size_t alignment) {
#if (AGL_PLATFORM == AGL_PLATFORM_WINDOWS)
  #if (AGL_COMPILER == AGL_COMPILER_MSVC)
    return __aligned_realloc(ptr, num_of_bytes, alignment);
  #elif (AGL_COMPILER == AGL_COMPILER_GCC)
    return __mingw_aligned_realloc(ptr, num_of_bytes, alignment);
  #else
    #error ("Unknown or unsupported compiler!")
  #endif
#elif (AGL_PLATFORM_IS_POSIX(AGL_PLATFORM))
  ptr = realloc(ptr, num_of_bytes);
  if ((((uintptr_t)ptr) % alignment) == 0)
    return ptr;
  void *aligned = memalign(alignment, num_of_bytes);
  memcpy(aligned, ptr, num_of_bytes);
  free(ptr);
  return aligned;
#else
  #error ("Unknown or unsupported platform!")
#endif
}

static void _free(agl_allocator_t *, void *ptr) {
#if (AGL_PLATFORM == AGL_PLATFORM_WINDOWS)
  #if (AGL_COMPILER == AGL_COMPILER_MSVC)
    __aligned_free(ptr);
  #elif (AGL_COMPILER == AGL_COMPILER_GCC)
    __mingw_aligned_free(ptr);
  #else
    #error ("Unknown or unsupported compiler!")
  #endif
#elif (AGL_PLATFORM_IS_POSIX(AGL_PLATFORM))
  free(ptr);
#else
  #error ("Unknown or unsupported platform!")
#endif
}

static bool heap_backed_command_list_exhausted(agl_command_list_t *command_list) {
  const size_t offs = command_list->current - command_list->begin;
  const size_t size = command_list->end - command_list->begin;
  const size_t new_size = ((size == 0) ? 1 : size) * 2;
  command_list->begin = (uintptr_t)realloc((void *)command_list->begin, new_size);
  command_list->current = command_list->begin + offs;
  command_list->end = command_list->begin + new_size;
  return true;
}

agl_backend_t agl_backend_from_str(
  const char* str)
{
  if (strcmp("d3d9", str) == 0) {
    return AGL_BACKEND_D3D9;
  } else if (strcmp("d3d11", str) == 0) {
    return AGL_BACKEND_D3D11;
  } else if (strcmp("opengl", str) == 0) {
    return AGL_BACKEND_OPENGL;
  } else if (strcmp("gles2", str) == 0) {
    return AGL_BACKEND_GLES2;
  } else if (strcmp("gles3", str) == 0) {
    return AGL_BACKEND_GLES3;
  }

  return AGL_BACKEND_NULL;
}

int agl_sample_run(
  agl_backend_t backend,
  const char *name,
  uint32_t width,
  uint32_t height,
  agl_sample_update_fn update,
  agl_sample_render_fn render)
{
  agl_set_error_handler(&error_handler);
  agl_allocator_t allocator = { &_alloc, &_realloc, &_free };
  agl_set_allocator(&allocator);
  agl_initialize(backend);
  agl_command_list_t cmds = { 0, 0, 0, &heap_backed_command_list_exhausted };

#if (AGL_PLATFORM == AGL_PLATFORM_WINDOWS)
  WNDCLASSEXA wcx;
  memset((void *)&wcx, 0, sizeof(WNDCLASSEXA));

  wcx.cbSize        = sizeof(WNDCLASSEXA);
  wcx.style         = CS_VREDRAW | CS_HREDRAW;
  wcx.lpfnWndProc   = DefWindowProc;
  wcx.hInstance     = GetModuleHandle(NULL);
  wcx.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wcx.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
  wcx.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
  wcx.lpszClassName = "sample";

  if (!RegisterClassExA(&wcx))
    return EXIT_FAILURE;

  DWORD styles = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW;
  DWORD ex_styles = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

  RECT client_area = { 0, 0, width, height };
  AdjustWindowRectEx(&client_area, styles, FALSE, ex_styles);

  HWND hwnd = CreateWindowExA(
    ex_styles, "sample", name, styles, 0, 0,
    client_area.right - client_area.left,
    client_area.bottom - client_area.top,
    NULL, NULL, GetModuleHandle(NULL), NULL);

  if (!hwnd)
    return EXIT_FAILURE;

  HMONITOR monitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONULL);
  if (!monitor)
    return EXIT_FAILURE;

  MONITORINFO mi;
  memset((void*)&mi, 0, sizeof(MONITORINFO));
  mi.cbSize = sizeof(MONITORINFO);
  if (!GetMonitorInfo(monitor, &mi))
    return EXIT_FAILURE;

  RECT encompassing_area;
  if (!GetWindowRect(hwnd, &encompassing_area))
    return EXIT_FAILURE;

  SetWindowPos(
    hwnd,
    HWND_TOP,
    (mi.rcMonitor.right - mi.rcMonitor.left - (encompassing_area.right - encompassing_area.left - 1)) / 2 + mi.rcMonitor.left,
    (mi.rcMonitor.bottom - mi.rcMonitor.top - (encompassing_area.bottom - encompassing_area.top - 1)) / 2 + mi.rcMonitor.top ,
    0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE);

  ShowWindow(hwnd, SW_SHOW);

  agl_context_t *context = agl_context_create(agl_adapter_primary());
  agl_swap_chain_t *swap_chain = agl_swap_chain_create(
    &cmds, (agl_surface_hndl_t)hwnd, AGL_R8G8B8A8, width, height, false, false);
  agl_command_list_execute(&cmds, context);

  while (!GetAsyncKeyState(VK_ESCAPE)) {
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

    update();
    cmds.current = cmds.begin;
    render(swap_chain, &cmds);
    agl_command_list_execute(&cmds, context);
  }
#else
  #error ("Unknown or unsupported platform!")
#endif
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
