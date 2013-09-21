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

#ifndef _AGL_D3D39_H_
#define _AGL_D3D39_H_

#include <agl.h>
#include <agl.private.h>

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

/*! ... */
extern void agl_initialize_d3d9();

/*! ... */
extern void agl_deinitialize_d3d9();

/* ========================================================================== */
/*  Common/Types:                                                             */
/*   * Pixel Formats                                                          */
/* ========================================================================== */

/* ==========================================================================
    Pixel Formats (agl_pixel_format_t):
   ========================================================================== */

/* ... */

/* ========================================================================== */
/*  Infrastructure:                                                           */
/*   * Adapters                                                               */
/*   * Outputs                                                                */
/*   * Display Modes                                                          */
/* ========================================================================== */

/* ==========================================================================
    Adapters (agl_adapter_t):
   ========================================================================== */

/* ... */

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

/*! ... */
typedef struct agl_context_d3d9 agl_context_d3d9_t;

/* ========================================================================== */

/*! ... */
extern agl_context_t *agl_context_alloc_d3d9();

/*! ... */
extern void agl_context_free_d3d9(agl_context_t *context);

/* ========================================================================== */

/*! ... */
extern void agl_context_create_d3d9(
  agl_context_t *context);

/*! ... */
extern void agl_context_destroy_d3d9(
  agl_context_t *context);

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

/*! ... */
typedef struct agl_swap_chain_d3d9 agl_swap_chain_d3d9_t;

/* ========================================================================== */

/*! ... */
extern agl_swap_chain_t *agl_swap_chain_alloc_d3d9();

/*! ... */
extern void agl_swap_chain_free_d3d9(agl_swap_chain_t *swap_chain);

/* ========================================================================== */

/*! ... */
extern void agl_swap_chain_create_d3d9(
  agl_swap_chain_t *swap_chain,
  agl_context_t *context);

/*! ... */
extern void agl_swap_chain_destroy_d3d9(
  agl_swap_chain_t *swap_chain,
  agl_context_t *context);

/*! ... */
extern void agl_swap_chain_present_d3d9(
  agl_swap_chain_t *swap_chain,
  agl_context_t *context);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _AGL_D3D39_H_ */
