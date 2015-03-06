//===-- gala/engine.c -------------------------------------------*- C++ -*-===//
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

#include "gala/engine.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

void
gala_engine_init(
  gala_engine_t *engine)
{
  gala_assert_debug(engine != NULL);
  engine->type = GALA_ENGINE_TYPE_INVALID;
  engine->flags = 0x00000000ul;
}

//===----------------------------------------------------------------------===//

void
gala_engine_shutdown(
  gala_engine_t *engine)
{
  gala_assert_debug(engine != NULL);
#if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
  // This might help find some (stupid) bugs.
  engine->type = GALA_ENGINE_TYPE_INVALID;
  engine->flags = 0x00000000ul;
#endif
}

//===----------------------------------------------------------------------===//

int gala_engine_to_s(
  const gala_engine_t *engine,
  char buf[],
  const int buf_sz)
{
  gala_assert_debug(engine != NULL);
  const char *type_as_str;
  switch (engine->type) {
    default: type_as_str = "<invalid>"; break;
    case GALA_ENGINE_TYPE_SOFTWARE: type_as_str = "software"; break;
    case GALA_ENGINE_TYPE_HARDWARE: type_as_str = "hardware"; break;
  }
  const bool debug = !!(engine->flags & GALA_ENGINE_DEBUG);
  return snprintf(buf, buf_sz, "#<gala_engine_t:%.16" PRIxPTR " type=%s debug=%s>", engine, type_as_str, debug ? "yes" : "no");
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

void Engine::init(::gala::Engine *engine) {
  ::gala_engine_init(&engine->__engine__);
}

//===----------------------------------------------------------------------===//

void Engine::shutdown() {
  ::gala_engine_shutdown(&this->__engine__);
}

//===----------------------------------------------------------------------===//

int Engine::to_s(char buf[], const int buf_sz) const {
  const char *type_as_str;
  switch (this->__engine__.type) {
    default: type_as_str = "<invalid>"; break;
    case kSoftware: type_as_str = "software"; break;
    case kHardware: type_as_str = "hardware"; break;
  }
  const bool debug = !!(this->__engine__.flags & GALA_ENGINE_DEBUG);
  return snprintf(buf, buf_sz, "#<gala::Engine:%.16" PRIxPTR " type=%s debug=%s>", this, type_as_str, debug ? "yes" : "no");
}

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
