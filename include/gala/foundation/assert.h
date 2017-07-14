//===-- gala/foundation/assert.h ------------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//
//
// TODO(mtwilliams): Document the purpose of this file.
//
//===----------------------------------------------------------------------===//

#ifndef _GALA_FOUNDATION_ASSERT_H_
#define _GALA_FOUNDATION_ASSERT_H_

#include "gala/config.h"
#include "gala/linkage.h"

#include "gala/foundation/types.h"
#include "gala/foundation/support.h"

GALA_BEGIN_EXTERN_C

/// Describes a (failed) assertion.
typedef struct gala_assertion {
  /// The predicate that failed.
  const char *predicate;

  /// A custom, more friendly description of why the predicate failed.
  const char *reason;

  /// Describes where the assertion is in the codebase.
  struct {
    const char *file;
    size_t line;
  } location;
} gala_assertion_t;

///
typedef void (*gala_assertion_handler_t)(const gala_assertion_t *assertion, void *ctx);

///
extern GALA_PUBLIC
void gala_assertion_handler(
  gala_assertion_handler_t *assertion_handler,
  void **ctx);

///
extern GALA_PUBLIC
void gala_set_assertion_handler(
  gala_assertion_handler_t new_assertion_handler,
  void *ctx = NULL);

GALA_END_EXTERN_C

#ifdef __cplusplus
namespace gala {

/// \copydoc ::gala_assertion_t
typedef ::gala_assertion_t Assertion;

/// \copydoc ::gala_assertion_handler_t
typedef void (*AssertionHandler)(const ::gala::Assertion &assertion, void *ctx);

///
extern GALA_PUBLIC
void assertion_handler(
  ::gala::AssertionHandler *assertion_handler,
  void **ctx);

///
extern GALA_PUBLIC
void set_assertion_handler(
  ::gala::AssertionHandler new_assertion_handler,
  void *ctx = NULL);

} // gala
#endif // __cplusplus

#include <stdio.h>

// REFACTOR(mtwilliams): Extract into a common header?
#if GALA_COMPILER == GALA_COMPILER_MSVC
  #include <malloc.h>
  #ifndef alloca
    #define alloca _alloca
  #endif
#endif

/// \def gala_assert
/// \brief Raises a fuss if @_Predicate doesn't evaluate to true.
///
#define gala_assert(_Predicate) \
  do { \
    if (!(_Predicate)) { \
      gala_assertion_t assertion; \
      assertion.predicate = #_Predicate; \
      assertion.reason = NULL; \
      assertion.location.file = __FILE__ ; \
      assertion.location.line = (size_t)__LINE__; \
      gala_assertion_handler_t assertion_handler; \
      void *assertion_handler_ctx; \
      gala_assertion_handler(&assertion_handler, &assertion_handler_ctx); \
      if (assertion_handler != NULL) \
        assertion_handler(&assertion, assertion_handler_ctx); \
      GALA_TRAP(); \
    } \
  } while (0,0)

/// \def gala_assertf
/// \brief Raises a fuss if @_Predicate doesn't evaluate to true, providing
/// user-specified, formatted reasoning.
///
#define gala_assertf(_Predicate, _Reason_format, ...) \
  do { \
    if (!(_Predicate)) { \
      gala_assertion_t assertion; \
      assertion.predicate = #_Predicate; \
      const size_t reason_len = snprintf(NULL, 0, _Reason_format, ##__VA_ARGS__) + 1; \
      const char *reason = (const char *)alloca(reason_len); \
      snprintf((char *)reason, reason_len, _Reason_format, ##__VA_ARGS__); \
      assertion.reason = reason; \
      assertion.location.file = __FILE__; \
      assertion.location.line = (size_t)__LINE__; \
      gala_assertion_handler_t assertion_handler; \
      void *assertion_handler_ctx; \
      gala_assertion_handler(&assertion_handler, &assertion_handler_ctx); \
      if (assertion_handler != NULL) \
        assertion_handler(&assertion, assertion_handler_ctx); \
      GALA_TRAP(); \
    } \
  } while (0,0)

// TODO(mtwilliams): Paranoid assertions.

#if defined(DOXYGEN)
  #define gala_assert_debug gala_assert
  #define gala_assertf_debug gala_assertf
  #define gala_assert_development gala_assert
  #define gala_assertf_development gala_assertf
  #define gala_assert_release gala_assert
  #define gala_assertf_release gala_assertf
#else
  #if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
    #define gala_assert_debug gala_assert
    #define gala_assertf_debug gala_assertf
  #else
    #define gala_assert_debug(...)
    #define gala_assertf_debug(...)
  #endif

  #if GALA_CONFIGURATION <= GALA_CONFIGURATION_DEVELOPMENT
    #define gala_assert_development gala_assert
    #define gala_assertf_development gala_assertf
  #else
    #define gala_assert_development(...)
    #define gala_assertf_development(...)
  #endif

  #if GALA_CONFIGURATION <= GALA_CONFIGURATION_RELEASE
    #define gala_assert_release gala_assert
    #define gala_assertf_release gala_assertf
  #else
    #define gala_assert_release(...)
    #define gala_assertf_release(...)
  #endif
#endif

#endif // _GALA_FOUNDATION_ASSERT_H_
