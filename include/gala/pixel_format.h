//===-- gala/pixel_format.h -------------------------------------*- C++ -*-===//
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
/// \brief TODO(mike): Document this file.
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_PIXEL_FORMAT_H_
#define _GALA_PIXEL_FORMAT_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// Indicates the pixel format has color channels.
static const uint32_t GALA_PIXEL_FORMAT_COLOR = (UINT32_C(1) << UINT32_C(28));
/// Indicates the pixel format has a depth channel.
static const uint32_t GALA_PIXEL_FORMAT_DEPTH = (UINT32_C(1) << UINT32_C(29));
/// Indicates the pixel format has a stencil channel.
static const uint32_t GALA_PIXEL_FORMAT_STENCIL = (UINT32_C(1) << UINT32_C(30));
/// Indicates a compressed pixel format.
static const uint32_t GALA_PIXEL_FORMAT_COMPRESSED = (UINT32_C(1) << UINT32_C(31));

//===----------------------------------------------------------------------===//

/// \brief
///
typedef enum gala_pixel_format {
  /// Unknown.
  GALA_PIXEL_FORMAT_UNKNOWN = 0,

  /// One 8-bit channel.
  GALA_PIXEL_FORMAT_R8 = 1 | GALA_PIXEL_FORMAT_COLOR,
  /// Two 8-bit channels.
  GALA_PIXEL_FORMAT_R8G8 = 2 | GALA_PIXEL_FORMAT_COLOR,
  /// Three 8-bit channels.
  /// \warning May be implemented as GALA_PIXEL_FORMAT_R8G8B8A8.
  GALA_PIXEL_FORMAT_R8G8B8 = 3 | GALA_PIXEL_FORMAT_COLOR,
  /// Four 8-bit channels.
  GALA_PIXEL_FORMAT_R8G8B8A8 = 4 | GALA_PIXEL_FORMAT_COLOR,

  /// One 16-bit floating-point channel.
  GALA_PIXEL_FORMAT_R16F = 5 | GALA_PIXEL_FORMAT_COLOR,
  /// Two 16-bit floating-point channels.
  GALA_PIXEL_FORMAT_R16FG16F = 6 | GALA_PIXEL_FORMAT_COLOR,
  /// Three 16-bit floating-point channels.
  GALA_PIXEL_FORMAT_R16FG16FB16F = 7 | GALA_PIXEL_FORMAT_COLOR,
  /// Four 16-bit floating-point channels.
  GALA_PIXEL_FORMAT_R16FG16FB16FA16F = 8 | GALA_PIXEL_FORMAT_COLOR,

  /// One 32-bit floating-point channel.
  GALA_PIXEL_FORMAT_R32F = 9 | GALA_PIXEL_FORMAT_COLOR,
  /// Two 32-bit floating-point channels.
  GALA_PIXEL_FORMAT_R32FG32F = 10 | GALA_PIXEL_FORMAT_COLOR,
  /// Three 32-bit floating-point channels.
  GALA_PIXEL_FORMAT_R32FG32FB32F = 11 | GALA_PIXEL_FORMAT_COLOR,
  /// Four 32-bit floating-point channels.
  GALA_PIXEL_FORMAT_R32FG32FB32FA32F = 12 | GALA_PIXEL_FORMAT_COLOR,

  /// Compressed format.
  GALA_PIXEL_FORMAT_BC1 = 13 | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_BC2 = 14 | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_BC3 = 15 | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_BC4 = 16 | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_BC5 = 17 | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_BC6H = 18 | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_BC7 = 20 | GALA_PIXEL_FORMAT_COMPRESSED,

  /// Compressed format.
  GALA_PIXEL_FORMAT_ATITC = 21 | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_ETC1 = 22 | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_ETC2 = 23 | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_PVRTC = 24 | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_PVRTC2 = 25 | GALA_PIXEL_FORMAT_COMPRESSED,

  /// 24-bit depth format.
  /// \warning May be implemented as GALA_PIXEL_FORMAT_D24A8.
  GALA_PIXEL_FORMAT_D24X8 = 26 | GALA_PIXEL_FORMAT_DEPTH,
  /// 24-bit depth and 8-bit stencil format.
  GALA_PIXEL_FORMAT_D24S8 = 27 | GALA_PIXEL_FORMAT_DEPTH | GALA_PIXEL_FORMAT_STENCIL,

  /// 16-bit depth format.
  GALA_PIXEL_FORMAT_D16 = 28 | GALA_PIXEL_FORMAT_DEPTH,
  /// 32-bit floating-point depth format.
  GALA_PIXEL_FORMAT_D32F = 29 | GALA_PIXEL_FORMAT_DEPTH,

  /// Force ::gala_pixel_format_t to require a minimum of 4-bytes of storage.
  /// This improves alignment on compilers that aggressively compress enums,
  /// like older versions of MSVC.
  GALA_PIXEL_FORMAT_FORCE_UINT32 = 0x7fffffff
} gala_pixel_format_t;

//===----------------------------------------------------------------------===//

