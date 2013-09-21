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

#include <agl.d3d9.h>
#include <agl.d3d9.private.h>

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

static agl_shared_lib_t *_agl_d3d9_dll = NULL;
static IDirect3D9 *_agl_d3d9 = NULL;

void agl_initialize_d3d9()
{
  WNDCLASSEXA wcx;
  memset((void *)&wcx, 0, sizeof(WNDCLASSEXA));

  wcx.cbSize        = sizeof(WNDCLASSEXA);
  wcx.style         = CS_VREDRAW | CS_HREDRAW;
  wcx.lpfnWndProc   = DefWindowProc;
  wcx.hInstance     = GetModuleHandle(NULL);
  wcx.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wcx.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
  wcx.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
  wcx.lpszClassName = "agl";

  if (!RegisterClassExA(&wcx))
    agl_error(AGL_EUNKNOWN);

  _agl_d3d9_dll = agl_shared_lib_open("d3d9.dll");
  if (!_agl_d3d9_dll)
    agl_error(AGL_EUNKNOWN);

  typedef IDirect3D9 *(WINAPI *Direct3DCreate9_fn)(UINT sdk_ver);
  Direct3DCreate9_fn Direct3DCreate9_ =
    (Direct3DCreate9_fn)agl_shared_lib_sym(_agl_d3d9_dll, "Direct3DCreate9");
  if (!Direct3DCreate9_)
    agl_error(AGL_EUNKNOWN);

  _agl_d3d9 = Direct3DCreate9_(D3D_SDK_VERSION);
  if (!_agl_d3d9)
    agl_error(AGL_EUNKNOWN);

  _agl_num_of_adapters = 0; {
    D3DCAPS9 caps;
    UINT adapter = D3DADAPTER_DEFAULT;
    while (IDirect3D9_GetDeviceCaps(_agl_d3d9, adapter, D3DDEVTYPE_HAL, &caps) == D3D_OK) {
      if (agl_device_capabilities_meet_requirements(&caps))
        _agl_num_of_adapters++;
      adapter++;
    }
  }

  _agl_adapters = (const agl_adapter_t *)agl_alloc(
    _agl_num_of_adapters * sizeof(agl_adapter_t),
    agl_alignof(agl_adapter_t));

  /* _agl_adapters = */ {
    D3DCAPS9 caps;
    UINT adapter = D3DADAPTER_DEFAULT;
    size_t adapter_id = 0;
    while (IDirect3D9_GetDeviceCaps(_agl_d3d9, adapter, D3DDEVTYPE_HAL, &caps) == D3D_OK) {
      if (!agl_device_capabilities_meet_requirements(&caps))
        { adapter++; continue; }

      agl_adapter_t *adapter_ = (agl_adapter_t *)&_agl_adapters[adapter_id];
      adapter_->primary = !!(adapter == D3DADAPTER_DEFAULT);
      adapter_->type = AGL_HARDWARE;
      adapter_->num_of_outputs = 1;
      adapter_->outputs = (const agl_output_t *)agl_alloc(
        sizeof(agl_output_t), agl_alignof(agl_output_t));
      adapter_->_internal = (uintptr_t)adapter;

      agl_output_t *output = (agl_output_t *)&adapter_->outputs[0]; {
        output->primary = true;
        output->num_of_display_modes =
          IDirect3D9_GetAdapterModeCount(_agl_d3d9, adapter, D3DFMT_X8R8G8B8);
        output->display_modes = (const agl_display_mode_t *)agl_alloc(
          output->num_of_display_modes * sizeof(agl_display_mode_t),
          agl_alignof(agl_display_mode_t));
        /* output->display_modes = */ {
          D3DDISPLAYMODE display_mode;
          UINT mode = 0;
          size_t display_mode_id = 0;
          while (IDirect3D9_EnumAdapterModes(_agl_d3d9, adapter, D3DFMT_X8R8G8B8, mode, &display_mode) == D3D_OK) {
            agl_display_mode_t *display_mode_ =
              (agl_display_mode_t *)&output->display_modes[display_mode_id];
            display_mode_->format = AGL_R8G8B8A8;
            display_mode_->width = display_mode.Width;
            display_mode_->height = display_mode.Height;
            display_mode_->refresh_rate = display_mode.RefreshRate;
            display_mode_id++;
            mode++;
          }
        }
      }

      _agl_num_of_adapters++;
      adapter++;
    }
  }
}

