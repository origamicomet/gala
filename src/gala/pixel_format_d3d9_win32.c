//===-- gala/pixel_format_d3d9_win32.c --------------------------*- C++ -*-===//
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

#include "gala/pixel_format_d3d9_win32.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

static const struct {
  gala_pixel_format_t gala;
  D3DFORMAT d3d;
} _gala_pixel_format_d3d_format_map[] = {
  { GALA_PIXEL_FORMAT_R8, D3DFMT_UNKNOWN },
  { GALA_PIXEL_FORMAT_R8G8, D3DFMT_UNKNOWN },
  { GALA_PIXEL_FORMAT_R8G8B8, D3DFMT_R8G8B8 },
  { GALA_PIXEL_FORMAT_R8G8B8A8, D3DFMT_A8R8G8B8 },

  { GALA_PIXEL_FORMAT_R16F, D3DFMT_R16F },
  { GALA_PIXEL_FORMAT_R16FG16F, D3DFMT_G16R16F },
  { GALA_PIXEL_FORMAT_R16FG16FB16F, D3DFMT_A16B16G16R16F },
  { GALA_PIXEL_FORMAT_R16FG16FB16FA16F, D3DFMT_A16B16G16R16F },

  { GALA_PIXEL_FORMAT_R32F, D3DFMT_R32F },
  { GALA_PIXEL_FORMAT_R32FG32F, D3DFMT_G32R32F },
  { GALA_PIXEL_FORMAT_R32FG32FB32F, D3DFMT_A32B32G32R32F },
  { GALA_PIXEL_FORMAT_R32FG32FB32FA32F, D3DFMT_A32B32G32R32F },

  { GALA_PIXEL_FORMAT_BC1, D3DFMT_DXT1 },
  { GALA_PIXEL_FORMAT_BC2, D3DFMT_DXT3 },
  { GALA_PIXEL_FORMAT_BC3, D3DFMT_DXT5 },
  { GALA_PIXEL_FORMAT_BC4, (D3DFORMAT)MAKEFOURCC('A', 'T', 'I', '1') },
  { GALA_PIXEL_FORMAT_BC5, (D3DFORMAT)MAKEFOURCC('A', 'T', 'I', '2') },
  { GALA_PIXEL_FORMAT_BC6H, D3DFMT_UNKNOWN },
  { GALA_PIXEL_FORMAT_BC7, D3DFMT_UNKNOWN },

  { GALA_PIXEL_FORMAT_ATITC, D3DFMT_UNKNOWN },
  { GALA_PIXEL_FORMAT_ETC1, D3DFMT_UNKNOWN },
  { GALA_PIXEL_FORMAT_ETC2, D3DFMT_UNKNOWN },
  { GALA_PIXEL_FORMAT_PVRTC, D3DFMT_UNKNOWN },
  { GALA_PIXEL_FORMAT_PVRTC2, D3DFMT_UNKNOWN },

  { GALA_PIXEL_FORMAT_D24X8, D3DFMT_D24X8 },
  { GALA_PIXEL_FORMAT_D24S8, D3DFMT_D24S8 },

  { GALA_PIXEL_FORMAT_D16, D3DFMT_D16 },
  { GALA_PIXEL_FORMAT_D32F, D3DFMT_D32 }
};

static const size_t _gala_pixel_format_d3d_format_map_sz =
  sizeof(_gala_pixel_format_d3d_format_map)/sizeof(_gala_pixel_format_d3d_format_map[0]);

//===----------------------------------------------------------------------===//

D3DFORMAT gala_pixel_format_to_d3d9(
  const gala_pixel_format_t gala)
{
  for (size_t i = 0; i < _gala_pixel_format_d3d_format_map_sz; ++i)
    if (_gala_pixel_format_d3d_format_map[i].gala == gala)
      return _gala_pixel_format_d3d_format_map[i].d3d;
  return D3DFMT_UNKNOWN;
}

//===----------------------------------------------------------------------===//

gala_pixel_format_t gala_pixel_format_from_d3d9(
  const D3DFORMAT d3d)
{
  for (size_t i = 0; i < _gala_pixel_format_d3d_format_map_sz; ++i)
    if (_gala_pixel_format_d3d_format_map[i].d3d == d3d)
      return _gala_pixel_format_d3d_format_map[i].gala;
  return GALA_PIXEL_FORMAT_UNKNOWN;
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//
