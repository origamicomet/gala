//===-- gala/pixel_format.c ------------------------------------------*- C++ -*-===//
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
///
/// \file
/// \brief
///
//===----------------------------------------------------------------------===//

#include "gala/pixel_format.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

const char *
gala_pixel_format_to_s(
  const gala_pixel_format_t pixel_format)
{
  switch (pixel_format) {
    default: return "#unknown";

    case GALA_PIXEL_FORMAT_R8: return "R8";
    case GALA_PIXEL_FORMAT_R8G8: return "R8G8";
    case GALA_PIXEL_FORMAT_R8G8B8: return "R8G8B8";
    case GALA_PIXEL_FORMAT_R8G8B8A8: return "R8G8B8A8";

    case GALA_PIXEL_FORMAT_R16: return "R16";
    case GALA_PIXEL_FORMAT_R16G16: return "R16G16";
    case GALA_PIXEL_FORMAT_R16G16B16: return "R16G16B16";
    case GALA_PIXEL_FORMAT_R16G16B16A16: return "R16G16B16A16";

    case GALA_PIXEL_FORMAT_R16F: return "R16F";
    case GALA_PIXEL_FORMAT_R16FG16F: return "R16FG16F";
    case GALA_PIXEL_FORMAT_R16FG16FB16F: return "R16FG16FB16F";
    case GALA_PIXEL_FORMAT_R16FG16FB16FA16F: return "R16FG16FB16FA16F";

    case GALA_PIXEL_FORMAT_R32: return "R32";
    case GALA_PIXEL_FORMAT_R32G32: return "R32G32";
    case GALA_PIXEL_FORMAT_R32G32B32: return "R32G32B32";
    case GALA_PIXEL_FORMAT_R32G32B32A32: return "R32G32B32A32";

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

    case GALA_PIXEL_FORMAT_D16: return "D16";
    case GALA_PIXEL_FORMAT_D24X8: return "D24X8";
    case GALA_PIXEL_FORMAT_D24S8: return "D24S8";
    case GALA_PIXEL_FORMAT_D32: return "D32";
  }
}

//===----------------------------------------------------------------------===//

