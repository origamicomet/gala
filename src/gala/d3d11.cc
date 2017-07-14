//===-- gala/d3d11.cc -----------------------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//

#include "gala/d3d11.h"

// TODO(mtwilliams): Improve the structure of this code.
// TODO(mtwilliams): Add paranoid asserts to verify that resources are valid,
// the right type, and have actually been created.

#if GALA_ENABLE_D3D11

#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  #include <InitGuid.h>

  #include <Windows.h>

  #include <DXGI.h>
  #define D3D11_NO_HELPERS
  #include <D3D11.h>

  // Microsoft still hasn't figured out that COM was a Bad Idea.
  #undef interface
#endif

GALA_BEGIN_EXTERN_C

static struct {
#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  IDXGIFactory *dxgi;

  struct {
    HMODULE dxgi;
    HMODULE d3d11;
  } libs;
#endif
} B;

// TODO(mtwilliams): Stop using short variable names like 'B', 'E', and 'R'.

void gala_d3d11_init(void)
{
#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  B.libs.dxgi = ::LoadLibraryA("dxgi.dll");
  gala_assert(B.libs.dxgi != NULL);

  B.libs.d3d11 = ::LoadLibraryA("d3d11.dll");
  gala_assert(B.libs.d3d11 != NULL);

  // TODO(mtwilliams): Use CreateDXGIFactory1 or CreateDXGIFactory2?
  // TODO(mtwilliams): Get debug interfaces with DXGIGetDebugInterface?

  /* B.dxgi = */ {
    typedef HRESULT (WINAPI *CreateDXGIFactory_fn)(REFIID, void **);
    CreateDXGIFactory_fn CreateDXGIFactory_ =
      (CreateDXGIFactory_fn)GetProcAddress(B.libs.dxgi, "CreateDXGIFactory");
    gala_assertf(CreateDXGIFactory_ != NULL, "Unable to initialize Direct3D 11 runtime because CreateDXGIFactory could not be found.");

    const HRESULT hr = CreateDXGIFactory_(__uuidof(IDXGIFactory), (void **)&B.dxgi);
    gala_assertf(hr == S_OK, "Unable to initialize Direct3D 11 runtime because CreateDXGIFactory failed.");
  }
#endif
}

void gala_d3d11_shutdown(void) {
#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  // TODO(mtwilliams): Actually implement this. ;)
#endif
}

typedef struct gala_d3d11_engine {
  gala_engine_t generic;

  ID3D11Device *device;
  ID3D11DeviceContext *immediate_context;

  struct {
    gala_uint32_t num_render_targets;
    ID3D11RenderTargetView *render_targets[8];
    ID3D11DepthStencilView *depth_stencil_target;
  } state;
} gala_d3d11_engine_t;

gala_engine_t *gala_d3d11_create_and_init_engine(
  const gala_engine_creation_params_t *engine_creation_params)
{
  gala_assert_debug(engine_creation_params != NULL);

  gala_d3d11_engine_t *engine = (gala_d3d11_engine_t *)calloc(1, sizeof(gala_d3d11_engine_t));

  engine->generic.meta.backend = GALA_BACKEND_D3D11;
  engine->generic.meta.type = GALA_ENGINE_TYPE_HARDWARE;
  engine->generic.meta.flags = engine_creation_params->flags;

  engine->generic.resource_table = gala_resource_table_create();

  engine->generic.execute = &gala_d3d11_engine_execute;

  typedef HRESULT (WINAPI *D3D11CreateDevice_fn)(IDXGIAdapter *, D3D_DRIVER_TYPE, HMODULE, UINT, const D3D_FEATURE_LEVEL *, UINT, UINT, ID3D11Device **, D3D_FEATURE_LEVEL *, ID3D11DeviceContext **);
  D3D11CreateDevice_fn D3D11CreateDevice_ =
    (D3D11CreateDevice_fn)GetProcAddress(B.libs.d3d11, "D3D11CreateDevice");
  gala_assertf(D3D11CreateDevice_ != NULL, "Unable to initialize Direct3D 11 runtime because D3D11CreateDevice could not be found!");

  UINT flags = 0x00000000ul;
  if (engine_creation_params->flags & GALA_ENGINE_DEBUG)
    flags |= D3D11_CREATE_DEVICE_DEBUG;

  D3D_DRIVER_TYPE driver_type;
  if (engine_creation_params->type == GALA_ENGINE_TYPE_SOFTWARE)
    // TODO(mtwilliams): Use D3D_DRIVER_TYPE_REFERENCE instead?
    driver_type = D3D_DRIVER_TYPE_SOFTWARE;
  else if (engine_creation_params->type == GALA_ENGINE_TYPE_HARDWARE)
    driver_type = D3D_DRIVER_TYPE_HARDWARE;

  // We target Direct3D 10 compatible hardware and up.
  static const D3D_FEATURE_LEVEL acceptable_feature_levels[] = {
    D3D_FEATURE_LEVEL_11_0,
    D3D_FEATURE_LEVEL_10_1,
    D3D_FEATURE_LEVEL_10_0
  };

  // TODO(mtwilliams): Allow creation with a specified adapter.
  const HRESULT hr = D3D11CreateDevice_(
    NULL, driver_type, NULL, flags, acceptable_feature_levels, 3,
    D3D11_SDK_VERSION, &engine->device, NULL, &engine->immediate_context);

  gala_assertf(hr == S_OK, "Unable to initialize Direct3D 11 runtime because D3D11CreateDevice failed!");

  return &engine->generic;
}

