//===-- gala/foundation/assert.cc -----------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//

#include "gala/foundation/assert.h"

GALA_BEGIN_EXTERN_C

static gala_assertion_handler_t assertion_handler_ = NULL;
static void *assertion_handler_ctx_ = NULL;

void gala_assertion_handler(
  gala_assertion_handler_t *assertion_handler,
  void **ctx)
{
  *assertion_handler = assertion_handler_;
  *ctx = assertion_handler_ctx_;
}

void gala_set_assertion_handler(
  gala_assertion_handler_t new_assertion_handler,
  void *ctx)
{
  assertion_handler_ = new_assertion_handler;
  assertion_handler_ctx_ = ctx;
}

GALA_END_EXTERN_C

#ifdef __cplusplus
namespace gala {
  namespace {
    // Wrap the C++ assertion handler in a C-compatible bridge but reuse |ctx|.
    // This allows C to opaquely call into C++.
    static AssertionHandler cpp_assertion_handler_;

    static void _faux_assertion_handler(const gala_assertion_t *assertion, void *ctx) {
      cpp_assertion_handler_(*assertion, ctx);
    }
  }
}

void gala::assertion_handler(
  ::gala::AssertionHandler *assertion_handler,
  void **ctx)
{
  *assertion_handler = cpp_assertion_handler_;
  *ctx = ::assertion_handler_ctx_;
}

void gala::set_assertion_handler(
  ::gala::AssertionHandler new_assertion_handler,
  void *ctx)
{
  cpp_assertion_handler_ = new_assertion_handler;
  ::assertion_handler_ = &_faux_assertion_handler;
  ::assertion_handler_ctx_ = ctx;
}

#endif // __cplusplus
