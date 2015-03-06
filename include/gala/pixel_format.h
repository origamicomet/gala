//===-- gala/pixel_format.h ------------------------------------------*- C++ -*-===//
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

/// \def GALA_PIXEL_FORMAT_COLOR
/// \brief Indicates the pixel format has color channels.
///
#define GALA_PIXEL_FORMAT_COLOR (UINT32_C(1) << UINT32_C(28))

/// \def GALA_PIXEL_FORMAT_DEPTH
/// \brief Indicates the pixel format has a depth channel.
///
#define GALA_PIXEL_FORMAT_DEPTH (UINT32_C(1) << UINT32_C(29))

/// \def GALA_PIXEL_FORMAT_STENCIL
/// \brief Indicates the pixel format has a stencil channel.
///
#define GALA_PIXEL_FORMAT_STENCIL (UINT32_C(1) << UINT32_C(30))

/// \def GALA_PIXEL_FORMAT_COMPRESSED
/// \brief Indicates a compressed pixel format.
///
#define GALA_PIXEL_FORMAT_COMPRESSED (UINT32_C(1) << UINT32_C(31))

//===----------------------------------------------------------------------===//

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

  /// \internal Force at least uint32_t storage and alignment.
  GALA_PIXEL_FORMAT_TYPE_FORCE_UINT32 = 0x7fffffff
} gala_pixel_format_t;

//===----------------------------------------------------------------------===//

/// \brief
/// \param pixel_format
/// \returns
///
extern GALA_PUBLIC const char *
gala_pixel_format_to_s(
  const gala_pixel_format_t pixel_format);

//===----------------------------------------------------------------------===//