gala_pixel_format_t
gala_pixel_format_from_s(
  const char *str)
{
  if (strncmp(str, "R8", strlen("R8")) == 0)
    return GALA_PIXEL_FORMAT_R8;
  if (strncmp(str, "R8G8", strlen("R8G8")) == 0)
    return GALA_PIXEL_FORMAT_R8G8;
  if (strncmp(str, "R8G8B8", strlen("R8G8B8")) == 0)
    return GALA_PIXEL_FORMAT_R8G8B8;
  if (strncmp(str, "R8G8B8A8", strlen("R8G8B8A8")) == 0)
    return GALA_PIXEL_FORMAT_R8G8B8A8;

  if (strncmp(str, "R16", strlen("R16")) == 0)
    return GALA_PIXEL_FORMAT_R16;
  if (strncmp(str, "R16G16", strlen("R16G16")) == 0)
    return GALA_PIXEL_FORMAT_R16G16;
  if (strncmp(str, "R16G16B16", strlen("R16G16B16")) == 0)
    return GALA_PIXEL_FORMAT_R16G16B16;
  if (strncmp(str, "R16G16B16A16", strlen("R16G16B16A16")) == 0)
    return GALA_PIXEL_FORMAT_R16G16B16A16;

  if (strncmp(str, "R16F", strlen("R16F")) == 0)
    return GALA_PIXEL_FORMAT_R16F;
  if (strncmp(str, "R16FG16F", strlen("R16FG16F")) == 0)
    return GALA_PIXEL_FORMAT_R16FG16F;
  if (strncmp(str, "R16FG16FB16F", strlen("R16FG16FB16F")) == 0)
    return GALA_PIXEL_FORMAT_R16FG16FB16F;
  if (strncmp(str, "R16FG16FB16FA16F", strlen("R16FG16FB16FA16F")) == 0)
    return GALA_PIXEL_FORMAT_R16FG16FB16FA16F;

  if (strncmp(str, "R32", strlen("R32")) == 0)
    return GALA_PIXEL_FORMAT_R32;
  if (strncmp(str, "R32G32", strlen("R32G32")) == 0)
    return GALA_PIXEL_FORMAT_R32G32;
  if (strncmp(str, "R32G32B32", strlen("R32G32B32")) == 0)
    return GALA_PIXEL_FORMAT_R32G32B32;
  if (strncmp(str, "R32G32B32A32", strlen("R32G32B32A32")) == 0)
    return GALA_PIXEL_FORMAT_R32G32B32A32;

  if (strncmp(str, "R32F", strlen("R32F")) == 0)
    return GALA_PIXEL_FORMAT_R32F;
  if (strncmp(str, "R32FG32F", strlen("R32FG32F")) == 0)
    return GALA_PIXEL_FORMAT_R32FG32F;
  if (strncmp(str, "R32FG32FB32F", strlen("R32FG32FB32F")) == 0)
    return GALA_PIXEL_FORMAT_R32FG32FB32F;
  if (strncmp(str, "R32FG32FB32FA32F", strlen("R32FG32FB32FA32F")) == 0)
    return GALA_PIXEL_FORMAT_R32FG32FB32FA32F;

  if (strncmp(str, "BC1", strlen("BC1")) == 0)
    return GALA_PIXEL_FORMAT_BC1;
  if (strncmp(str, "BC2", strlen("BC2")) == 0)
    return GALA_PIXEL_FORMAT_BC2;
  if (strncmp(str, "BC3", strlen("BC3")) == 0)
    return GALA_PIXEL_FORMAT_BC3;
  if (strncmp(str, "BC4", strlen("BC4")) == 0)
    return GALA_PIXEL_FORMAT_BC4;
  if (strncmp(str, "BC5", strlen("BC5")) == 0)
    return GALA_PIXEL_FORMAT_BC5;
  if (strncmp(str, "BC6H", strlen("BC6H")) == 0)
    return GALA_PIXEL_FORMAT_BC6H;
  if (strncmp(str, "BC7", strlen("BC7")) == 0)
    return GALA_PIXEL_FORMAT_BC7;

  if (strncmp(str, "ATITC", strlen("ATITC")) == 0)
    return GALA_PIXEL_FORMAT_ATITC;
  if (strncmp(str, "ETC1", strlen("ETC1")) == 0)
    return GALA_PIXEL_FORMAT_ETC1;
  if (strncmp(str, "ETC2", strlen("ETC2")) == 0)
    return GALA_PIXEL_FORMAT_ETC2;
  if (strncmp(str, "PVRTC", strlen("PVRTC")) == 0)
    return GALA_PIXEL_FORMAT_PVRTC;
  if (strncmp(str, "PVRTC2", strlen("PVRTC2")) == 0)
    return GALA_PIXEL_FORMAT_PVRTC2;

  if (strncmp(str, "D16", strlen("D16")) == 0)
    return GALA_PIXEL_FORMAT_D16;
  if (strncmp(str, "D24X8", strlen("D24X8")) == 0)
    return GALA_PIXEL_FORMAT_D24X8;
  if (strncmp(str, "D24S8", strlen("D24S8")) == 0)
    return GALA_PIXEL_FORMAT_D24S8;
  if (strncmp(str, "D32", strlen("D32")) == 0)
    return GALA_PIXEL_FORMAT_D32;

  return GALA_PIXEL_FORMAT_INVALID;
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

const ::gala::PixelFormat PixelFormat::kInvalid = ::GALA_PIXEL_FORMAT_INVALID;
const ::gala::PixelFormat PixelFormat::kR8 = ::GALA_PIXEL_FORMAT_R8;
const ::gala::PixelFormat PixelFormat::kR8G8 = ::GALA_PIXEL_FORMAT_R8G8;
const ::gala::PixelFormat PixelFormat::kR8G8B8 = ::GALA_PIXEL_FORMAT_R8G8B8;
const ::gala::PixelFormat PixelFormat::kR8G8B8A8 = ::GALA_PIXEL_FORMAT_R8G8B8A8;

const ::gala::PixelFormat PixelFormat::kR16 = ::GALA_PIXEL_FORMAT_R16;
const ::gala::PixelFormat PixelFormat::kR16G16 = ::GALA_PIXEL_FORMAT_R16G16;
const ::gala::PixelFormat PixelFormat::kR16G16B16 = ::GALA_PIXEL_FORMAT_R16G16B16;
const ::gala::PixelFormat PixelFormat::kR16G16B16A16 = ::GALA_PIXEL_FORMAT_R16G16B16A16;

const ::gala::PixelFormat PixelFormat::kR16F = ::GALA_PIXEL_FORMAT_R16F;
const ::gala::PixelFormat PixelFormat::kR16FG16F = ::GALA_PIXEL_FORMAT_R16FG16F;
const ::gala::PixelFormat PixelFormat::kR16FG16FB16F = ::GALA_PIXEL_FORMAT_R16FG16FB16F;
const ::gala::PixelFormat PixelFormat::kR16FG16FB16FA16F = ::GALA_PIXEL_FORMAT_R16FG16FB16FA16F;

const ::gala::PixelFormat PixelFormat::kR32 = ::GALA_PIXEL_FORMAT_R32;
const ::gala::PixelFormat PixelFormat::kR32G32 = ::GALA_PIXEL_FORMAT_R32G32;
const ::gala::PixelFormat PixelFormat::kR32G32B32 = ::GALA_PIXEL_FORMAT_R32G32B32;
const ::gala::PixelFormat PixelFormat::kR32G32B32A32 = ::GALA_PIXEL_FORMAT_R32G32B32A32;

const ::gala::PixelFormat PixelFormat::kR32F = ::GALA_PIXEL_FORMAT_R32F;
const ::gala::PixelFormat PixelFormat::kR32FG32F = ::GALA_PIXEL_FORMAT_R32FG32F;
const ::gala::PixelFormat PixelFormat::kR32FG32FB32F = ::GALA_PIXEL_FORMAT_R32FG32FB32F;
const ::gala::PixelFormat PixelFormat::kR32FG32FB32FA32F = ::GALA_PIXEL_FORMAT_R32FG32FB32FA32F;

const ::gala::PixelFormat PixelFormat::kBC1 = ::GALA_PIXEL_FORMAT_BC1;
const ::gala::PixelFormat PixelFormat::kBC2 = ::GALA_PIXEL_FORMAT_BC2;
const ::gala::PixelFormat PixelFormat::kBC3 = ::GALA_PIXEL_FORMAT_BC3;
const ::gala::PixelFormat PixelFormat::kBC4 = ::GALA_PIXEL_FORMAT_BC4;
const ::gala::PixelFormat PixelFormat::kBC5 = ::GALA_PIXEL_FORMAT_BC5;
const ::gala::PixelFormat PixelFormat::kBC6H = ::GALA_PIXEL_FORMAT_BC6H;
const ::gala::PixelFormat PixelFormat::kBC7 = ::GALA_PIXEL_FORMAT_BC7;

const ::gala::PixelFormat PixelFormat::kATITC = ::GALA_PIXEL_FORMAT_ATITC;
const ::gala::PixelFormat PixelFormat::kETC1 = ::GALA_PIXEL_FORMAT_ETC1;
const ::gala::PixelFormat PixelFormat::kETC2 = ::GALA_PIXEL_FORMAT_ETC2;
const ::gala::PixelFormat PixelFormat::kPVRTC = ::GALA_PIXEL_FORMAT_PVRTC;
const ::gala::PixelFormat PixelFormat::kPVRTC2 = ::GALA_PIXEL_FORMAT_PVRTC2;

const ::gala::PixelFormat PixelFormat::kD16 = ::GALA_PIXEL_FORMAT_D16;
const ::gala::PixelFormat PixelFormat::kD24X8 = ::GALA_PIXEL_FORMAT_D24X8;
const ::gala::PixelFormat PixelFormat::kD24S8 = ::GALA_PIXEL_FORMAT_D24S8;
const ::gala::PixelFormat PixelFormat::kD32 = ::GALA_PIXEL_FORMAT_D32;

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