void gala_d3d11_destroy_engine(
  gala_engine_t *engine)
{
  gala_assert_debug(engine != NULL);

  // TODO(mtwilliams): Actually implement this. ;)
}

// TODO(mtwilliams): Expose more granular mutability hints?

static void gala_mutability_to_d3d11(const gala_mutability_t mutability,
                                            D3D11_USAGE *usage,
                                            UINT *cpu_access_flags) {
  switch (mutability) {
    case GALA_MUTABILITY_IMMUTABLE:
      *usage = D3D11_USAGE_IMMUTABLE;
      *cpu_access_flags = 0;
      break;
    case GALA_MUTABILITY_MUTABLE:
      *usage = D3D11_USAGE_DEFAULT;
      *cpu_access_flags = 0;
      break;
    case GALA_MUTABILITY_DYNAMIC:
      *usage = D3D11_USAGE_DYNAMIC;
      *cpu_access_flags = D3D11_CPU_ACCESS_WRITE;
      break;
  }

  GALA_TRAP();
}

static UINT gala_bindability_to_d3d11(const gala_uint32_t bindability) {
  UINT flags = 0;

  if (bindability & GALA_BIND_TO_VERTEX_BUFFER)
    flags |= D3D11_BIND_VERTEX_BUFFER;
  if (bindability & GALA_BIND_TO_INDEX_BUFFER)
    flags |= D3D11_BIND_INDEX_BUFFER;
  if (bindability & GALA_BIND_TO_CONSTANT_BUFFER)
    flags |= D3D11_BIND_CONSTANT_BUFFER;

  if (bindability & GALA_BIND_TO_SAMPLER)
    flags |= D3D11_BIND_SHADER_RESOURCE;

  if (bindability & GALA_BIND_TO_RENDER_TARGET)
    flags |= D3D11_BIND_RENDER_TARGET;
  if (bindability & GALA_BIND_TO_DEPTH_STENCIL_TARGET)
    flags |= D3D11_BIND_DEPTH_STENCIL;

  return flags;
}

