//===-- gala/d3d11/output.c -------------------------------------*- C++ -*-===//
//
//  Gala
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//    * Michael Williams <mike@origamicomet.com>
//
//===----------------------------------------------------------------------===//

#include "gala/d3d11/types.h"
#include "gala/d3d11/output.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

void
gala_d3d11_output_destroy(
  gala_d3d11_output_t *output)
{
  gala_assert_debug(output != NULL);
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  output->itf->Release();
#if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
  // This might help find some (stupid) bugs.
  output->itf = (IDXGIOutput *)NULL;
#endif
#endif
  bitbyte_foundation_tier4_allocator_t *heap = bitbyte_foundation_tier4_heap();
  heap->free(heap, (void *)output->display_modes.descs);
#if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
  // This might help find some (stupid) bugs.
  output->display_modes.count = 0;
  output->display_modes.descs = (DXGI_MODE_DESC *)NULL;
#endif
  gala_output_destroy(&output->__output__);
  heap->free(heap, (void *)output);
}

//===----------------------------------------------------------------------===//

size_t
gala_d3d11_output_num_display_modes(
  const gala_d3d11_output_t *output)
{
  gala_assert_debug(output != NULL);
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  return output->display_modes.count;
#endif
}

//===----------------------------------------------------------------------===//

void
gala_d3d11_output_display_mode(
  const gala_d3d11_output_t *output,
  const size_t idx,
  gala_display_mode_t *display_mode)
{
  gala_assert_debug(output != NULL);
  gala_assert_debug(idx < output->display_modes.count);
  gala_assert_debug(display_mode != NULL);
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  display_mode->width = output->display_modes.descs[idx].Width;
  display_mode->height = output->display_modes.descs[idx].Height;
  display_mode->refresh_rate.numer = output->display_modes.descs[idx].RefreshRate.Numerator;
  display_mode->refresh_rate.denom = output->display_modes.descs[idx].RefreshRate.Denominator;
  gala_assert(output->display_modes.descs[idx].Format == DXGI_FORMAT_R8G8B8A8_UNORM);
  display_mode->format = GALA_PIXEL_FORMAT_R8G8B8A8;
#endif
}

//===----------------------------------------------------------------------===//

int gala_d3d11_output_to_s(
  const gala_d3d11_output_t *output,
  char buf[],
  const int buf_sz)
{
  gala_assert_debug(output != NULL);
  return snprintf(buf, buf_sz, "#<gala_d3d11_output_t:%.16" PRIxPTR " IDXGIOutput=%.16" PRIxPTR ">", output, output->itf);
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace gala {

//===----------------------------------------------------------------------===//

void D3D11Output::destroy() {
  ::gala_d3d11_output_destroy((::gala_d3d11_output_t *)&this->__output__);
}

//===----------------------------------------------------------------------===//

size_t D3D11Output::num_display_modes() const {
  return ::gala_d3d11_output_num_display_modes((const ::gala_d3d11_output_t *)&this->__output__);
}

//===----------------------------------------------------------------------===//

void D3D11Output::display_mode(const size_t idx, ::gala::DisplayMode *display_mode) const {
  return ::gala_d3d11_output_display_mode((const ::gala_d3d11_output_t *)&this->__output__,
                                          idx, (::gala_display_mode_t *)&display_mode->__display_mode__);
}

//===----------------------------------------------------------------------===//

int D3D11Output::to_s(char buf[], const int buf_sz) const {
  const ::gala_d3d11_output_t *output = (const ::gala_d3d11_output_t *)this;
  return snprintf(buf, buf_sz, "#<gala::D3D11Output:%.16" PRIxPTR " IDXGIOutput=%.16" PRIxPTR ">", output, output->itf);
}

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
