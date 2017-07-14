#include <stdlib.h>
#include <stdio.h>

#include "gala.h"

namespace gala {
namespace test {
  static struct {
    gala_backend_t type;

    const char *slug;
    const char *name;

    void (*init)(void);
    void (*shutdown)(void);

    gala_engine_t *(*create_and_init_engine)(const gala_engine_creation_params_t *);
    void (*destroy_engine)(gala_engine_t *);
  } backends[] = {
    #if GALA_ENABLE_OPENGL
      { GALA_BACKEND_OPENGL,
        "opengl", "OpenGL",
        &gala_ogl_init,
        &gala_ogl_shutdown,
        &gala_ogl_create_and_init_engine,
        &gala_ogl_destroy_engine },
    #endif
    #if GALA_ENABLE_D3D11
      { GALA_BACKEND_D3D11,
        "d3d11", "Direct3D 11",
        &gala_d3d11_init,
        &gala_d3d11_shutdown,
        &gala_d3d11_create_and_init_engine,
        &gala_d3d11_destroy_engine },
    #endif
  };

  // TODO(mtwilliams): Refactor test suites into a common structure.
  namespace swap_chain_tests { extern void run(gala_engine_t *engine); }

  static struct {
    const char *slug;
    const char *name;

    void (*run)(gala_engine_t *engine);
  } suites[] = {
    { "swap_chain", "Swap Chain", &swap_chain_tests::run }
  };
} // test
} // gala

// TODO(mtwilliams): Improve assertion handler.
static void _assertion_handler(const gala_assertion_t *assertion, void *) {
  ::fprintf(stderr, "Assertion failed!\n");
  ::fprintf(stderr, " predicate=\"%s\"\n", assertion->predicate);
  if (assertion->reason)
    ::fprintf(stderr, " reason=\"%s\"\n", assertion->reason);
  ::fprintf(stderr, " file=\"%s\" line=%u\n\n", assertion->location.file, (unsigned int)assertion->location.line);
  ::exit(EXIT_FAILURE);
}

int main(int argc, const char *argv[]) {
  gala_set_assertion_handler(&_assertion_handler, NULL);

  const gala_uint32_t num_backends = sizeof(gala::test::backends) / sizeof(gala::test::backends[0]);
  const gala_uint32_t num_test_suites = sizeof(gala::test::suites) / sizeof(gala::test::suites[0]);

  // Initialize all available backends.
  for (gala_uint32_t backend = 0; backend < num_backends; ++backend)
    gala::test::backends[backend].init();

  // Run all test suites against all available backends.
  for (gala_uint32_t backend = 0; backend < num_backends; ++backend) {
    gala_engine_creation_params_t engine_creation_params;
    engine_creation_params.type = GALA_ENGINE_TYPE_HARDWARE;
    engine_creation_params.flags = GALA_ENGINE_DEBUG;

    gala_engine_t *engine = gala::test::backends[backend].create_and_init_engine(&engine_creation_params);

    for (gala_uint32_t test_suite = 0; test_suite < num_test_suites; ++test_suite)
      gala::test::suites[test_suite].run(engine);

    gala::test::backends[backend].destroy_engine(engine);
  }

  return EXIT_FAILURE;
}