static DXGI_FORMAT gala_pixel_format_to_dxgi(const gala_pixel_format_t pixel_format) {
  switch (pixel_format) {
    case GALA_PIXEL_FORMAT_R8:
      return DXGI_FORMAT_R8_UNORM;
    case GALA_PIXEL_FORMAT_R8G8:
      return DXGI_FORMAT_R8G8_UNORM;
    case GALA_PIXEL_FORMAT_R8G8B8:
    case GALA_PIXEL_FORMAT_R8G8B8A8:
      return DXGI_FORMAT_R8G8B8A8_UNORM;

    case GALA_PIXEL_FORMAT_R8G8B8_SRGB:
    case GALA_PIXEL_FORMAT_R8G8B8A8_SRGB:
      return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

    case GALA_PIXEL_FORMAT_R16F:
      return DXGI_FORMAT_R16_FLOAT;
    case GALA_PIXEL_FORMAT_R16FG16F:
      return DXGI_FORMAT_R16G16_FLOAT;
    case GALA_PIXEL_FORMAT_R16FG16FB16F:
    case GALA_PIXEL_FORMAT_R16FG16FB16FA16F:
      return DXGI_FORMAT_R16G16B16A16_FLOAT;

    case GALA_PIXEL_FORMAT_R32F:
      return DXGI_FORMAT_R32_FLOAT;
    case GALA_PIXEL_FORMAT_R32FG32F:
      return DXGI_FORMAT_R32G32_FLOAT;
    case GALA_PIXEL_FORMAT_R32FG32FB32F:
      return DXGI_FORMAT_R32G32B32_FLOAT;
    case GALA_PIXEL_FORMAT_R32FG32FB32FA32F:
      return DXGI_FORMAT_R32G32B32A32_FLOAT;

    case GALA_PIXEL_FORMAT_BC1:
      return DXGI_FORMAT_BC1_UNORM;
    case GALA_PIXEL_FORMAT_BC2:
      return DXGI_FORMAT_BC2_UNORM;
    case GALA_PIXEL_FORMAT_BC3:
      return DXGI_FORMAT_BC3_UNORM;
    case GALA_PIXEL_FORMAT_BC4:
      return DXGI_FORMAT_BC4_UNORM;
    case GALA_PIXEL_FORMAT_BC5:
      return DXGI_FORMAT_BC5_UNORM;

    case GALA_PIXEL_FORMAT_D16:
      return DXGI_FORMAT_D16_UNORM;
    case GALA_PIXEL_FORMAT_D24X8:
    case GALA_PIXEL_FORMAT_D24S8:
      return DXGI_FORMAT_D24_UNORM_S8_UINT;
    case GALA_PIXEL_FORMAT_D32:
      return DXGI_FORMAT_D32_FLOAT;
  }

  return DXGI_FORMAT_UNKNOWN;
}

typedef struct gala_d3d11_resource {
  ID3D11Resource *interface;
} gala_d3d11_resource_t;

static void gala_d3d11_fence_on_submission(
  gala_d3d11_engine_t *engine,
  const gala_fence_command_t *cmd)
{
  gala_atomic_store_u64(cmd->fence, cmd->writeback);
}

static void gala_d3d11_fence_on_completion(
  gala_d3d11_engine_t *engine,
  const gala_fence_command_t *cmd)
{
  // HACK(mtwilliams): This isn't asynchronous. There might be another way to
  // achieve this. Perhaps by (ab)using internals?

  ID3D11Query *query;

  D3D11_QUERY_DESC query_desc;
  query_desc.Query = D3D11_QUERY_EVENT;
  query_desc.MiscFlags = 0x00000000ul;

  engine->device->CreateQuery(&query_desc, &query);

  engine->immediate_context->End(query);
  while (engine->immediate_context->GetData(query, NULL, 0, 0) == S_FALSE);

  query->Release();

  gala_atomic_store_u64(cmd->fence, cmd->writeback);
}

typedef struct gala_d3d11_swap_chain {
  IDXGISwapChain *interface;
} gala_d3d11_swap_chain_t;

