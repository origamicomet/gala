//===-- gala/context.h ------------------------------------------*- C++ -*-===//
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

#ifndef _GALA_CONTEXT_H_
#define _GALA_CONTEXT_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"
#include "gala/error.h"

//===----------------------------------------------------------------------===//

#include "gala/adapter.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_context {
  /// The backend this belongs to.
  struct gala_backend *_backend;
} gala_context_t;

//===----------------------------------------------------------------------===//

/// \brief
/// \param context
/// \param buf
/// \param buf_sz
/// \param error_details
/// \returns
///
extern
GALA_PUBLIC
gala_error_t gala_context_to_s(
  const gala_context_t *context,
  char *buf,
  const size_t buf_sz,
  const gala_error_details_t **error_details);

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace gala {

//===----------------------------------------------------------------------===//

/// \copydoc ::gala_context_t
class Context {
 public:
  /// \copydoc ::gala_context_to_s
  ::gala::Error to_s(
    char *buf,
    const size_t buf_sz,
    const ::gala::ErrorDetails **error_details = NULL) const
  {
    return (::gala::Error)::gala_context_to_s(&__context__,
                                              buf, buf_sz,
                                              (const ::gala_error_details_t **)error_details);
  }

 public:
  ::gala_context_t __context__;
};

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_CONTEXT_H_

//============================================================================//
