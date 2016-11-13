#include "gala/command_buffer.h"
#include "command_buffer.h"

namespace gala {
namespace test {

static const gala_size_t command_buffer_sz = 1048576; /* 1MiB */
static gala_uint8_t command_buffer_mem[command_buffer_sz] = { 0, };

gala_command_buffer_t command_buffer() {
  gala_command_buffer_t command_buffer;

  gala_command_buffer_init(&command_buffer);

  command_buffer.start = (uintptr_t)&command_buffer_mem[0];
  command_buffer.current = (uintptr_t)&command_buffer_mem[0];
  command_buffer.end = (uintptr_t)&command_buffer_mem[command_buffer_sz-1];

  return command_buffer;
}

} // test
} // gala
