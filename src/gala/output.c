//===-- gala/output.c -------------------------------------------*- C++ -*-===//
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

#include "gala/output.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

void
gala_output_init(
  gala_output_t *output)
{
  gala_assert_debug(output != NULL);
  output->type = GALA_OUTPUT_TYPE_INVALID;
  output->flags = 0x00000000ul;
}

//===----------------------------------------------------------------------===//

void
gala_output_destroy(
  gala_output_t *output)
{
  gala_assert_debug(output != NULL);
#if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
  // This might help find some (stupid) bugs.
  output->type = GALA_OUTPUT_TYPE_INVALID;
  output->flags = 0x00000000ul;
#endif
}

//===----------------------------------------------------------------------===//

int gala_output_to_s(
  const gala_output_t *output,
  char buf[],
  const int buf_sz)
{
  gala_assert_debug(output != NULL);
  const char *type_as_str;
  switch (output->type) {
    default: type_as_str = "<invalid>"; break;
    case GALA_OUTPUT_TYPE_MONITOR: type_as_str = "monitor"; break;
    case GALA_OUTPUT_TYPE_TELEVISION: type_as_str = "television"; break;
  }
  const bool primary = !!(output->flags & GALA_OUTPUT_PRIMARY);
  return snprintf(buf, buf_sz, "#<gala_output_t:%.16" PRIxPTR " type=%s primary=%s>", output, type_as_str, primary ? "yes" : "no");
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace gala {

//===----------------------------------------------------------------------===//

void Output::init(::gala::Output *output) {
  ::gala_output_init(&output->__output__);
}

//===----------------------------------------------------------------------===//

void Output::destroy() {
  ::gala_output_destroy(&this->__output__);
}

//===----------------------------------------------------------------------===//

int Output::to_s(char buf[], const int buf_sz) const {
  const char *type_as_str;
  switch (this->__output__.type) {
    default: type_as_str = "<invalid>"; break;
    case GALA_OUTPUT_TYPE_MONITOR: type_as_str = "monitor"; break;
    case GALA_OUTPUT_TYPE_TELEVISION: type_as_str = "television"; break;
  }
  const bool primary = !!(this->__output__.flags & GALA_OUTPUT_PRIMARY);
  return snprintf(buf, buf_sz, "#<gala::Output:%.16" PRIxPTR " type=%s primary=%s>", this, type_as_str, primary ? "yes" : "no");
}

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
