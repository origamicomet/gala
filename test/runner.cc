#include "gala.h"

#include <stdlib.h>
#include <stdio.h>

static struct {
  gala_backend_t type;

  const char *slug;
  const char *name;

  void (*init)(void);
  void (*shutdown)(void);
} backends[] = {
  #if GALA_ENABLE_D3D11
    { GALA_BACKEND_D3D11, "d3d11", "Direct3D 11", &gala_d3d11_init, &gala_d3d11_shutdown },
  #endif
};


int main(int argc, const char *argv[]) {
  // Initialize all available backends.
  const gala_uint32_t N = sizeof(backends) / sizeof(backends[0]);
  for (gala_uint32_t backend = 0; backend < N; ++backend)
    backends[backend].init();

  return EXIT_FAILURE;
}
