//===-- gala/output.h -------------------------------------------*- C++ -*-===//
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

#ifndef _GALA_OUTPUT_H_
#define _GALA_OUTPUT_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef enum gala_output_type {
  /// Invalid.
  GALA_OUTPUT_TYPE_INVALID = 0,
  /// Monitor.
  GALA_OUTPUT_TYPE_MONITOR = 1,
  /// Television.
  GALA_OUTPUT_TYPE_TELEVISION = 2,
  /// \internal Force at least uint32_t storage and alignment.
  GALA_OUTPUT_TYPE_FORCE_UINT32 = 0x7fffffff
} gala_output_type_t;

//===----------------------------------------------------------------------===//

/// \brief
///
typedef enum gala_output_flags {
  /// Primary.
  GALA_OUTPUT_PRIMARY = (1 << 0)
} gala_output_flags_t;

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_output {
  /// \copyodc :;gala_output_type_t
  gala_output_type_t type;
  /// \copydoc ::gala_output_flags_t
  uint32_t flags;
} gala_output_t;

//===----------------------------------------------------------------------===//

/// \brief
/// \param output
/// \returns
///
extern GALA_PUBLIC void
gala_output_init(
  gala_output_t *output);

//===----------------------------------------------------------------------===//

/// \brief
/// \param output
///
extern GALA_PUBLIC void
gala_output_destroy(
  gala_output_t *output);

//===----------------------------------------------------------------------===//

/// \brief
/// \param output
/// \param buf
/// \param buf_sz
/// \returns
///
extern GALA_PUBLIC int
gala_output_to_s(
  const gala_output_t *output,
  char buf[],
  const int buf_sz);

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace gala {

//===----------------------------------------------------------------------===//

/// \copydoc ::gala_output_t
class GALA_PUBLIC Output {
 public:
  /// \copydoc ::gala_output_type_t
  enum Type {
    /// \copydoc ::GALA_OUTPUT_TYPE_INVALID
    kInvalid = ::GALA_OUTPUT_TYPE_INVALID,
    /// \copydoc ::GALA_OUTPUT_TYPE_MONITOR
    kMonitor = ::GALA_OUTPUT_TYPE_MONITOR,
    /// \copydoc ::GALA_OUTPUT_TYPE_TELEVISION
    kTelevision = ::GALA_OUTPUT_TYPE_TELEVISION,
  };

  /// \copydoc ::gala_output_flags_t
  enum Flags {
    /// \copydoc ::GALA_OUTPUT_PRIMARY
    kPrimary = ::GALA_OUTPUT_PRIMARY
  };

 public:
  /// \copydoc ::gala_output_init
  static void init(::gala::Output *output);

  /// \copydoc ::gala_output_destroy
  void destroy();

 public:
  /// \copydoc ::gala_output_to_s
  int to_s(char buf[], const int buf_sz) const;

 public:
  ::gala_output_t __output__;
};

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_OUTPUT_H_

//============================================================================//