void agl_deinitialize_d3d9()
{
  IDirect3D9_Release(_agl_d3d9);
  agl_shared_lib_close(_agl_d3d9_dll);
  // TODO(mtwilliams): Fix memory leak w/ adapters.
}

/* ========================================================================== */
/*  Common/Types:                                                             */
/*   * Pixel Formats                                                          */
/* ========================================================================== */

/* ==========================================================================
    Pixel Formats (agl_pixel_format_t):
   ========================================================================== */

D3DFORMAT agl_pixel_format_to_d3d(
  const agl_pixel_format_t format)
{
  switch (format) {
    case AGL_R8G8B8: return D3DFMT_R8G8B8;
    case AGL_R8G8B8A8: return D3DFMT_A8R8G8B8;
    case AGL_D24_S8: return D3DFMT_D24S8;
  }

  return D3DFMT_UNKNOWN;
}

/* ========================================================================== */
/*  Infrastructure:                                                           */
/*   * Adapters                                                               */
/*   * Outputs                                                                */
/*   * Display Modes                                                          */
/* ========================================================================== */

/* ==========================================================================
    Adapters (agl_adapter_t):
   ========================================================================== */

bool agl_device_capabilities_meet_requirements(
  const D3DCAPS9 *caps)
{
  if ((caps->DeviceType != D3DDEVTYPE_HAL) &&
      (caps->DeviceType != D3DDEVTYPE_SW)  &&
      (caps->DeviceType != D3DDEVTYPE_SW))
    { return false; }

  if (!(caps->Caps2 & D3DCAPS2_DYNAMICTEXTURES))
    return false;

  if (!(caps->DevCaps & D3DDEVCAPS_DRAWPRIMITIVES2) ||
      !(caps->DevCaps & D3DDEVCAPS_DRAWPRIMITIVES2EX) ||
      !(caps->DevCaps & D3DDEVCAPS_DRAWPRIMTLVERTEX))
    { return false; }

  if (!(caps->PrimitiveMiscCaps & D3DPMISCCAPS_CULLCW) ||
      !(caps->PrimitiveMiscCaps & D3DPMISCCAPS_CULLCCW) ||
      !(caps->PrimitiveMiscCaps & D3DPMISCCAPS_BLENDOP) ||
      (caps->PrimitiveMiscCaps & D3DPMISCCAPS_NULLREFERENCE) ||
      !(caps->PrimitiveMiscCaps & D3DPMISCCAPS_SEPARATEALPHABLEND))
    { return false; }

  if (!(caps->PresentationIntervals & D3DPRESENT_INTERVAL_IMMEDIATE) ||
      !(caps->PresentationIntervals & D3DPRESENT_INTERVAL_ONE))
    { return false; }

  if (!(caps->RasterCaps & D3DPRASTERCAPS_ANISOTROPY) ||
      !(caps->RasterCaps & D3DPRASTERCAPS_MIPMAPLODBIAS) ||
      !(caps->RasterCaps & D3DPRASTERCAPS_SCISSORTEST) ||
      !(caps->RasterCaps & D3DPRASTERCAPS_ZTEST))
    { return false; }

  if ((caps->AlphaCmpCaps == D3DPCMPCAPS_ALWAYS) ||
      (caps->AlphaCmpCaps == D3DPCMPCAPS_NEVER))
    { return false; }

  if (!(caps->AlphaCmpCaps & D3DPCMPCAPS_ALWAYS) ||
      !(caps->AlphaCmpCaps & D3DPCMPCAPS_EQUAL) ||
      !(caps->AlphaCmpCaps & D3DPCMPCAPS_GREATER) ||
      !(caps->AlphaCmpCaps & D3DPCMPCAPS_GREATEREQUAL) ||
      !(caps->AlphaCmpCaps & D3DPCMPCAPS_LESS) ||
      !(caps->AlphaCmpCaps & D3DPCMPCAPS_LESSEQUAL) ||
      !(caps->AlphaCmpCaps & D3DPCMPCAPS_NEVER) ||
      !(caps->AlphaCmpCaps & D3DPCMPCAPS_NOTEQUAL))
    { return false; }

  if (!(caps->ZCmpCaps & D3DPCMPCAPS_ALWAYS) ||
      !(caps->ZCmpCaps & D3DPCMPCAPS_EQUAL) ||
      !(caps->ZCmpCaps & D3DPCMPCAPS_GREATER) ||
      !(caps->ZCmpCaps & D3DPCMPCAPS_GREATEREQUAL) ||
      !(caps->ZCmpCaps & D3DPCMPCAPS_LESS) ||
      !(caps->ZCmpCaps & D3DPCMPCAPS_LESSEQUAL) ||
      !(caps->ZCmpCaps & D3DPCMPCAPS_NEVER) ||
      !(caps->ZCmpCaps & D3DPCMPCAPS_NOTEQUAL))
    { return false; }

  if (!(caps->DestBlendCaps & D3DPBLENDCAPS_BLENDFACTOR) ||
      !(caps->DestBlendCaps & D3DPBLENDCAPS_BOTHINVSRCALPHA) ||
      !(caps->DestBlendCaps & D3DPBLENDCAPS_DESTALPHA) ||
      !(caps->DestBlendCaps & D3DPBLENDCAPS_DESTCOLOR) ||
      !(caps->DestBlendCaps & D3DPBLENDCAPS_INVDESTALPHA) ||
      !(caps->DestBlendCaps & D3DPBLENDCAPS_INVDESTCOLOR) ||
      !(caps->DestBlendCaps & D3DPBLENDCAPS_INVSRCALPHA) ||
      !(caps->DestBlendCaps & D3DPBLENDCAPS_INVSRCCOLOR) ||
      !(caps->DestBlendCaps & D3DPBLENDCAPS_ONE) ||
      !(caps->DestBlendCaps & D3DPBLENDCAPS_SRCALPHA) ||
      !(caps->DestBlendCaps & D3DPBLENDCAPS_SRCALPHASAT) ||
      !(caps->DestBlendCaps & D3DPBLENDCAPS_SRCCOLOR) ||
      !(caps->DestBlendCaps & D3DPBLENDCAPS_ZERO))
    { return false; }

  if (!(caps->SrcBlendCaps & D3DPBLENDCAPS_BLENDFACTOR) ||
      !(caps->SrcBlendCaps & D3DPBLENDCAPS_BOTHINVSRCALPHA) ||
      !(caps->SrcBlendCaps & D3DPBLENDCAPS_DESTALPHA) ||
      !(caps->SrcBlendCaps & D3DPBLENDCAPS_DESTCOLOR) ||
      !(caps->SrcBlendCaps & D3DPBLENDCAPS_INVDESTALPHA) ||
      !(caps->SrcBlendCaps & D3DPBLENDCAPS_INVDESTCOLOR) ||
      !(caps->SrcBlendCaps & D3DPBLENDCAPS_INVSRCALPHA) ||
      !(caps->SrcBlendCaps & D3DPBLENDCAPS_INVSRCCOLOR) ||
      !(caps->SrcBlendCaps & D3DPBLENDCAPS_ONE) ||
      !(caps->SrcBlendCaps & D3DPBLENDCAPS_SRCALPHA) ||
      !(caps->SrcBlendCaps & D3DPBLENDCAPS_SRCALPHASAT) ||
      !(caps->SrcBlendCaps & D3DPBLENDCAPS_SRCCOLOR) ||
      !(caps->SrcBlendCaps & D3DPBLENDCAPS_ZERO))
    { return false; }

  if (!(caps->TextureCaps & D3DPTEXTURECAPS_ALPHA) ||
      !(caps->TextureCaps & D3DPTEXTURECAPS_CUBEMAP) ||
      !(caps->TextureCaps & D3DPTEXTURECAPS_MIPMAP) ||
      !(caps->TextureCaps & D3DPTEXTURECAPS_MIPCUBEMAP) ||
      !(caps->TextureCaps & D3DPTEXTURECAPS_MIPVOLUMEMAP) ||
      !(caps->TextureCaps & D3DPTEXTURECAPS_PERSPECTIVE) ||
      !(caps->TextureCaps & D3DPTEXTURECAPS_VOLUMEMAP))
    { return false; }

  if (!(caps->TextureFilterCaps & D3DPTFILTERCAPS_MAGFPOINT) ||
      !(caps->TextureFilterCaps & D3DPTFILTERCAPS_MAGFLINEAR) ||
      !(caps->TextureFilterCaps & D3DPTFILTERCAPS_MAGFANISOTROPIC) ||
      !(caps->TextureFilterCaps & D3DPTFILTERCAPS_MINFPOINT) ||
      !(caps->TextureFilterCaps & D3DPTFILTERCAPS_MINFLINEAR) ||
      !(caps->TextureFilterCaps & D3DPTFILTERCAPS_MINFANISOTROPIC) ||
      !(caps->TextureFilterCaps & D3DPTFILTERCAPS_MIPFPOINT) ||
      !(caps->TextureFilterCaps & D3DPTFILTERCAPS_MIPFLINEAR))
    { return false; }

  if (!(caps->CubeTextureFilterCaps & D3DPTFILTERCAPS_MAGFPOINT) ||
      !(caps->CubeTextureFilterCaps & D3DPTFILTERCAPS_MAGFLINEAR) ||
      !(caps->CubeTextureFilterCaps & D3DPTFILTERCAPS_MINFPOINT) ||
      !(caps->CubeTextureFilterCaps & D3DPTFILTERCAPS_MINFLINEAR) ||
      !(caps->CubeTextureFilterCaps & D3DPTFILTERCAPS_MIPFPOINT) ||
      !(caps->CubeTextureFilterCaps & D3DPTFILTERCAPS_MIPFLINEAR))
    { return false; }

  if (!(caps->VolumeTextureFilterCaps & D3DPTFILTERCAPS_MAGFPOINT) ||
      !(caps->VolumeTextureFilterCaps & D3DPTFILTERCAPS_MAGFLINEAR) ||
      !(caps->VolumeTextureFilterCaps & D3DPTFILTERCAPS_MINFPOINT) ||
      !(caps->VolumeTextureFilterCaps & D3DPTFILTERCAPS_MINFLINEAR) ||
      !(caps->VolumeTextureFilterCaps & D3DPTFILTERCAPS_MIPFPOINT) ||
      !(caps->VolumeTextureFilterCaps & D3DPTFILTERCAPS_MIPFLINEAR))
    { return false; }

  /* if (!(caps->VertexTextureFilterCaps & D3DPTFILTERCAPS_MAGFPOINT) ||
      !(caps->VertexTextureFilterCaps & D3DPTFILTERCAPS_MAGFLINEAR) ||
      !(caps->VertexTextureFilterCaps & D3DPTFILTERCAPS_MINFPOINT) ||
      !(caps->VertexTextureFilterCaps & D3DPTFILTERCAPS_MINFLINEAR) ||
      !(caps->VertexTextureFilterCaps & D3DPTFILTERCAPS_MIPFPOINT) ||
      !(caps->VertexTextureFilterCaps & D3DPTFILTERCAPS_MIPFLINEAR))
    { return false; } */

  if (!(caps->TextureAddressCaps & D3DPTADDRESSCAPS_BORDER) ||
      !(caps->TextureAddressCaps & D3DPTADDRESSCAPS_CLAMP) ||
      !(caps->TextureAddressCaps & D3DPTADDRESSCAPS_INDEPENDENTUV) ||
      !(caps->TextureAddressCaps & D3DPTADDRESSCAPS_MIRROR) ||
      !(caps->TextureAddressCaps & D3DPTADDRESSCAPS_MIRRORONCE) ||
      !(caps->TextureAddressCaps & D3DPTADDRESSCAPS_WRAP))
    { return false; }

  if (!(caps->VolumeTextureAddressCaps & D3DPTADDRESSCAPS_BORDER) ||
      !(caps->VolumeTextureAddressCaps & D3DPTADDRESSCAPS_CLAMP) ||
      !(caps->VolumeTextureAddressCaps & D3DPTADDRESSCAPS_INDEPENDENTUV) ||
      !(caps->VolumeTextureAddressCaps & D3DPTADDRESSCAPS_MIRROR) ||
      !(caps->VolumeTextureAddressCaps & D3DPTADDRESSCAPS_MIRRORONCE) ||
      !(caps->VolumeTextureAddressCaps & D3DPTADDRESSCAPS_WRAP))
    { return false; }

  if (!(caps->LineCaps & D3DLINECAPS_BLEND) ||
      !(caps->LineCaps & D3DLINECAPS_ZTEST))
    { return false; }

  if (!(caps->StencilCaps & D3DSTENCILCAPS_KEEP) ||
      !(caps->StencilCaps & D3DSTENCILCAPS_ZERO) ||
      !(caps->StencilCaps & D3DSTENCILCAPS_REPLACE) ||
      !(caps->StencilCaps & D3DSTENCILCAPS_INCRSAT) ||
      !(caps->StencilCaps & D3DSTENCILCAPS_DECRSAT) ||
      !(caps->StencilCaps & D3DSTENCILCAPS_INVERT) ||
      !(caps->StencilCaps & D3DSTENCILCAPS_INCR) ||
      !(caps->StencilCaps & D3DSTENCILCAPS_DECR) ||
      !(caps->StencilCaps & D3DSTENCILCAPS_TWOSIDED))
    { return false; }

  if (caps->MaxVertexIndex <= 0x0000FFFF)
    return false;

  if (!(caps->DevCaps2 & D3DDEVCAPS2_STREAMOFFSET))
    return false;

  if (!(caps->DeclTypes & D3DDTCAPS_UBYTE4) ||
      !(caps->DeclTypes & D3DDTCAPS_UBYTE4N) ||
      !(caps->DeclTypes & D3DDTCAPS_SHORT2N) ||
      !(caps->DeclTypes & D3DDTCAPS_SHORT4N) ||
      !(caps->DeclTypes & D3DDTCAPS_USHORT2N) ||
      !(caps->DeclTypes & D3DDTCAPS_USHORT4N) ||
      !(caps->DeclTypes & D3DDTCAPS_FLOAT16_2) ||
      !(caps->DeclTypes & D3DDTCAPS_FLOAT16_4))
    { return false; }

  if (caps->VertexShaderVersion < 0x300)
    return false;

  if (caps->PixelShaderVersion < 0x300)
    return false;

  if (caps->NumSimultaneousRTs < 3)
    return false;

  return true;
}

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

