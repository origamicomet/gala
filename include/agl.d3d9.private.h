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

#ifndef _AGL_D3D39_PRIVATE_H_
#define _AGL_D3D39_PRIVATE_H_

#include <agl.d3d9.h>

#if (AGL_PLATFORM == AGL_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #define WIN32_EXTRA_LEAN
  #include <Windows.h>
  #undef WIN32_EXTRA_LEAN
  #undef WIN32_LEAN_AND_MEAN
  #include <D3D9.h>
#else
  #error ("Unknown or unsupported platform!")
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ========================================================================== */
/*  Integration:                                                              */
/*   * Errors & Error Handling                                                */
/*   * Memory Management                                                      */
/*   * Backends                                                               */
/*   * Initialization & Deinitialization                                      */
/* ========================================================================== */

/* ==========================================================================
    Errors & Error Handling (agl_error_t):
   ========================================================================== */

/* ... */

/* ==========================================================================
    Memory Management (agl_allocator_t):
   ========================================================================== */

/* ... */

/* ==========================================================================
    Backends (agl_backend_t):
   ========================================================================== */

/* ... */

/* ==========================================================================
    Initialization & Deinitialization (agl_initialize, agl_deinitialize):
   ========================================================================== */

/* ... */

/* ========================================================================== */
/*  Common/Types:                                                             */
/*   * Pixel Formats                                                          */
/* ========================================================================== */

/* ==========================================================================
    Pixel Formats (agl_pixel_format_t):
   ========================================================================== */

extern D3DFORMAT agl_pixel_format_to_d3d(
  const agl_pixel_format_t format);

/* ========================================================================== */
/*  Infrastructure:                                                           */
/*   * Adapters                                                               */
/*   * Outputs                                                                */
/*   * Display Modes                                                          */
/* ========================================================================== */

/* ==========================================================================
    Adapters (agl_adapter_t):
   ========================================================================== */

extern bool agl_device_capabilities_meet_requirements(
  const D3DCAPS9 *caps);

/* ==========================================================================
    Outputs (agl_output_t):
   ========================================================================== */

/* ... */

/* ==========================================================================
    Display Modes (agl_display_mode_t):
   ========================================================================== */

/* ... */

/* ========================================================================== */
/*  Runtime:                                                                  */
/*   * Contexts                                                               */
/*   * Command Lists                                                          */
/*   * Requests                                                               */
/*   * Resources                                                              */
/*     * Swap Chains                                                          */
/* ========================================================================== */

/* ==========================================================================
    Contexts (agl_context_t):
   ========================================================================== */

struct agl_context_d3d9 {
  agl_context_t context;
  HWND hwnd;
  IDirect3DDevice9 *d3dd9;
};

/* ==========================================================================
    Command Lists (agl_command_list_t):
   ========================================================================== */

/* ... */

/* ==========================================================================
    Requests (agl_request_t):
   ========================================================================== */

/* ... */

/* ==========================================================================
    Resources (agl_resource_t):
   ========================================================================== */

/* ... */

/* ==========================================================================
    Resources > Swap Chains:
   ========================================================================== */

struct agl_swap_chain_d3d9 {
  agl_swap_chain_t swap_chain;
  IDirect3DSwapChain9 *intf;
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _AGL_D3D39_PRIVATE_H_ */
