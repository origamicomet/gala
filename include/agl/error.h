//===-- agl/error.h ---------------------------------------------*- C++ -*-===//
//
//  Abstract Graphics Library (AGL)
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//    * Michael Williams <mwilliams@bitbyte.ca>
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Defines various errors and provides error management.
///
//===----------------------------------------------------------------------===//

#ifndef _AGL_ERROR_H_
#define _AGL_ERROR_H_

//============================================================================//

#include "agl/linkage.h"
#include "agl/types.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef enum agl_error {
  /// No error occured.
  AGL_ERROR_NONE = 0,
  /// The requested feature is not implemented.
  AGL_ERROR_NOT_IMPLEMENTED = 1,
  /// An internal error occured.
  AGL_ERROR_INTERNAL = 2,
  /// One or more invalid arguments specified are invalid.
  AGL_ERROR_ONE_OR_MORE_INVALID_ARGUMENTS = 3,
} agl_error_t;

//===----------------------------------------------------------------------===//

/// \def AGL_ERROR_UNFORMATTED
/// \brief
///
#define AGL_ERROR_UNFORMATTED(_Reason) \
  agl_error_details_construct(__FILE__, __LINE__, _Reason)

/// \def AGL_ERROR_FORMATTED
/// \brief
///
#define AGL_ERROR_FORMATTED(_Format, ...) \
  agl_error_details_constructf(__FILE__, __LINE__, _Format, ##__VA_ARGS__)

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct agl_error_details {
  const char *file;
  unsigned line;
  const char *reason;
  unsigned __owned__ : 1;
  unsigned __reserved__ : 31;
} agl_error_details_t;

//===----------------------------------------------------------------------===//

/// \brief
///
extern
AGL_EXPORT
agl_error_details_t *
agl_error_details_construct(
  const char *file,
  unsigned line,
  const char *reason);

//===----------------------------------------------------------------------===//

/// \brief
///
extern
AGL_EXPORT
agl_error_details_t *
agl_error_details_constructf(
  const char *file,
  unsigned line,
  const char *format,
  ...);

//===----------------------------------------------------------------------===//

/// \brief
///
extern
AGL_EXPORT
void
agl_error_details_destruct(
  agl_error_details_t *error_details);

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#endif // _AGL_ERROR_H_

//============================================================================//