static void gala_d3d11_swap_chain_create(
  gala_d3d11_engine_t *engine,
  const gala_create_swap_chain_command_t *cmd)
{
  DXGI_SWAP_CHAIN_DESC swap_chain_desc;

  swap_chain_desc.BufferDesc.Width = cmd->desc.width;
  swap_chain_desc.BufferDesc.Height = cmd->desc.height;

  if (cmd->desc.flags & GALA_SWAP_CHAIN_FULLSCREEN) {
    // FIXME(mtwilliams): Create windowed, then upgrade to fullscreen.
    swap_chain_desc.BufferDesc.RefreshRate.Numerator = cmd->desc.refresh_rate.numerator;
    swap_chain_desc.BufferDesc.RefreshRate.Denominator = cmd->desc.refresh_rate.denominator ? cmd->desc.refresh_rate.denominator : 1;
    swap_chain_desc.Windowed = FALSE;
  } else {
    swap_chain_desc.BufferDesc.RefreshRate.Numerator = 0;
    swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
    swap_chain_desc.Windowed = TRUE;
  }

  swap_chain_desc.BufferDesc.Format = gala_pixel_format_to_dxgi(cmd->desc.format);

  swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
  swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;

  // TODO(mtwilliams): Expose multisampling.
  swap_chain_desc.SampleDesc.Count = 1;
  swap_chain_desc.SampleDesc.Quality = 0;

  swap_chain_desc.BufferUsage = DXGI_USAGE_BACK_BUFFER
                              | DXGI_USAGE_RENDER_TARGET_OUTPUT;

  if (cmd->desc.flags & GALA_SWAP_CHAIN_FULLSCREEN)
    // We need to "allocate" the back and front buffers ourselves.
    swap_chain_desc.BufferCount = 2;
  else
    swap_chain_desc.BufferCount = 1;

  // Sanity check that we were actually passed a window handle.
  gala_assert_debug(cmd->desc.surface != NULL);
  gala_assert_debug(IsWindow((HWND)cmd->desc.surface));

  swap_chain_desc.OutputWindow = (HWND)cmd->desc.surface;

  // TODO(mtwilliams): Investigate `DXGI_SWAP_EFFECT_FLIP_DISCARD.`
  // Anything else is stupid.
  swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

  // TODO(mtwilliams): Should we specify DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH?
  swap_chain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

  IDXGISwapChain *swap_chain_interface;
  const HRESULT hr = B.dxgi->CreateSwapChain(engine->device, &swap_chain_desc, &swap_chain_interface);
  gala_assertf(hr == S_OK, "Unable to create swap-chain because IDXGIFactory::CreateSwapChain failed!");

  // HACK(mtwilliams): Wrap without allocating.
  gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table, cmd->swap_chain_handle);
  gala_d3d11_swap_chain_t *swap_chain = (gala_d3d11_swap_chain_t *)&resource->internal;
  swap_chain->interface = swap_chain_interface;
}

static void gala_d3d11_swap_chain_destroy(
  gala_d3d11_engine_t *engine,
  const gala_destroy_swap_chain_command_t *cmd)
{
  gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table, cmd->swap_chain_handle);

  gala_d3d11_swap_chain_t *swap_chain = (gala_d3d11_swap_chain_t *)&resource->internal;
  IDXGISwapChain *swap_chain_interface = swap_chain->interface;

  swap_chain_interface->Release();

  gala_resource_table_free(engine->generic.resource_table, cmd->swap_chain_handle);
}

static void gala_d3d11_resize_swap_chain(
  gala_d3d11_engine_t *engine,
  const gala_resize_swap_chain_command_t *cmd)
{
  gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table, cmd->swap_chain_handle);

  gala_d3d11_swap_chain_t *swap_chain = (gala_d3d11_swap_chain_t *)&resource->internal;
  IDXGISwapChain *swap_chain_interface = swap_chain->interface;

  swap_chain_interface->ResizeBuffers(0, cmd->width, cmd->height, DXGI_FORMAT_UNKNOWN, 0);
}

// TODO(mtwilliams): Expose multisampling.
// TODO(mtwilliams): Expose mipmaps.

typedef struct gala_d3d11_texture {
  ID3D11Resource *interface;
} gala_d3d11_texture_t;

static void gala_d3d11_texture_create_1d(
  gala_d3d11_engine_t *engine,
  const gala_create_texture_command_t *cmd)
{
  gala_assertf(0, "Not implemented yet!");
}

