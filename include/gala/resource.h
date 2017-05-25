//===-- gala/resource.h  --------------------------------*- mode: C++11 -*-===//
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

#ifndef _GALA_RESOURCE_H_
#define _GALA_RESOURCE_H_

#include "gala/foundation.h"

GALA_BEGIN_EXTERN_C

typedef enum gala_resource_type {
  /// Unknown or invalid.
  GALA_RESOURCE_TYPE_UNKNOWN = 0,

  /// A swap-chain.
  GALA_RESOURCE_TYPE_SWAP_CHAIN = 0x000 | 1,

  /// A texture.
  GALA_RESOURCE_TYPE_TEXTURE = 0x100,

  /// A one-dimensional texture.
  GALA_RESOURCE_TYPE_TEXTURE_1D = GALA_RESOURCE_TYPE_TEXTURE | 1,

  /// A two-dimensional texture.
  GALA_RESOURCE_TYPE_TEXTURE_2D = GALA_RESOURCE_TYPE_TEXTURE | 2,

  /// A three-dimensional texture.
  GALA_RESOURCE_TYPE_TEXTURE_3D = GALA_RESOURCE_TYPE_TEXTURE | 3,

  /// A buffer.
  GALA_RESOURCE_TYPE_BUFFER = 0x200,

  /// A vertex buffer.
  GALA_RESOURCE_TYPE_VERTEX_BUFFER = GALA_RESOURCE_TYPE_BUFFER | 1,

  /// An index Buffer.
  GALA_RESOURCE_TYPE_INDEX_BUFFER = GALA_RESOURCE_TYPE_BUFFER | 1,

  /// A constant Buffer.
  GALA_RESOURCE_TYPE_CONSTANT_BUFFER = GALA_RESOURCE_TYPE_BUFFER | 1,

  /// A resource view.
  GALA_RESOURCE_TYPE_VIEW = 0x400,

  /// A render-target view.
  GALA_RESOURCE_TYPE_RENDER_TARGET_VIEW = GALA_RESOURCE_TYPE_VIEW | 1,

  /// A depth-stencil-target view.
  GALA_RESOURCE_TYPE_DEPTH_STENCIL_TARGET_VIEW = GALA_RESOURCE_TYPE_VIEW | 2,

  /// A texture sampler.
  GALA_RESOURCE_TYPE_SAMPLER = GALA_RESOURCE_TYPE_VIEW | 3,

  /// A shader.
  GALA_RESOURCE_TYPE_SHADER = 0x800,

  /// A vertex shader.
  GALA_RESOURCE_TYPE_VERTEX_SHADER = GALA_RESOURCE_TYPE_SHADER | 1,

  /// A pixel shader.
  GALA_RESOURCE_TYPE_PIXEL_SHADER  = GALA_RESOURCE_TYPE_SHADER | 2,

  /// \internal Force gala_uint32_t storage and alignment.
  GALA_RESOURCE_TYPE_FORCE_UINT32 = 0x7fffffff
} gala_resource_type_t;

typedef uint32_t gala_resource_handle_t;

/// \def GALA_INVALID_RESOURCE_HANDLE
/// \brief An invalid resource handle.
#define GALA_INVALID_RESOURCE_HANDLE \
  (~(gala_resource_handle_t)0)

typedef struct gala_resource {
  gala_uint16_t type;
  gala_uint16_t meta;
  uintptr_t internal;
} gala_resource_t;

typedef enum gala_dimensionality {
  /// One dimensional.
  GALA_ONE_DIMENSIONAL = 1,
  /// Two dimensional.
  GALA_TWO_DIMENSIONAL = 2,
  /// Three dimensional.
  GALA_THREE_DIMENSIONAL = 3,
  /// \internal Force gala_uint32_t storage and alignment.
  GALA_DIMENSIONALITY_TYPE_FORCE_UINT32 = 0x7fffffff
} gala_dimensionality_t;

