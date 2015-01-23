//===-- gala/error.h --------------------------------------------*- C++ -*-===//
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

#ifndef _GALA_ERROR_H_
#define _GALA_ERROR_H_

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
typedef enum gala_error {
  /// No error; success.
  GALA_ERROR_NONE = 0,
  /// Unknown.
  GALA_ERROR_UNKNOWN = 1,
  /// One or more arguments are invalid.
  GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS = 2,
  /// Not enough memory.
  GALA_ERROR_OUT_OF_MEMORY = 3
} gala_error_t;

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_error_details {
  /// \copydoc ::gala_error_t
  gala_error_t error;
  /// TODO(mike): Document this.
  const char *details;
  /// TODO(mike): Document this.
  bool _own_details_mem;
} gala_error_details_t;

//===----------------------------------------------------------------------===//

/// \brief
/// \param error
/// \param format
/// \returns
///
extern
GALA_PUBLIC
const gala_error_details_t *gala_error_details_create_formatted(
  const gala_error_t error,
  const char *format,
  ...);

//===----------------------------------------------------------------------===//

/// \brief
/// \param error
/// \param details
/// \returns
///
extern
GALA_PUBLIC
const gala_error_details_t *gala_error_details_create_unformatted(
  const gala_error_t error,
  const char *details);

//===----------------------------------------------------------------------===//

/// \brief
/// \param error_details
/// \returns
///
extern
GALA_PUBLIC
void gala_error_details_destroy(
  const gala_error_details_t *error_details);

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace gala {

//===----------------------------------------------------------------------===//

namespace Errors {
  enum _ {
    /// \copydoc ::GALA_ERROR_NONE
    kNone = ::GALA_ERROR_NONE,
    /// \copydoc ::GALA_ERROR_UNKNOWN
    kUnknown = ::GALA_ERROR_UNKNOWN,
    /// \copydoc ::GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS
    kOneOrMoreInvalidArguments = ::GALA_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS,
    /// \copydoc ::GALA_ERROR_OUT_OF_MEMORY
    kOutOfMemory = ::GALA_ERROR_OUT_OF_MEMORY
  };
}

/// \copydoc ::gala_error_t
typedef Errors::_ Error;

//===----------------------------------------------------------------------===//

/// \copydoc ::gala_error_details_t
class ErrorDetails {
 private:
  ErrorDetails();
  ErrorDetails(const ErrorDetails &error_details);
  ErrorDetails &operator=(const ErrorDetails &error_details);
  ~ErrorDetails();

 public:
  /// \copydoc ::gala_error_details_destroy
  void destroy() const {
    ::gala_error_details_destroy((const ::gala_error_details_t *)&__error_details__);
  }

 public:
  /// \copydoc ::gala_error_details_t::error
  const ::gala::Error error() const {
    return (const ::gala::Error)__error_details__.error;
  }

  /// \copydoc ::gala_error_details_t::details
  const char *details() const {
    return __error_details__.details;
  }

 public:
  ::gala_error_details_t __error_details__;
};

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_ERROR_H_

//============================================================================//