static void gala_d3d11_texture_create_2d(
  gala_d3d11_engine_t *engine,
  const gala_create_texture_command_t *cmd)
{
  D3D11_TEXTURE2D_DESC texture_desc;

  texture_desc.Width  = cmd->desc.width;
  texture_desc.Height = cmd->desc.height;

  texture_desc.MipLevels = 0;

  texture_desc.ArraySize = 1;

  texture_desc.Format = gala_pixel_format_to_dxgi(cmd->desc.format);

  texture_desc.SampleDesc.Count = 1;
  texture_desc.SampleDesc.Quality = 0;

  gala_mutability_to_d3d11(cmd->desc.mutability,
                           &texture_desc.Usage,
                           &texture_desc.CPUAccessFlags);

  texture_desc.BindFlags = gala_bindability_to_d3d11(cmd->desc.bindability);

  texture_desc.MiscFlags = 0;

  const gala_bool_t storage =
    !!(cmd->desc.bindability & GALA_BIND_TO_RENDER_TARGET) ||
    !!(cmd->desc.bindability & GALA_BIND_TO_DEPTH_STENCIL_TARGET);

  const gala_bool_t sampleable =
    !!(cmd->desc.bindability & GALA_BIND_TO_SAMPLER);

  if (storage && sampleable)
    // Will likely want mipmaps.
    texture_desc.MiscFlags |= D3D11_RESOURCE_MISC_GENERATE_MIPS;

  D3D11_SUBRESOURCE_DATA data;

  data.pSysMem = cmd->desc.data;
  data.SysMemPitch = (cmd->desc.width * gala_pixel_format_stride(cmd->desc.format)) / 32;
  data.SysMemSlicePitch = 0;

  ID3D11Texture2D *texture_interface;

  const HRESULT hr = engine->device->CreateTexture2D(
    &texture_desc,
    cmd->desc.data ? &data : NULL,
    &texture_interface);

  gala_assertf(hr == S_OK, "Unable to create texture because ID3D11Device::CreateTexture2D failed!");

  // HACK(mtwilliams): Wrap without allocating.
  gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table, cmd->texture_handle);
  gala_d3d11_texture_t *texture = (gala_d3d11_texture_t *)&resource->internal;
  texture->interface = texture_interface;
}

static void gala_d3d11_texture_create_3d(
  gala_d3d11_engine_t *engine,
  const gala_create_texture_command_t *cmd)
{
  gala_assertf(0, "Not implemented yet!");
}

static void gala_d3d11_create_texture(
  gala_d3d11_engine_t *engine,
  const gala_create_texture_command_t *cmd)
{
  if (cmd->desc.dimensionality == GALA_ONE_DIMENSIONAL)
    gala_d3d11_texture_create_1d(engine, cmd);
  else if (cmd->desc.dimensionality == GALA_TWO_DIMENSIONAL)
    gala_d3d11_texture_create_2d(engine, cmd);
  else if (cmd->desc.dimensionality == GALA_THREE_DIMENSIONAL)
    gala_d3d11_texture_create_3d(engine, cmd);
}

static void gala_d3d11_destroy_texture(
  gala_d3d11_engine_t *engine,
  const gala_destroy_texture_command_t *cmd)
{
  gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table, cmd->texture_handle);

  gala_d3d11_texture_t *texture = (gala_d3d11_texture_t *)&resource->internal;

  ID3D11Resource *texture_interface = texture->interface;
  texture_interface->Release();

  gala_resource_table_free(engine->generic.resource_table, cmd->texture_handle);
}

typedef struct gala_d3d11_render_target_view {
  ID3D11RenderTargetView *interface;
} gala_d3d11_render_target_view_t;

// TODO(mtwilliams): Allow rendering into specific slices.

static void gala_d3d11_render_target_view_create(
  gala_d3d11_engine_t *engine,
  const gala_create_render_target_view_command_t *cmd)
{
  D3D11_RENDER_TARGET_VIEW_DESC render_target_view_desc;

  render_target_view_desc.Format = gala_pixel_format_to_dxgi(cmd->desc.format);

  if (cmd->desc.dimensionality == GALA_ONE_DIMENSIONAL)
    render_target_view_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE1D;
  else if (cmd->desc.dimensionality == GALA_TWO_DIMENSIONAL)
    render_target_view_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

  render_target_view_desc.Texture3D.MipSlice = 0;
  render_target_view_desc.Texture3D.FirstWSlice = 0;
  render_target_view_desc.Texture3D.WSize = -1;

  gala_resource_t *storage = gala_resource_table_lookup(engine->generic.resource_table, cmd->desc.storage);

  const gala_bool_t backed_by_swap_chain = (storage->type == GALA_RESOURCE_TYPE_SWAP_CHAIN);
  const gala_bool_t backed_by_texture = !!(storage->type & GALA_RESOURCE_TYPE_TEXTURE);

  gala_assert_debug(backed_by_swap_chain || backed_by_texture);

  ID3D11Resource *storage_interface = NULL;
  if (backed_by_swap_chain) {
    // Grab back buffer.
    gala_d3d11_swap_chain_t *swap_chain = (gala_d3d11_swap_chain_t *)&storage->internal;
    IDXGISwapChain *swap_chain_interface = swap_chain->interface;
    swap_chain_interface->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&storage_interface);
  } else if (backed_by_texture) {
    storage_interface = ((gala_d3d11_resource_t *)&storage->internal)->interface;
  }

  ID3D11RenderTargetView *render_target_view_interface;
  const HRESULT hr = engine->device->CreateRenderTargetView(
    storage_interface,
    &render_target_view_desc,
    &render_target_view_interface);

  gala_assertf(hr == S_OK, "Unable to create render target view because ID3D11Device::CreateRenderTargetView failed!");

  if (backed_by_swap_chain)
    // The returned interface should only be used temporarily.
    storage_interface->Release();

  // HACK(mtwilliams): Wrap without allocating.
  gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table, cmd->render_target_view_handle);
  gala_d3d11_render_target_view_t *render_target_view = (gala_d3d11_render_target_view_t *)&resource->internal;
  render_target_view->interface = render_target_view_interface;
}