typedef enum gala_mutability {
  /// Readable by the GPU.
  /// \note Initialized upon creation and cannot be modified after.
  GALA_MUTABILITY_IMMUTABLE = 0,
  /// Readable from and writeable to by the GPU.
  GALA_MUTABILITY_MUTABLE = 1,
  /// Written to by CPU and read from by the GPU.
  /// \note Ideal for a resource that is updated each frame.
  GALA_MUTABILITY_DYNAMIC = 2,
  /// \internal Force gala_uint32_t storage and alignment.
  GALA_MUTABILITY_TYPE_FORCE_UINT32 = 0x7fffffff
} gala_mutability_t;

typedef enum gala_bindability {
  /// Can be bound as a vertex buffer.
  GALA_BIND_TO_VERTEX_BUFFER = (1 << 0),
  /// Can be bound as an index buffer.
  GALA_BIND_TO_INDEX_BUFFER = (1 << 1),
  /// Can be bound as a constant buffer.
  GALA_BIND_TO_CONSTANT_BUFFER = (1 << 2),
  /// Can be bound as a sampler.
  GALA_BIND_TO_SAMPLER = (1 << 3),
  /// Can be bound as a render-target.
  GALA_BIND_TO_RENDER_TARGET = (1 << 4),
  /// Can be bound as a depth-stencil-target.
  GALA_BIND_TO_DEPTH_STENCIL_TARGET = (1 << 5),
  /// \internal Force gala_uint32_t storage and alignment.
  GALA_BINDABILITY_TYPE_FORCE_UINT32 = 0x7fffffff
} gala_bindability_t;

GALA_END_EXTERN_C

#ifdef __cplusplus
namespace gala {

/// \copydoc ::gala_resource_t
struct GALA_PUBLIC Resource : public ::gala_resource_t {
 public:
  /// \copydoc ::gala_resource_type_t
  typedef ::gala_resource_type_t Type;

  /// \copydoc GALA_RESOURCE_TYPE_UNKNOWN
  static const Type UNKNOWN = ::GALA_RESOURCE_TYPE_UNKNOWN;

  /// \copydoc GALA_RESOURCE_TYPE_SWAP_CHAIN
  static const Type SWAP_CHAIN = ::GALA_RESOURCE_TYPE_SWAP_CHAIN;

  /// \copydoc GALA_RESOURCE_TYPE_BUFFER
  static const Type BUFFER = ::GALA_RESOURCE_TYPE_BUFFER;

  /// \copydoc GALA_RESOURCE_TYPE_VERTEX_BUFFER
  static const Type VERTEX_BUFFER = ::GALA_RESOURCE_TYPE_VERTEX_BUFFER;

  /// \copydoc GALA_RESOURCE_TYPE_INDEX_BUFFER
  static const Type INDEX_BUFFER = ::GALA_RESOURCE_TYPE_INDEX_BUFFER;

  /// \copydoc GALA_RESOURCE_TYPE_CONSTANT_BUFFER
  static const Type CONSTANT_BUFFER = ::GALA_RESOURCE_TYPE_CONSTANT_BUFFER;

  /// \copydoc GALA_RESOURCE_TYPE_TEXTURE
  static const Type TEXTURE = ::GALA_RESOURCE_TYPE_TEXTURE;

  /// \copydoc GALA_RESOURCE_TYPE_TEXTURE_1D
  static const Type TEXTURE_1D = ::GALA_RESOURCE_TYPE_TEXTURE_1D;

  /// \copydoc GALA_RESOURCE_TYPE_TEXTURE_2D
  static const Type TEXTURE_2D = ::GALA_RESOURCE_TYPE_TEXTURE_2D;

  /// \copydoc GALA_RESOURCE_TYPE_TEXTURE_3D
  static const Type TEXTURE_3D = ::GALA_RESOURCE_TYPE_TEXTURE_3D;

  /// \copydoc GALA_RESOURCE_TYPE_VIEW
  static const Type VIEW = ::GALA_RESOURCE_TYPE_VIEW;