agl_context_t *agl_context_alloc_d3d9() {
  return (agl_context_t *)agl_alloc(
    sizeof(agl_context_d3d9_t), agl_alignof(agl_context_d3d9_t));
}

void agl_context_free_d3d9(agl_context_t *context) {
  agl_free((void *)context);
}

/* ========================================================================== */

void agl_context_create_d3d9(
  agl_context_t *context)
{
  agl_context_d3d9_t *context_ = (agl_context_d3d9_t *)context;

  context_->hwnd = CreateWindowEx(
    WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
    "agl", "",
    WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,
    0, 0, 1, 1,
    NULL, NULL,
    GetModuleHandle(NULL), NULL);

  if (!context_->hwnd)
    agl_error(AGL_EUNKNOWN);

  D3DPRESENT_PARAMETERS pp;
  pp.BackBufferWidth = 1;
  pp.BackBufferHeight = 1;
  pp.BackBufferFormat = D3DFMT_UNKNOWN;
  pp.BackBufferCount = 1;
  pp.MultiSampleType = D3DMULTISAMPLE_NONE;
  pp.MultiSampleQuality = 0;
  pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
  pp.hDeviceWindow = context_->hwnd;
  pp.Windowed = TRUE;
  pp.EnableAutoDepthStencil = FALSE;
  pp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
  pp.FullScreen_RefreshRateInHz = 0;
  pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

  /* context_->d3dd9 = */ {
    const HRESULT hr = IDirect3D9_CreateDevice(
      _agl_d3d9,
      (UINT)context->adapter->_internal,
      D3DDEVTYPE_HAL,
      context_->hwnd,
      D3DCREATE_FPU_PRESERVE |
      D3DCREATE_HARDWARE_VERTEXPROCESSING |
      D3DCREATE_MULTITHREADED,
      &pp,
      &context_->d3dd9);
    if (hr != D3D_OK)
      agl_error(AGL_EUNKNOWN);
  }

  IDirect3DSwapChain9 *swap_chain; {
    const HRESULT hr = IDirect3DDevice9_GetSwapChain(
      context_->d3dd9, 0, &swap_chain);
    if (hr != D3D_OK)
      agl_error(AGL_EUNKNOWN);
  }

  IDirect3DSwapChain9_Release(swap_chain);
}

