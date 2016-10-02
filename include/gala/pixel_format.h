//===-- gala/pixel_format.h -----------------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_PIXEL_FORMAT_H_
#define _GALA_PIXEL_FORMAT_H_

#include "gala/foundation.h"

GALA_BEGIN_EXTERN_C

/// \def GALA_PIXEL_FORMAT_COLOR
/// \brief The pixel format has color channels.
///
#define GALA_PIXEL_FORMAT_COLOR (1 << 28)

/// \def GALA_PIXEL_FORMAT_DEPTH
/// \brief The pixel format has a depth channel.
///
#define GALA_PIXEL_FORMAT_DEPTH (1 << 29)

/// \def GALA_PIXEL_FORMAT_STENCIL
/// \brief The pixel format has a stencil channel.
///
#define GALA_PIXEL_FORMAT_STENCIL (1 << 30)

/// \def GALA_PIXEL_FORMAT_COMPRESSED
/// \brief A compressed pixel format.
///
#define GALA_PIXEL_FORMAT_COMPRESSED (1 << 31)

/// \brief
///
typedef enum gala_pixel_format {
  /// Invalid.
  GALA_PIXEL_FORMAT_INVALID = 0,

  /// One 8-bit color channel.
  GALA_PIXEL_FORMAT_R8 = 1 | GALA_PIXEL_FORMAT_COLOR,
  /// Two 8-bit color channels.
  GALA_PIXEL_FORMAT_R8G8 = 2 | GALA_PIXEL_FORMAT_COLOR,
  /// Three 8-bit color channels.
  /// \warning May be implemented as GALA_PIXEL_FORMAT_R8G8B8A8.
  GALA_PIXEL_FORMAT_R8G8B8 = 3 | GALA_PIXEL_FORMAT_COLOR,
  /// Three 8-bit color channels and an 8-bit alpha channel.
  GALA_PIXEL_FORMAT_R8G8B8A8 = 4 | GALA_PIXEL_FORMAT_COLOR,

  /// One 16-bit color channel.
  GALA_PIXEL_FORMAT_R16 = 5 | GALA_PIXEL_FORMAT_COLOR,
  /// Two 16-bit color channels.
  GALA_PIXEL_FORMAT_R16G16 = 6 | GALA_PIXEL_FORMAT_COLOR,
  /// Three 16-bit color channels.
  /// \warning May be implemented as GALA_PIXEL_FORMAT_R16G16B16A16.
  GALA_PIXEL_FORMAT_R16G16B16 = 7 | GALA_PIXEL_FORMAT_COLOR,
  /// Three 16-bit color channels and a 16-bit alpha channel.
  GALA_PIXEL_FORMAT_R16G16B16A16 = 8 | GALA_PIXEL_FORMAT_COLOR,

  /// One 16-bit floating-point color channel.
  GALA_PIXEL_FORMAT_R16F = 9 | GALA_PIXEL_FORMAT_COLOR,
  /// Two 16-bit floating-point color channels.
  GALA_PIXEL_FORMAT_R16FG16F = 10 | GALA_PIXEL_FORMAT_COLOR,
  /// Three 16-bit floating-point color channels.
  /// \warning May be implemented as GALA_PIXEL_FORMAT_R16FG16FB16FA16F.
  GALA_PIXEL_FORMAT_R16FG16FB16F = 11 | GALA_PIXEL_FORMAT_COLOR,
  /// Three 16-bit floating-point color channels and a 16-bit floating-point alpha channel.
  GALA_PIXEL_FORMAT_R16FG16FB16FA16F = 12 | GALA_PIXEL_FORMAT_COLOR,

  /// One 32-bit color channel.
  GALA_PIXEL_FORMAT_R32 = 13 | GALA_PIXEL_FORMAT_COLOR,
  /// Two 32-bit color channels.
  GALA_PIXEL_FORMAT_R32G32 = 14 | GALA_PIXEL_FORMAT_COLOR,
  /// Three 32-bit color channels.
  /// \warning May be implemented as GALA_PIXEL_FORMAT_R32G32B32A32.
  GALA_PIXEL_FORMAT_R32G32B32 = 15 | GALA_PIXEL_FORMAT_COLOR,
  /// Three 32-bit color channels and a 32-bit alpha channel.
  GALA_PIXEL_FORMAT_R32G32B32A32 = 16 | GALA_PIXEL_FORMAT_COLOR,

  /// One 32-bit floating-point color channel.
  GALA_PIXEL_FORMAT_R32F = 17 | GALA_PIXEL_FORMAT_COLOR,
  /// Two 32-bit floating-point color channels.
  GALA_PIXEL_FORMAT_R32FG32F = 18 | GALA_PIXEL_FORMAT_COLOR,
  /// Three 32-bit floating-point color channels.
  GALA_PIXEL_FORMAT_R32FG32FB32F = 19 | GALA_PIXEL_FORMAT_COLOR,
  /// Three 32-bit floating-point color channels and a 32-bit floating-point alpha channel.
  GALA_PIXEL_FORMAT_R32FG32FB32FA32F = 20 | GALA_PIXEL_FORMAT_COLOR,

  /// Compressed format.
  GALA_PIXEL_FORMAT_BC1 = 21 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_BC2 = 22 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_BC3 = 23 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_BC4 = 24 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_BC5 = 25 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_BC6H = 26 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_BC7 = 27 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,

  /// Compressed format.
  GALA_PIXEL_FORMAT_ATITC = 28 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_ETC1 = 29 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_ETC2 = 30 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_PVRTC = 31 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_PVRTC2 = 32 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,

  /// 16-bit depth.
  GALA_PIXEL_FORMAT_D16 = 33 | GALA_PIXEL_FORMAT_DEPTH,
  /// 24-bit depth.
  /// \warning May be implemented as GALA_PIXEL_FORMAT_D24S8.
  GALA_PIXEL_FORMAT_D24X8 = 34 | GALA_PIXEL_FORMAT_DEPTH,
  /// 24-bit depth with 8-bit stencil.
  GALA_PIXEL_FORMAT_D24S8 = 35 | GALA_PIXEL_FORMAT_DEPTH | GALA_PIXEL_FORMAT_STENCIL,
  /// 32-bit depth.
  GALA_PIXEL_FORMAT_D32 = 36 | GALA_PIXEL_FORMAT_DEPTH,

  /// \internal Force gala_uint32_t storage and alignment.
  GALA_PIXEL_FORMAT_TYPE_FORCE_UINT32 = 0x7fffffff
} gala_pixel_format_t;

GALA_END_EXTERN_C

#endif // _GALA_PIXEL_FORMAT_H_