  /// \copydoc GALA_RESOURCE_TYPE_RENDER_TARGET_VIEW
  static const Type RENDER_TARGET_VIEW = ::GALA_RESOURCE_TYPE_RENDER_TARGET_VIEW;

  /// \copydoc GALA_RESOURCE_TYPE_DEPTH_STENCIL_TARGET_VIEW
  static const Type DEPTH_STENCIL_TARGET_VIEW = ::GALA_RESOURCE_TYPE_DEPTH_STENCIL_TARGET_VIEW;

  /// \copydoc GALA_RESOURCE_TYPE_SAMPLER
  static const Type SAMPLER = ::GALA_RESOURCE_TYPE_SAMPLER;

  /// \copydoc GALA_RESOURCE_TYPE_SHADER
  static const Type SHADER = ::GALA_RESOURCE_TYPE_SHADER;

  /// \copydoc GALA_RESOURCE_TYPE_VERTEX_SHADER
  static const Type VERTEX_SHADER = ::GALA_RESOURCE_TYPE_VERTEX_SHADER;

  /// \copydoc GALA_RESOURCE_TYPE_PIXEL_SHADER
  static const Type PIXEL_SHADER = ::GALA_RESOURCE_TYPE_PIXEL_SHADER;

 public:
  /// \copydoc ::gala_resource_handle_t
  typedef ::gala_resource_handle_t Handle;
};

/// \copydoc ::gala_dimensionality_t
typedef gala_dimensionality_t Dimensionality;

/// \copydoc ::GALA_ONE_DIMENSIONAL
static const Dimensionality ONE_DIMENSIONAL = ::GALA_ONE_DIMENSIONAL;

/// \copydoc ::GALA_TWO_DIMENSIONAL
static const Dimensionality TWO_DIMENSIONAL = ::GALA_TWO_DIMENSIONAL;

/// \copydoc ::GALA_THREE_DIMENSIONAL
static const Dimensionality THREE_DIMENSIONAL = ::GALA_THREE_DIMENSIONAL;

/// \copydoc ::gala_mutability_t
typedef gala_mutability_t Mutability;

/// \copydoc ::GALA_MUTABILITY_MUTABLE
static const Mutability MUTABLE = ::GALA_MUTABILITY_MUTABLE;

/// \copydoc ::GALA_MUTABILITY_IMMUTABLE
static const Mutability IMMUTABLE = ::GALA_MUTABILITY_IMMUTABLE;

/// \copydoc ::GALA_MUTABILITY_DYNAMIC
static const Mutability DYNAMIC = ::GALA_MUTABILITY_DYNAMIC;

/// \copydoc ::gala_bindability_t
typedef gala_bindability_t Bindability;

/// \copydoc ::GALA_BIND_TO_VERTEX_BUFFER
static const Bindability BIND_TO_VERTEX_BUFFER = ::GALA_BIND_TO_VERTEX_BUFFER;

/// \copydoc ::GALA_BIND_TO_INDEX_BUFFER
static const Bindability BIND_TO_INDEX_BUFFER = ::GALA_BIND_TO_INDEX_BUFFER;

/// \copydoc ::GALA_BIND_TO_CONSTANT_BUFFER
static const Bindability BIND_TO_CONSTANT_BUFFER = ::GALA_BIND_TO_CONSTANT_BUFFER;

/// \copydoc ::GALA_BIND_TO_SAMPLER
static const Bindability BIND_TO_SAMPLER = ::GALA_BIND_TO_SAMPLER;

/// \copydoc ::GALA_BIND_TO_RENDER_TARGET
static const Bindability BIND_TO_RENDER_TARGET = ::GALA_BIND_TO_RENDER_TARGET;

/// \copydoc ::GALA_BIND_TO_DEPTH_STENCIL_TARGET
static const Bindability BIND_TO_DEPTH_STENCIL_TARGET = ::GALA_BIND_TO_DEPTH_STENCIL_TARGET;

} // gala
#endif // __cplusplus

#endif // _GALA_RESOURCE_H_