/// \brief
/// \param pixel_format
/// \returns
///
extern
GALA_PUBLIC
const char *gala_pixel_format_to_s(
  const gala_pixel_format_t pixel_format);

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace gala {

//===----------------------------------------------------------------------===//

namespace PixelFormats {
  /// \copydoc ::GALA_PIXEL_FORMAT_COLOR
  static const uint32_t kColor = ::GALA_PIXEL_FORMAT_COLOR;
  /// \copydoc ::GALA_PIXEL_FORMAT_DEPTH
  static const uint32_t kDepth = ::GALA_PIXEL_FORMAT_DEPTH;
  /// \copydoc ::GALA_PIXEL_FORMAT_STENCIL
  static const uint32_t kStencil = ::GALA_PIXEL_FORMAT_STENCIL;
  /// \copydoc ::GALA_PIXEL_FORMAT_COMPRESSED
  static const uint32_t kCompressed = ::GALA_PIXEL_FORMAT_COMPRESSED;

  enum _ {
    /// \copydoc ::GALA_PIXEL_FORMAT_UNKNOWN
    kUnknown = ::GALA_PIXEL_FORMAT_UNKNOWN,

    /// \copydoc ::GALA_PIXEL_FORMAT_R8
    kR8 = ::GALA_PIXEL_FORMAT_R8,
    /// \copydoc ::GALA_PIXEL_FORMAT_R8G8
    kR8G8 = ::GALA_PIXEL_FORMAT_R8G8,
    /// \copydoc ::GALA_PIXEL_FORMAT_R8G8B8
    kR8G8B8 = ::GALA_PIXEL_FORMAT_R8G8B8,
    /// \copydoc ::GALA_PIXEL_FORMAT_R8G8B8A8
    kR8G8B8A8 = ::GALA_PIXEL_FORMAT_R8G8B8A8,

    /// \copydoc ::GALA_PIXEL_FORMAT_R16F
    kR16F = ::GALA_PIXEL_FORMAT_R16F,
    /// \copydoc ::GALA_PIXEL_FORMAT_R16FG16F
    kR16FG16F = ::GALA_PIXEL_FORMAT_R16FG16F,
    /// \copydoc ::GALA_PIXEL_FORMAT_R16FG16FB16F
    kR16FG16FB16F = ::GALA_PIXEL_FORMAT_R16FG16FB16F,
    /// \copydoc ::GALA_PIXEL_FORMAT_R16FG16FB16FA16F
    kR16FG16FB16FA16F = ::GALA_PIXEL_FORMAT_R16FG16FB16FA16F,

    /// \copydoc ::GALA_PIXEL_FORMAT_R32F
    kR32F = ::GALA_PIXEL_FORMAT_R32F,
    /// \copydoc ::GALA_PIXEL_FORMAT_R32FG32F
    kR32FG32F = ::GALA_PIXEL_FORMAT_R32FG32F,
    /// \copydoc ::GALA_PIXEL_FORMAT_R32FG32FB32F
    kR32FG32FB32F = ::GALA_PIXEL_FORMAT_R32FG32FB32F,
    /// \copydoc ::GALA_PIXEL_FORMAT_R32FG32FB32FA32F
    kR32FG32FB32FA32F = ::GALA_PIXEL_FORMAT_R32FG32FB32FA32F,

    /// \copydoc ::GALA_PIXEL_FORMAT_BC1
    kBC1 = ::GALA_PIXEL_FORMAT_BC1,
    /// \copydoc ::GALA_PIXEL_FORMAT_BC2
    kBC2 = ::GALA_PIXEL_FORMAT_BC2,
    /// \copydoc ::GALA_PIXEL_FORMAT_BC3
    kBC3 = ::GALA_PIXEL_FORMAT_BC3,
    /// \copydoc ::GALA_PIXEL_FORMAT_BC4
    kBC4 = ::GALA_PIXEL_FORMAT_BC4,
    /// \copydoc ::GALA_PIXEL_FORMAT_BC5
    kBC5 = ::GALA_PIXEL_FORMAT_BC5,
    /// \copydoc ::GALA_PIXEL_FORMAT_BC6H
    kBC6H = ::GALA_PIXEL_FORMAT_BC6H,
    /// \copydoc ::GALA_PIXEL_FORMAT_BC7
    kBC7 = ::GALA_PIXEL_FORMAT_BC7,

    /// \copydoc ::GALA_PIXEL_FORMAT_ATITC
    kATITC = ::GALA_PIXEL_FORMAT_ATITC,
    /// \copydoc ::GALA_PIXEL_FORMAT_ETC1
    kETC1 = ::GALA_PIXEL_FORMAT_ETC1,
    /// \copydoc ::GALA_PIXEL_FORMAT_ETC2
    kETC2 = ::GALA_PIXEL_FORMAT_ETC2,
    /// \copydoc ::GALA_PIXEL_FORMAT_PVRTC
    kPVRTC = ::GALA_PIXEL_FORMAT_PVRTC,
    /// \copydoc ::GALA_PIXEL_FORMAT_PVRTC2
    kPVRTC2 = ::GALA_PIXEL_FORMAT_PVRTC2,

    /// \copydoc ::GALA_PIXEL_FORMAT_D24X8
    kD24X8 = ::GALA_PIXEL_FORMAT_D24X8,
    /// \copydoc ::GALA_PIXEL_FORMAT_D24S8
    kD24S8 = ::GALA_PIXEL_FORMAT_D24S8,
    /// \copydoc ::GALA_PIXEL_FORMAT_D16
    kD16 = ::GALA_PIXEL_FORMAT_D16,
    /// \copydoc ::GALA_PIXEL_FORMAT_D32F
    kD32F = ::GALA_PIXEL_FORMAT_D32F,

    /// \copydoc ::GALA_PIXEL_FORMAT_FORCE_UINT32
    kForceUInt32 = ::GALA_PIXEL_FORMAT_FORCE_UINT32
  };
}

/// \copydoc ::gala_pixel_format_t
typedef PixelFormats::_ PixelFormat;

//===----------------------------------------------------------------------===//

/// \copydoc ::gala_pixel_format_to_s
static
const char *to_s(
  const ::gala::PixelFormat pixel_format)
{
  return ::gala_pixel_format_to_s((::gala_pixel_format_t)pixel_format);
}

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_PIXEL_FORMAT_H_

//============================================================================//