static void gala_d3d11_render_target_view_destroy(
  gala_d3d11_engine_t *engine,
  const gala_destroy_render_target_view_command_t *cmd)
{
  gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table, cmd->render_target_view_handle);

  gala_d3d11_render_target_view_t *render_target_view = (gala_d3d11_render_target_view_t *)&resource->internal;

  ID3D11RenderTargetView *render_target_view_interface = render_target_view->interface;
  render_target_view_interface->Release();

  gala_resource_table_free(engine->generic.resource_table, cmd->render_target_view_handle);
}

typedef struct gala_d3d11_depth_stencil_target_view {
  ID3D11DepthStencilView *interface;
} gala_d3d11_depth_stencil_target_view_t;

static void gala_d3d11_set_render_and_depth_stencil_targets(
  gala_d3d11_engine_t *engine,
  const gala_set_render_and_depth_stencil_targets_command_t *cmd)
{
  ID3D11RenderTargetView *render_targets[8];

  for (gala_uint32_t render_target = 0; render_target < cmd->num_render_target_views; ++render_target) {
    gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table, cmd->render_target_view_handles[render_target]);
    render_targets[render_target] = ((gala_d3d11_render_target_view_t *)&resource->internal)->interface;
  }

  ID3D11DepthStencilView *depth_stencil_target = NULL;

  if (cmd->depth_stencil_target_view_handle != GALA_INVALID_DEPTH_STENCIL_TARGET_VIEW_HANDLE) {
    gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table, cmd->depth_stencil_target_view_handle);
    depth_stencil_target = ((gala_d3d11_depth_stencil_target_view_t *)&resource->internal)->interface;
  }

  const gala_bool_t bind_render_targets = (cmd->num_render_target_views > 0);
  const gala_bool_t bind_depth_stencil_target = !!(depth_stencil_target);

  engine->immediate_context->OMSetRenderTargets(
    cmd->num_render_target_views,
    bind_render_targets ? render_targets : NULL,
    bind_depth_stencil_target ? depth_stencil_target : NULL);

  engine->state.num_render_targets = cmd->num_render_target_views;
  memcpy((void *)&engine->state.render_targets[0], (void *)&render_targets[0], sizeof(render_targets));
  engine->state.depth_stencil_target = depth_stencil_target;
}

static void gala_d3d11_clear_render_targets(
  gala_d3d11_engine_t *engine,
  const gala_clear_render_targets_command_t *cmd)
{
  for (gala_uint32_t rt = 0; rt < engine->state.num_render_targets; ++rt)
    engine->immediate_context->ClearRenderTargetView(engine->state.render_targets[rt], &cmd->rgba[0]);
}

static void gala_d3d11_clear_depth_stencil_target(
  gala_d3d11_engine_t *engine,
  const gala_clear_depth_stencil_target_command_t *cmd)
{
  const UINT clear_flags = (cmd->channels.depth ? D3D11_CLEAR_DEPTH : 0) |
                           (cmd->channels.stencil ? D3D11_CLEAR_STENCIL : 0);

  engine->immediate_context->ClearDepthStencilView(engine->state.depth_stencil_target, clear_flags, cmd->depth, cmd->stencil);
}

