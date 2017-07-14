//===-- gala/wgl.cc -------------------------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//

#include "gala/wgl.h"

// TODO(mtwilliams): Improve the structure of this code.
// TODO(mtwilliams): Improve error handling.

#if GALA_ENABLE_OPENGL
#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS

#include <Windows.h>

GALA_BEGIN_EXTERN_C

// HACK(mtwilliams): We pun undecorated names with preprocessor because Windows
// headers declare functions of the same name.

static HMODULE gl;
static HMODULE gdi;

#define WGL_DRAW_TO_WINDOW_ARB                    0x2001
#define WGL_DRAW_TO_BITMAP_ARB                    0x2002

#define WGL_ACCELERATION_ARB                      0x2003
#define WGL_SUPPORT_OPENGL_ARB                    0x2010
#define WGL_SUPPORT_GDI_ARB                       0x200F

#define WGL_PIXEL_TYPE_ARB                        0x2013
#define WGL_TYPE_RGBA_ARB                         0x202B

#define WGL_COLOR_BITS_ARB                        0x2014
#define WGL_RED_BITS_ARB                          0x2015
#define WGL_GREEN_BITS_ARB                        0x2017
#define WGL_BLUE_BITS_ARB                         0x2019
#define WGL_ALPHA_BITS_ARB                        0x201B
#define WGL_DEPTH_BITS_ARB                        0x2022
#define WGL_STENCIL_BITS_ARB                      0x2023

#define WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB          0x20A9

#define WGL_COLORSPACE_EXT                        0x309D
#define WGL_COLORSPACE_SRGB_EXT                   0x3089
#define WGL_COLORSPACE_LINEAR_EXT                 0x308A

#define WGL_SWAP_METHOD_ARB                       0x2007
#define WGL_DOUBLE_BUFFER_ARB                     0x2011

#define WGL_STEREO_ARB                            0x2012

#define WGL_SWAP_EXCHANGE_ARB                     0x2028
#define WGL_SWAP_COPY_ARB                         0x2029
#define WGL_SWAP_UNDEFINED_ARB                    0x202A

#define WGL_NO_ACCELERATION_ARB                   0x2025
#define WGL_GENERIC_ACCELERATION_ARB              0x2026
#define WGL_FULL_ACCELERATION_ARB                 0x2027

#define WGL_CONTEXT_MAJOR_VERSION_ARB             0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB             0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB              0x9126
#define WGL_CONTEXT_LAYER_PLANE_ARB               0x2093
#define WGL_CONTEXT_FLAGS_ARB                     0x2094
#define WGL_CONTEXT_RELEASE_BEHAVIOR_ARB          0x2097

#define WGL_CONTEXT_DEBUG_BIT_ARB                 0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB    0x0002

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002

#define WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB     0x0000
#define WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB    0x2098

typedef const char *(WINAPI *WGLGETEXTENSIONSSTRINGPROC)(HDC hdc);
typedef void *(WINAPI *WGLGETPROCADDRESSPROC)(const char *name);

#define wglGetExtensionsString __gala_wglGetExtensionsString
#define wglGetProcAddress __gala_wglGetProcAddress

static WGLGETEXTENSIONSSTRINGPROC __gala_wglGetExtensionsString = NULL;
static WGLGETPROCADDRESSPROC __gala_wglGetProcAddress = NULL;

typedef HGLRC (WINAPI *WGLCREATECONTEXTPROC)(HDC hdc);
typedef BOOL (WINAPI *WGLDELETECONTEXTPROC)(HGLRC hglrc);
typedef BOOL (WINAPI *WGLMAKECURRENTPROC)(HDC hdc, HGLRC hglrc);

#define wglCreateContext __gala_wglCreateContext
#define wglDeleteContext __gala_wglDeleteContext
#define wglMakeCurrent __gala_wglMakeCurrent

