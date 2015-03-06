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
  gala_output_destroy(&output->__output__);
  bitbyte_foundation_tier4_allocator_t *heap = bitbyte_foundation_tier4_heap();
  heap->free(heap, (void *)output);
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

int D3D11Output::to_s(char buf[], const int buf_sz) const {
  const ::gala_d3d11_output_t *output = (const ::gala_d3d11_output_t *)this;
  return snprintf(buf, buf_sz, "#<gala::D3D11Output:%.16" PRIxPTR " IDXGIOutput=%.16" PRIxPTR ">", output, output->itf);
}

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