static void gala_d3d11_present(
  gala_d3d11_engine_t *engine,
  const gala_present_command_t *cmd)
{
  gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table, cmd->swap_chain_handle);

  gala_d3d11_swap_chain_t *swap_chain = (gala_d3d11_swap_chain_t *)&resource->internal;
  IDXGISwapChain *swap_chain_interface = swap_chain->interface;

  // TODO(mtwilliams): Expose vertical synchronization flag.
  // TODO(mtwilliams): Expose DXGI_PRESENT_DO_NOT_WAIT?
  swap_chain_interface->Present(0, 0);
}

static void gala_d3d11_engine_dispatch(
  gala_d3d11_engine_t *engine,
  const gala_command_t *cmd)
{
  switch (cmd->header.type) {
    case GALA_COMMAND_TYPE_NOP:
      // Do absolutely nothing.
      return;

    case GALA_COMMAND_TYPE_FENCE_ON_SUBMISSION:
      return gala_d3d11_fence_on_submission(engine, (gala_fence_command_t *)cmd);

    case GALA_COMMAND_TYPE_FENCE_ON_COMPLETION:
      return gala_d3d11_fence_on_completion(engine, (gala_fence_command_t *)cmd);

    case GALA_COMMAND_TYPE_CREATE_SWAP_CHAIN:
      return gala_d3d11_swap_chain_create(engine, (gala_create_swap_chain_command_t *)cmd);

    case GALA_COMMAND_TYPE_DESTROY_SWAP_CHAIN:
      return gala_d3d11_swap_chain_destroy(engine, (gala_destroy_swap_chain_command_t *)cmd);

    case GALA_COMMAND_TYPE_RESIZE_SWAP_CHAIN:
      return gala_d3d11_resize_swap_chain(engine, (gala_resize_swap_chain_command_t *)cmd);

    case GALA_COMMAND_TYPE_CREATE_RENDER_TARGET_VIEW:
      return gala_d3d11_render_target_view_create(engine, (gala_create_render_target_view_command_t *)cmd);

    case GALA_COMMAND_TYPE_DESTROY_RENDER_TARGET_VIEW:
      return gala_d3d11_render_target_view_destroy(engine, (gala_destroy_render_target_view_command_t *)cmd);

    case GALA_COMMAND_TYPE_CREATE_DEPTH_STENCIL_TARGET_VIEW:
    case GALA_COMMAND_TYPE_DESTROY_DEPTH_STENCIL_TARGET_VIEW:
      // Implement.
      return;

    case GALA_COMMAND_TYPE_SET_RENDER_AND_DEPTH_STENCIL_TARGETS:
      return gala_d3d11_set_render_and_depth_stencil_targets(engine, (gala_set_render_and_depth_stencil_targets_command_t *)cmd);

    case GALA_COMMAND_TYPE_CLEAR_RENDER_TARGETS:
      return gala_d3d11_clear_render_targets(engine, (gala_clear_render_targets_command_t *)cmd);

    case GALA_COMMAND_TYPE_CLEAR_DEPTH_STENCIL_TARGET:
      return gala_d3d11_clear_depth_stencil_target(engine, (gala_clear_depth_stencil_target_command_t *)cmd);

    case GALA_COMMAND_TYPE_PRESENT:
      return gala_d3d11_present(engine, (gala_present_command_t *)cmd);
  }
}

void gala_d3d11_engine_execute(
  gala_engine_t *engine,
  const gala_command_buffer_t *commands)
{
  gala_assert_debug(engine != NULL);
  gala_assert_debug(commands != NULL);

  gala_assert_debug(engine->meta.backend == GALA_BACKEND_D3D11);

  gala_uintptr_t current = commands->start;
  const gala_uintptr_t last = commands->current;

  while (current < last) {
    const gala_command_t *command = (gala_command_t *)current;
    gala_d3d11_engine_dispatch((gala_d3d11_engine_t *)engine, command);
    current += command->header.size;
  }
}

GALA_END_EXTERN_C

#endif // GALA_ENABLE_D3D11