void agl_context_destroy_d3d9(
  agl_context_t *context)
{
  agl_context_d3d9_t *context_ = (agl_context_d3d9_t *)context;
  IDirect3DDevice9_Release(context_->d3dd9);
}

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

agl_swap_chain_t *agl_swap_chain_alloc_d3d9() {
  return (agl_swap_chain_t *)agl_alloc(
    sizeof(agl_swap_chain_d3d9_t), agl_alignof(agl_swap_chain_d3d9_t));
}

void agl_swap_chain_free_d3d9(agl_swap_chain_t *swap_chain) {
  agl_free((void *)swap_chain);
}

/* ========================================================================== */

void agl_swap_chain_create_d3d9(
  agl_swap_chain_t *swap_chain,
  agl_context_t *context)
{
  agl_swap_chain_d3d9_t *swap_chain_ = (agl_swap_chain_d3d9_t *)swap_chain;
  agl_context_d3d9_t *context_ = (agl_context_d3d9_t *)context;

  D3DPRESENT_PARAMETERS pp;

  pp.BackBufferWidth = swap_chain->width;
  pp.BackBufferHeight = swap_chain->height;
  pp.BackBufferFormat = agl_pixel_format_to_d3d(swap_chain->format);
  if (pp.BackBufferFormat == D3DFMT_UNKNOWN)
    agl_error(AGL_EUNKNOWN);
  pp.BackBufferCount = 1;

  pp.MultiSampleType = D3DMULTISAMPLE_NONE;
  pp.MultiSampleQuality = 0;

  pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
  pp.hDeviceWindow = ((HWND)swap_chain->surface);
  pp.Windowed = !!(swap_chain->resource.flags & AGL_SWAP_CHAIN_IS_WINDOWED);

  pp.EnableAutoDepthStencil = FALSE;
  pp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;

  if (swap_chain->resource.flags & AGL_SWAP_CHAIN_IS_FULLSCREEN) {
    agl_display_mode_t dm;
    dm.format = swap_chain->format;
    dm.width = swap_chain->width;
    dm.height = swap_chain->height;
    dm.refresh_rate = 0;
    const agl_display_mode_t *dm_ = agl_output_find_closest_matching_display_mode(
      agl_adapter_primary_output(context->adapter), &dm);
    if (!dm_)
      agl_error(AGL_EUNKNOWN);
    pp.FullScreen_RefreshRateInHz = dm_->refresh_rate;
  } else {
    pp.FullScreen_RefreshRateInHz = 0;
  }

  if (swap_chain->resource.flags & AGL_SWAP_CHAIN_IS_VERTICALLY_SYNCHRONIZED)
    pp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
  else
    pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

  /* swap_chain_->intf = */ {
    const HRESULT hr = IDirect3DDevice9_CreateAdditionalSwapChain(
      context_->d3dd9, &pp, &swap_chain_->intf);
    if (hr != D3D_OK)
      agl_error(AGL_EUNKNOWN);
  }
}

void agl_swap_chain_destroy_d3d9(
  agl_swap_chain_t *swap_chain,
  agl_context_t *context)
{
  agl_swap_chain_d3d9_t *swap_chain_ = (agl_swap_chain_d3d9_t *)swap_chain;
  IDirect3DSwapChain9_Release(swap_chain_->intf);
}

void agl_swap_chain_present_d3d9(
  agl_swap_chain_t *swap_chain,
  agl_context_t *context)
{
  agl_swap_chain_d3d9_t *swap_chain_ = (agl_swap_chain_d3d9_t *)swap_chain;
  IDirect3DSwapChain9_Present(swap_chain_->intf, NULL, NULL, NULL, NULL, 0);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