static WGLCREATECONTEXTPROC __gala_wglCreateContext = NULL;
static WGLDELETECONTEXTPROC __gala_wglDeleteContext = NULL;
static WGLMAKECURRENTPROC __gala_wglMakeCurrent = NULL;

typedef BOOL (WINAPI *WGLCHOOSEPIXELFORMATPROC)(HDC hdc, const UINT *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
typedef HGLRC (WINAPI *WGLCREATECONTEXTATTRIBSPROC)(HDC hDC, HGLRC hShareContext, const UINT *attribList);

#define wglChoosePixelFormat __gala_wglChoosePixelFormat
#define wglCreateContextAttribs __gala_wglCreateContextAttribs

static WGLCHOOSEPIXELFORMATPROC __gala_wglChoosePixelFormat = NULL;
static WGLCREATECONTEXTATTRIBSPROC __gala_wglCreateContextAttribs = NULL;

typedef BOOL (WINAPI *WGLSWAPINTERVALPROC)(int interval);
typedef BOOL (WINAPI *SWAPBUFFERSPROC)(HDC hdc);

#define wglSwapInterval __gala_wglSwapInterval
#define SwapBuffers __gala_SwapBuffers

static WGLSWAPINTERVALPROC __gala_wglSwapInterval = NULL;
static SWAPBUFFERSPROC __gala_SwapBuffers = NULL;

// TODO(mtwilliams): Affinity?
 // WGL_AMD_gpu_association
 // WGL_NV_gpu_affinity

static const char *WGL_ACTUAL_CONTEXT_CLASS    = "163207f8-4dfe-46ce-9bef-593e1485859d";
static const char *WGL_BOOTSTRAP_CONTEXT_CLASS = "02d5662d-766e-4144-8e1d-d8e21975af9d";

static void gala_wgl_register_context_classes(void)
{
  // We register two distinct window classes to aid differentiation of context
  // types. One is for our boostrap context and the other for the contexts we
  // use.

  WNDCLASSEXA actual_context_class;
  memset((void *)&actual_context_class, 0, sizeof(WNDCLASSEXA));

  actual_context_class.cbSize        = sizeof(WNDCLASSEXA);
  actual_context_class.style         = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
  actual_context_class.lpfnWndProc   = DefWindowProc;
  actual_context_class.hInstance     = GetModuleHandle(NULL);
  actual_context_class.hCursor       = LoadCursor(NULL, IDC_ARROW);
  actual_context_class.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
  actual_context_class.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
  actual_context_class.lpszClassName = WGL_ACTUAL_CONTEXT_CLASS;

  static const BOOL registered_actual_context_class_succesfully =
    RegisterClassExA(&actual_context_class);

  gala_assert(registered_actual_context_class_succesfully);

  // We have to create a dummy context to create a core context...
  WNDCLASSEXA bootstrap_context_class;
  memset((void *)&bootstrap_context_class, 0, sizeof(WNDCLASSEXA));

  bootstrap_context_class.cbSize        = sizeof(WNDCLASSEXA);
  bootstrap_context_class.style         = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
  bootstrap_context_class.lpfnWndProc   = DefWindowProc;
  bootstrap_context_class.hInstance     = GetModuleHandle(NULL);
  bootstrap_context_class.hCursor       = LoadCursor(NULL, IDC_ARROW);
  bootstrap_context_class.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
  bootstrap_context_class.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
  bootstrap_context_class.lpszClassName = WGL_BOOTSTRAP_CONTEXT_CLASS;

  static const BOOL registered_boostrap_context_class_succesfully =
    RegisterClassExA(&bootstrap_context_class);

  gala_assert(registered_boostrap_context_class_succesfully);
}

static void gala_wgl_check_for_required_extensions(HWND hwnd, HDC hdc, HGLRC hglrc)
{
  (void)hwnd;
  (void)hglrc;

  const char *extensions = wglGetExtensionsString(hdc);
  gala_assert(extensions != NULL);

  // QUESTION(mtwilliams): Should we require WGL_ARB_context_flush_control?
  static const char *required[] = {
    "WGL_ARB_pixel_format",
    "WGL_ARB_create_context",
    "WGL_ARB_create_context_profile",
    "WGL_EXT_swap_control",
    "WGL_EXT_swap_control_tear"
  };

  static const unsigned count = sizeof(required) / sizeof(required[0]);

  for (unsigned i = 0; i < count; ++i) {
    // TODO(mtwilliams): Replace `strstr` with a custom implementation to
    // remove dependence on standard library?
    const gala_bool_t advertised = (strstr(extensions, required[i]) != 0);
    gala_assertf(advertised, "Required extension `%s` is not available!", required[i]);
  }
}

static void gala_wgl_create_bootstrap_context_window(
  HWND *bootstrap_context_window)
{
  *bootstrap_context_window =
    CreateWindowA(WGL_BOOTSTRAP_CONTEXT_CLASS,
                  WGL_BOOTSTRAP_CONTEXT_CLASS,
                  WS_POPUP | WS_DISABLED,
                  0, 0, 1, 1,
                  NULL,
                  NULL,
                  GetModuleHandle(NULL),
                  NULL);

  gala_assert(*bootstrap_context_window != NULL);
}

static void gala_wgl_create_bootstrap_context(
  HWND bootstrap_context_window,
  HDC *bootstrap_context_hdc,
  HGLRC *bootstrap_context_hglrc)
{
  *bootstrap_context_hdc = GetDC(bootstrap_context_window);
  gala_assert(*bootstrap_context_hdc != NULL);

  PIXELFORMATDESCRIPTOR pixel_format_desc;
  memset((void *)&pixel_format_desc, 0, sizeof(PIXELFORMATDESCRIPTOR));

  pixel_format_desc.nSize        = sizeof(PIXELFORMATDESCRIPTOR);
  pixel_format_desc.nVersion     = 1;
  pixel_format_desc.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pixel_format_desc.iPixelType   = PFD_TYPE_RGBA;
  pixel_format_desc.cColorBits   = 24;
  pixel_format_desc.cAlphaBits   = 0;
  pixel_format_desc.cDepthBits   = 0;
  pixel_format_desc.cStencilBits = 0;
  pixel_format_desc.iLayerType   = PFD_MAIN_PLANE;

  const int pixel_format = ChoosePixelFormat(*bootstrap_context_hdc,
                                             &pixel_format_desc);
  gala_assert(pixel_format != 0);

  const BOOL set_pixel_format_succesfully = !!SetPixelFormat(*bootstrap_context_hdc,
                                                             pixel_format,
                                                             &pixel_format_desc);
  gala_assert(set_pixel_format_succesfully);

  *bootstrap_context_hglrc = wglCreateContext(*bootstrap_context_hdc);
  gala_assert(*bootstrap_context_hglrc != NULL);
}

void gala_wgl_init(void)
{
  gl = ::LoadLibraryA("opengl32.dll");
  gala_assert(gl != NULL);

  wglGetProcAddress = (WGLGETPROCADDRESSPROC)GetProcAddress(gl, "wglGetProcAddress");
  wglCreateContext  = (WGLCREATECONTEXTPROC)GetProcAddress(gl, "wglCreateContext");
  wglDeleteContext  = (WGLDELETECONTEXTPROC)GetProcAddress(gl, "wglDeleteContext");
  wglMakeCurrent    = (WGLMAKECURRENTPROC)GetProcAddress(gl, "wglMakeCurrent");

  gala_wgl_register_context_classes();

  HWND bootstrap_context_window;
  HDC bootstrap_context_hdc;
  HGLRC bootstrap_context_hglrc;

  gala_wgl_create_bootstrap_context_window(&bootstrap_context_window);
  gala_wgl_create_bootstrap_context(bootstrap_context_window,
                                    &bootstrap_context_hdc,
                                    &bootstrap_context_hglrc);

  wglMakeCurrent(bootstrap_context_hdc, bootstrap_context_hglrc);

  // NOTE(mtwilliams): We assume that `WGL_ARB_extensions_string` is available.
  wglGetExtensionsString = (WGLGETEXTENSIONSSTRINGPROC)wglGetProcAddress("wglGetExtensionsStringARB");

  gala_wgl_check_for_required_extensions(bootstrap_context_window,
                                         bootstrap_context_hdc,
                                         bootstrap_context_hglrc);

  // TODO(mtwilliams): Refresh previously fetched function pointers?
  // wglGetProcAddress = (WGLGETPROCADDRESSPROC)wglGetProcAddress("wglGetProcAddress");
  // wglCreateContext  = (WGLCREATECONTEXTPROC)wglGetProcAddress("wglCreateContext");
  // wglDeleteContext  = (WGLDELETECONTEXTPROC)wglGetProcAddress("wglDeleteContext");
  // wglMakeCurrent    = (WGLMAKECURRENTPROC)wglGetProcAddress("wglMakeCurrent");

  wglChoosePixelFormat = (WGLCHOOSEPIXELFORMATPROC)wglGetProcAddress("wglChoosePixelFormatARB");
  wglCreateContextAttribs = (WGLCREATECONTEXTATTRIBSPROC)wglGetProcAddress("wglCreateContextAttribsARB");
  wglSwapInterval = (WGLSWAPINTERVALPROC)wglGetProcAddress("wglSwapIntervalEXT");

  wglMakeCurrent(NULL, NULL);

  // TODO(mtwilliams): Determine if we should keep the bootstrap context around
  // until shutdown. Probably not.
  wglDeleteContext(bootstrap_context_hglrc);
  ReleaseDC(bootstrap_context_window, bootstrap_context_hdc);
  DestroyWindow(bootstrap_context_window);

  gdi = ::LoadLibraryA("gdi32.dll");
  gala_assert(gdi != NULL);

  SwapBuffers = (SWAPBUFFERSPROC)GetProcAddress(gdi, "SwapBuffers");
}

void gala_wgl_shutdown(void)
{
  // TODO(mtwilliams): Actually implement this. ;)
}

void *gala_wgl_get_proc_address(
  const char *name)
{
  gala_assert_debug(name != NULL);

  if (void *addr = wglGetProcAddress(name))
    return addr;

  return GetProcAddress(gl, name);
}

struct gala_wgl_context {
  HWND window;

  // Indicates if we own `window` and should destroy it.
  gala_bool_t owner_of_window;

  // Drawing and resource contexts.
  HDC hdc;
  HGLRC hglrc;

  // Cached for surfaces.
  int pixel_format;
  PIXELFORMATDESCRIPTOR pixel_format_desc;
};

static void gala_wgl_create_context_window(
  HWND *actual_context_window)
{
  *actual_context_window =
    CreateWindowA(WGL_ACTUAL_CONTEXT_CLASS,
                  WGL_ACTUAL_CONTEXT_CLASS,
                  WS_POPUP | WS_DISABLED,
                  0, 0, 1, 1,
                  NULL,
                  NULL,
                  GetModuleHandle(NULL),
                  NULL);

  gala_assert(*actual_context_window != NULL);
}

gala_wgl_context_t *gala_wgl_create_context(
  const gala_wgl_context_creation_params_t *context_creation_params)
{
  gala_assert_debug(context_creation_params != NULL);

  gala_wgl_context_t *context =
    (gala_wgl_context_t *)calloc(1, sizeof(gala_wgl_context_t));

  gala_wgl_create_context_window(&context->window);

  // REFACTOR(mtwilliams): Allow context creation on an existing window?
  context->owner_of_window = true;

  context->hdc = GetDC(context->window);
  gala_assert(context->hdc != NULL);

  const gala_pixel_format_t format = GALA_PIXEL_FORMAT_R8G8B8;

  // HACK(mtwilliams): Other formats are inconscient, buggy, or not available.
  gala_assert(format == GALA_PIXEL_FORMAT_R8G8B8 ||
              format == GALA_PIXEL_FORMAT_R8G8B8A8);

  const UINT pixel_format_attributes[] = {
    // Goes without saying...
    WGL_DRAW_TO_WINDOW_ARB, TRUE,

    // Yeah...
    WGL_SUPPORT_OPENGL_ARB, TRUE,

    // Don't know if software is supported in practice...
    WGL_ACCELERATION_ARB, (context_creation_params->flags & GALA_WGL_CONTEXT_ACCELERATED)
                            ? WGL_FULL_ACCELERATION_ARB : WGL_NO_ACCELERATION_ARB,

    // See note above.
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_COLOR_BITS_ARB, 24,
    WGL_RED_BITS_ARB, 8,
    WGL_GREEN_BITS_ARB, 8,
    WGL_BLUE_BITS_ARB, 8,
    WGL_ALPHA_BITS_ARB, (format == GALA_PIXEL_FORMAT_R8G8B8A8) ? 8 : 0,

    // TODO(mtwilliams): Explictly request linear?
    // WGL_COLORSPACE_EXT, WGL_COLORSPACE_LINEAR_EXT,

    // PERF(mtwilliams): Determine if `WGL_SWAP_EXCHANGE_ARB` is fast path, as
    // some say it is. It should be as it's just exchanging pointers rather
    // than copying contents like `WGL_SWAP_COPY_ARB`. Except,
    // `WGL_SWAP_COPY_ARB` is analogous to `DXGI_SWAP_EFFECT_DISCARD` which is
    // the fast path for D3D11...
    WGL_SWAP_METHOD_ARB, WGL_SWAP_EXCHANGE_ARB,
    WGL_DOUBLE_BUFFER_ARB, TRUE,

    0
  };

  // TODO(mtwilliams): Determine if we can pass `NULL`.
  UINT unused;

  const BOOL chose_pixel_format_succesfully =
    wglChoosePixelFormat(context->hdc, &pixel_format_attributes[0], NULL, 1, &context->pixel_format, &unused);

  gala_assert(chose_pixel_format_succesfully);

  // Yeah...
  DescribePixelFormat(context->hdc, context->pixel_format, sizeof(PIXELFORMATDESCRIPTOR), &context->pixel_format_desc);

  SetPixelFormat(context->hdc, context->pixel_format, &context->pixel_format_desc);

  UINT flags = 0x00000000;
  if (context_creation_params->flags & GALA_WGL_CONTEXT_DEBUG)
    flags |= WGL_CONTEXT_DEBUG_BIT_ARB;

  const UINT context_attributes[] = {
    WGL_CONTEXT_MAJOR_VERSION_ARB, context_creation_params->version.major,
    WGL_CONTEXT_MINOR_VERSION_ARB, context_creation_params->version.minor,

    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,

    // PERF(mtwilliams): Determine if we incur a context release when we only
    // change `hdc` and not `hglrc`.
    WGL_CONTEXT_RELEASE_BEHAVIOR_ARB, WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB,

    WGL_CONTEXT_FLAGS_ARB, flags,

    0
  };

  context->hglrc = wglCreateContextAttribs(context->hdc,
                                           context_creation_params->share ?
                                             context_creation_params->share->hglrc : NULL,
                                           &context_attributes[0]);

  gala_assertf(context->hglrc, "Unable to create context!");

  return context;
}

void gala_wgl_destroy_context(
  gala_wgl_context_t *context)
{  gala_assert_debug(context != NULL);

  wglDeleteContext(context->hglrc);
  ReleaseDC(context->window, context->hdc);

  if (context->owner_of_window)
    DestroyWindow(context->window);

  free((void *)context);
}

typedef struct gala_wgl_surface {
  HWND window;
  HDC hdc;
  gala_bool_t fullscreen;
  gala_bool_t borderless;
} gala_wgl_surface_t;

gala_wgl_surface_t *gala_wgl_create_surface(
  gala_wgl_context_t *context,
  gala_uintptr_t window,
  gala_uint32_t flags)
{
  gala_assert_debug(context != NULL);
  gala_assert_debug(window != NULL);
  gala_assert_debug(IsWindow((HWND)window));

  gala_wgl_surface_t *surface =
    (gala_wgl_surface_t *)calloc(1, sizeof(gala_wgl_surface_t));

  surface->window = (HWND)window;
  surface->hdc = GetDC(surface->window);

  // TODO(mtwilliams): Respect flags.
   // https://www.reddit.com/r/vulkan/comments/4ep1pa/no_exclusive_fullscreen_ways_to_bypass_the_dwm
  surface->fullscreen = !!(flags & GALA_WGL_SURFACE_FULLSCREEN);
  surface->borderless = !!(flags & GALA_WGL_SURFACE_BORDERLESS);

  // TODO(mtwilliams): Figure out a nicer way to do this.
  SetPixelFormat(surface->hdc, context->pixel_format, &context->pixel_format_desc);

  return surface;
}

void gala_wgl_destroy_surface(
  gala_wgl_surface_t *surface)
{
  gala_assert_debug(surface != NULL);

  ReleaseDC(surface->window, surface->hdc);

  free((void *)surface);
}

void gala_wgl_dimensions_of_surface(
  gala_wgl_surface_t *surface,
  gala_uint32_t *width,
  gala_uint32_t *height)
{
  gala_assert_debug(surface != NULL);
  gala_assert_debug(width != NULL);
  gala_assert_debug(height != NULL);

  RECT area = { 0, };
  ::GetClientRect(surface->window, &area);

  *width = area.right - area.left;
  *height = area.bottom - area.top;
}

void gala_wgl_bind(
  const gala_wgl_context_t *context,
  const gala_wgl_surface_t *surface)
{
  if (context) {
    wglMakeCurrent(surface ? surface->hdc : context->hdc, context->hglrc);
  } else {
    wglMakeCurrent(NULL, NULL);
  }
}

// TODO(mtwilliams): Investigate surface sharing with DXGI. We could try
// copying to a `IDXGISwapChain` after "presentation" and present through
// `IDXGISwapChain::Present` instead of `wglMakeCurrent`. WGL_NV_DX_interop2
// seems like the only path to do so, and has varying support across the big
// three.
//
// TODO(mtwilliams): Should also investigate presentation using
// NV_copy_image and/or ARB_copy_image.

// TODO(mtwilliams): If we don't have swap groups:
//  * Swap the first with an interval of 1.
//  * Then swap the rest with an interval of -1, i.e. tear if we miss.

// TODO(mtwilliams): Use `wglSwapMultipleBuffers` to prevent blocking?

void gala_wgl_present(
  gala_uint32_t n,
  gala_wgl_surface_t * const *surfaces,
  gala_uint32_t flags)
{
  gala_assert_debug(surfaces != NULL);

  if (flags & GALA_WGL_PRESENT_SYNCHRONIZE)
    if (flags & GALA_WGL_PRESENT_TEAR_ON_MISS)
      wglSwapInterval(-1);
    else
      wglSwapInterval(1);
  else
    wglSwapInterval(0);

  // TODO(mtwilliams): Use wglSwapMultipleBuffers?
  for (gala_uint32_t i = 0; i < n; ++i)
    SwapBuffers(surfaces[i]->hdc);
}

GALA_END_EXTERN_C

#endif // GALA_PLATFORM_WINDOWS
#endif // GALA_ENABLE_OPENGL