/// \brief
/// \param str
/// \returns
///
extern GALA_PUBLIC gala_pixel_format_t
gala_pixel_format_from_s(
  const char *str);

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
  /// \copydoc ::GALA_PIXEL_FORMAT_INVALID
  static const ::gala::PixelFormat kInvalid;
  /// \copydoc ::GALA_PIXEL_FORMAT_R8
  static const ::gala::PixelFormat kR8;
  /// \copydoc ::GALA_PIXEL_FORMAT_R8G8
  static const ::gala::PixelFormat kR8G8;
  /// \copydoc ::GALA_PIXEL_FORMAT_R8G8B8
  static const ::gala::PixelFormat kR8G8B8;
  /// \copydoc ::GALA_PIXEL_FORMAT_R8G8B8A8
  static const ::gala::PixelFormat kR8G8B8A8;

  /// \copydoc ::GALA_PIXEL_FORMAT_R16
  static const ::gala::PixelFormat kR16;
  /// \copydoc ::GALA_PIXEL_FORMAT_R16G16
  static const ::gala::PixelFormat kR16G16;
  /// \copydoc ::GALA_PIXEL_FORMAT_R16G16B16
  static const ::gala::PixelFormat kR16G16B16;
  /// \copydoc ::GALA_PIXEL_FORMAT_R16G16B16A16
  static const ::gala::PixelFormat kR16G16B16A16;

  /// \copydoc ::GALA_PIXEL_FORMAT_R16F
  static const ::gala::PixelFormat kR16F;
  /// \copydoc ::GALA_PIXEL_FORMAT_R16FG16F
  static const ::gala::PixelFormat kR16FG16F;
  /// \copydoc ::GALA_PIXEL_FORMAT_R16FG16FB16F
  static const ::gala::PixelFormat kR16FG16FB16F;
  /// \copydoc ::GALA_PIXEL_FORMAT_R16FG16FB16FA16F
  static const ::gala::PixelFormat kR16FG16FB16FA16F;

  /// \copydoc ::GALA_PIXEL_FORMAT_R32
  static const ::gala::PixelFormat kR32;
  /// \copydoc ::GALA_PIXEL_FORMAT_R32G32
  static const ::gala::PixelFormat kR32G32;
  /// \copydoc ::GALA_PIXEL_FORMAT_R32G32B32
  static const ::gala::PixelFormat kR32G32B32;
  /// \copydoc ::GALA_PIXEL_FORMAT_R32G32B32A32
  static const ::gala::PixelFormat kR32G32B32A32;

  /// \copydoc ::GALA_PIXEL_FORMAT_R32F
  static const ::gala::PixelFormat kR32F;
  /// \copydoc ::GALA_PIXEL_FORMAT_R32FG32F
  static const ::gala::PixelFormat kR32FG32F;
  /// \copydoc ::GALA_PIXEL_FORMAT_R32FG32FB32F
  static const ::gala::PixelFormat kR32FG32FB32F;
  /// \copydoc ::GALA_PIXEL_FORMAT_R32FG32FB32FA32F
  static const ::gala::PixelFormat kR32FG32FB32FA32F;

  /// \copydoc ::GALA_PIXEL_FORMAT_BC1
  static const ::gala::PixelFormat kBC1;
  /// \copydoc ::GALA_PIXEL_FORMAT_BC2
  static const ::gala::PixelFormat kBC2;
  /// \copydoc ::GALA_PIXEL_FORMAT_BC3
  static const ::gala::PixelFormat kBC3;
  /// \copydoc ::GALA_PIXEL_FORMAT_BC4
  static const ::gala::PixelFormat kBC4;
  /// \copydoc ::GALA_PIXEL_FORMAT_BC5
  static const ::gala::PixelFormat kBC5;
  /// \copydoc ::GALA_PIXEL_FORMAT_BC6H
  static const ::gala::PixelFormat kBC6H;
  /// \copydoc ::GALA_PIXEL_FORMAT_BC7
  static const ::gala::PixelFormat kBC7;

  /// \copydoc ::GALA_PIXEL_FORMAT_ATITC
  static const ::gala::PixelFormat kATITC;
  /// \copydoc ::GALA_PIXEL_FORMAT_ETC1
  static const ::gala::PixelFormat kETC1;
  /// \copydoc ::GALA_PIXEL_FORMAT_ETC2
  static const ::gala::PixelFormat kETC2;
  /// \copydoc ::GALA_PIXEL_FORMAT_PVRTC
  static const ::gala::PixelFormat kPVRTC;
  /// \copydoc ::GALA_PIXEL_FORMAT_PVRTC2
  static const ::gala::PixelFormat kPVRTC2;

  /// \copydoc ::GALA_PIXEL_FORMAT_D16
  static const ::gala::PixelFormat kD16;
  /// \copydoc ::GALA_PIXEL_FORMAT_D24X8
  static const ::gala::PixelFormat kD24X8;
  /// \copydoc ::GALA_PIXEL_FORMAT_D24S8
  static const ::gala::PixelFormat kD24S8;
  /// \copydoc ::GALA_PIXEL_FORMAT_D32
  static const ::gala::PixelFormat kD32;

 public:
  PixelFormat();
  inline PixelFormat(const ::gala_pixel_format_t pixel_format) : _Value(pixel_format) {}
  inline PixelFormat(const PixelFormat &pixel_format) : _Value(pixel_format._Value) {}
  PixelFormat &operator=(const PixelFormat &pixel_format);

 public:
  inline bool operator==(const PixelFormat rhs) const { return (_Value == rhs._Value); }
  inline bool operator!=(const PixelFormat rhs) const { return (_Value != rhs._Value); }

 public:
  inline bool is_color() const { return !!(_Value & GALA_PIXEL_FORMAT_COLOR); }
  inline bool is_depth() const { return !!(_Value & GALA_PIXEL_FORMAT_DEPTH); }
  inline bool is_stencil() const { return !!(_Value & GALA_PIXEL_FORMAT_STENCIL); }
  inline bool is_compressed() const { return !!(_Value & GALA_PIXEL_FORMAT_COMPRESSED); }

 public:
  /// \copydoc ::gala_pixel_format_to_s
  inline const char *to_s() const {
    return ::gala_pixel_format_to_s(_Value);
  }

  /// \copydoc ::gala_pixel_format_from_s
  static inline ::gala::PixelFormat from_s(const char *str) {
    return ::gala::PixelFormat(::gala_pixel_format_from_s(str));
  }

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
