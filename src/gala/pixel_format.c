//===-- gala/pixel_format.c -------------------------------------*- C++ -*-===//
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

#include "gala/pixel_format.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

const char *gala_pixel_format_to_s(
  const gala_pixel_format_t pixel_format)
{
  switch (pixel_format) {
    case GALA_PIXEL_FORMAT_UNKNOWN: return "#unknown";
    case GALA_PIXEL_FORMAT_R8: return "R8";
    case GALA_PIXEL_FORMAT_R8G8: return "R8G8";
    case GALA_PIXEL_FORMAT_R8G8B8: return "R8G8B8";
    case GALA_PIXEL_FORMAT_R8G8B8A8: return "R8G8B8A8";
    case GALA_PIXEL_FORMAT_R16F: return "R16F";
    case GALA_PIXEL_FORMAT_R16FG16F: return "R16FG16F";
    case GALA_PIXEL_FORMAT_R16FG16FB16F: return "R16FG16FB16F";
    case GALA_PIXEL_FORMAT_R16FG16FB16FA16F: return "R16FG16FB16FA16F";
    case GALA_PIXEL_FORMAT_R32F: return "R32F";
    case GALA_PIXEL_FORMAT_R32FG32F: return "R32FG32F";
    case GALA_PIXEL_FORMAT_R32FG32FB32F: return "R32FG32FB32F";
    case GALA_PIXEL_FORMAT_R32FG32FB32FA32F: return "R32FG32FB32FA32F";
    case GALA_PIXEL_FORMAT_BC1: return "BC1";
    case GALA_PIXEL_FORMAT_BC2: return "BC2";
    case GALA_PIXEL_FORMAT_BC3: return "BC3";
    case GALA_PIXEL_FORMAT_BC4: return "BC4";
    case GALA_PIXEL_FORMAT_BC5: return "BC5";
    case GALA_PIXEL_FORMAT_BC6H: return "BC6H";
    case GALA_PIXEL_FORMAT_BC7: return "BC7";
    case GALA_PIXEL_FORMAT_ATITC: return "ATITC";
    case GALA_PIXEL_FORMAT_ETC1: return "ETC1";
    case GALA_PIXEL_FORMAT_ETC2: return "ETC2";
    case GALA_PIXEL_FORMAT_PVRTC: return "PVRTC";
    case GALA_PIXEL_FORMAT_PVRTC2: return "PVRTC2";
    case GALA_PIXEL_FORMAT_D24X8: return "D24X8";
    case GALA_PIXEL_FORMAT_D24S8: return "D24S8";
    case GALA_PIXEL_FORMAT_D16: return "D16";
    case GALA_PIXEL_FORMAT_D32F: return "D32F";
  }

  return "#invalid";
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//
