#include "gala.h"

#include "surface.h"
#include "command_buffer.h"

namespace gala {
namespace test {
namespace swap_chain_tests {

void run(gala_engine_t *engine);

} // swap_chain_tests
} // test
} // gala

void on_surface_event(const gala::test::Surface::Event *event, void *) {
  // Do nothing for now.
}

void gala::test::swap_chain_tests::run(gala_engine_t *engine) {
  Surface *surface = Surface::create({"Swap Chain Tests", {1280, 720}});

  gala_swap_chain_handle_t swap_chain;
  gala_render_target_view_handle_t render_target_view;

  {
    gala_command_buffer_t cmds = command_buffer();

    gala_swap_chain_desc_t swap_chain_desc;
    swap_chain_desc.format = GALA_PIXEL_FORMAT_R8G8B8;
    swap_chain_desc.width = 1280;
    swap_chain_desc.height = 720;
    swap_chain_desc.refresh_rate.numerator = 60;
    swap_chain_desc.refresh_rate.denominator = 1;
    swap_chain_desc.flags = 0;
    swap_chain_desc.surface = surface->to_native_hndl();

    swap_chain = gala_swap_chain_create(engine, &cmds, &swap_chain_desc);

    gala_render_target_view_desc_t render_target_view_desc;
    render_target_view_desc.format = swap_chain_desc.format;
    render_target_view_desc.dimensionality = GALA_RENDER_TARGET_VIEW_2D;
    render_target_view_desc.width = swap_chain_desc.width;
    render_target_view_desc.height = swap_chain_desc.height;
    render_target_view_desc.storage = swap_chain;

    render_target_view = gala_render_target_view_create(engine, &cmds, &render_target_view_desc);

    engine->execute(engine, &cmds);
  }

  while (true) {
    gala_command_buffer_t cmds = command_buffer();

    gala_set_render_and_depth_stencil_targets(&cmds, 1, &render_target_view, GALA_INVALID_DEPTH_STENCIL_TARGET_VIEW_HANDLE);
    gala_clear_render_targets_command(&cmds, 159.f / 255.0f, 43.f / 255.0f, 104.f / 255.0f, 1.0f);
    gala_present(&cmds, swap_chain);

    engine->execute(engine, &cmds);

    surface->update(&on_surface_event);
  }

  {
    gala_command_buffer_t cmds = command_buffer();

    gala_render_target_view_destroy(engine, &cmds, render_target_view);
    gala_swap_chain_destroy(engine, &cmds, swap_chain);
    engine->execute(engine, &cmds);
  }

  surface->destroy();
}
