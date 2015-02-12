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
  GALA_PIXEL_FORMAT_BC1 = 13 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_BC2 = 14 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_BC3 = 15 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_BC4 = 16 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_BC5 = 17 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_BC6H = 18 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_BC7 = 20 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,

  /// Compressed format.
  GALA_PIXEL_FORMAT_ATITC = 21 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_ETC1 = 22 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_ETC2 = 23 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_PVRTC = 24 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,
  /// Compressed format.
  GALA_PIXEL_FORMAT_PVRTC2 = 25 | GALA_PIXEL_FORMAT_COLOR | GALA_PIXEL_FORMAT_COMPRESSED,

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

/// \copydoc ::gala_pixel_format_t
class GALA_PUBLIC PixelFormat {
 public:
  /// \copydoc ::GALA_PIXEL_FORMAT_UNKNOWN
  static const PixelFormat kUnknown;

  /// \copydoc ::GALA_PIXEL_FORMAT_R8
  static const PixelFormat kR8;
  /// \copydoc ::GALA_PIXEL_FORMAT_R8G8
  static const PixelFormat kR8G8;
  /// \copydoc ::GALA_PIXEL_FORMAT_R8G8B8
  static const PixelFormat kR8G8B8;
  /// \copydoc ::GALA_PIXEL_FORMAT_R8G8B8A8
  static const PixelFormat kR8G8B8A8;

  /// \copydoc ::GALA_PIXEL_FORMAT_R16F
  static const PixelFormat kR16F;
  /// \copydoc ::GALA_PIXEL_FORMAT_R16FG16F
  static const PixelFormat kR16FG16F;
  /// \copydoc ::GALA_PIXEL_FORMAT_R16FG16FB16F
  static const PixelFormat kR16FG16FB16F;
  /// \copydoc ::GALA_PIXEL_FORMAT_R16FG16FB16FA16F
  static const PixelFormat kR16FG16FB16FA16F;

  /// \copydoc ::GALA_PIXEL_FORMAT_R32F
  static const PixelFormat kR32F;
  /// \copydoc ::GALA_PIXEL_FORMAT_R32FG32F
  static const PixelFormat kR32FG32F;
  /// \copydoc ::GALA_PIXEL_FORMAT_R32FG32FB32F
  static const PixelFormat kR32FG32FB32F;
  /// \copydoc ::GALA_PIXEL_FORMAT_R32FG32FB32FA32F
  static const PixelFormat kR32FG32FB32FA32F;

  /// \copydoc ::GALA_PIXEL_FORMAT_BC1
  static const PixelFormat kBC1;
  /// \copydoc ::GALA_PIXEL_FORMAT_BC2
  static const PixelFormat kBC2;
  /// \copydoc ::GALA_PIXEL_FORMAT_BC3
  static const PixelFormat kBC3;
  /// \copydoc ::GALA_PIXEL_FORMAT_BC4
  static const PixelFormat kBC4;
  /// \copydoc ::GALA_PIXEL_FORMAT_BC5
  static const PixelFormat kBC5;
  /// \copydoc ::GALA_PIXEL_FORMAT_BC6H
  static const PixelFormat kBC6H;
  /// \copydoc ::GALA_PIXEL_FORMAT_BC7
  static const PixelFormat kBC7;

  /// \copydoc ::GALA_PIXEL_FORMAT_ATITC
  static const PixelFormat kATITC;
  /// \copydoc ::GALA_PIXEL_FORMAT_ETC1
  static const PixelFormat kETC1;
  /// \copydoc ::GALA_PIXEL_FORMAT_ETC2
  static const PixelFormat kETC2;
  /// \copydoc ::GALA_PIXEL_FORMAT_PVRTC
  static const PixelFormat kPVRTC;
  /// \copydoc ::GALA_PIXEL_FORMAT_PVRTC2
  static const PixelFormat kPVRTC2;

  /// \copydoc ::GALA_PIXEL_FORMAT_D24X8
  static const PixelFormat kD24X8;
  /// \copydoc ::GALA_PIXEL_FORMAT_D24S8
  static const PixelFormat kD24S8;
  /// \copydoc ::GALA_PIXEL_FORMAT_D16
  static const PixelFormat kD16;
  /// \copydoc ::GALA_PIXEL_FORMAT_D32F
  static const PixelFormat kD32F;

 public:
  PixelFormat();
  inline PixelFormat(const ::gala_pixel_format_t pixel_format) : _Value(pixel_format) {}
  inline PixelFormat(const PixelFormat &pixel_format) : _Value(pixel_format._Value) {}
  PixelFormat &operator=(const PixelFormat &pixel_format);

 public:
  inline bool operator==(const PixelFormat rhs) const { return (_Value == rhs._Value); }
  inline bool operator!=(const PixelFormat rhs) const { return (_Value != rhs._Value); }

 public:
  inline bool is_color() const { return !!(_Value & ::GALA_PIXEL_FORMAT_COLOR); }
  inline bool is_depth() const { return !!(_Value & ::GALA_PIXEL_FORMAT_DEPTH); }
  inline bool is_stencil() const { return !!(_Value & ::GALA_PIXEL_FORMAT_STENCIL); }
  inline bool is_compressed() const { return !!(_Value & ::GALA_PIXEL_FORMAT_COMPRESSED); }

 public:
  /// \copydoc ::gala_pixel_format_to_s
  inline const char *to_s() const { return ::gala_pixel_format_to_s(_Value); }

 private:
  const ::gala_pixel_format_t _Value;
};

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_PIXEL_FORMAT_H_

//============================================================================//
