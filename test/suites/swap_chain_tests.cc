#include "gala.h"

#include "surface.h"
#include "command_buffer.h"

namespace gala {
namespace test {
namespace swap_chain_tests {

static bool complete;

void on_surface_event(Surface *surface,
                      const Surface::Event *event,
                      void *);

void run(gala_engine_t *engine) {
  complete = false;

  Surface *surfaces[2] = {
    Surface::create({"Swap Chain Tests - A", {640, 480}}),
    Surface::create({"Swap Chain Tests - B", {640, 480}})
  };

  gala_swap_chain_handle_t swap_chains[2];
  gala_render_target_view_handle_t render_target_views[2];

  {
    gala_command_buffer_t cmds = command_buffer();

    gala_swap_chain_desc_t swap_chain_desc;
    swap_chain_desc.format = GALA_PIXEL_FORMAT_R8G8B8;
    swap_chain_desc.width = 640;
    swap_chain_desc.height = 480;
    swap_chain_desc.refresh_rate.numerator = 60;
    swap_chain_desc.refresh_rate.denominator = 1;
    swap_chain_desc.flags = 0;

    gala_render_target_view_desc_t render_target_view_desc;
    render_target_view_desc.format = swap_chain_desc.format;
    render_target_view_desc.dimensionality = GALA_TWO_DIMENSIONAL;
    render_target_view_desc.width = swap_chain_desc.width;
    render_target_view_desc.height = swap_chain_desc.height;

    swap_chain_desc.surface = surfaces[0]->to_native_hndl();
    swap_chains[0] = gala_swap_chain_create(engine, &cmds, &swap_chain_desc);
    swap_chain_desc.surface = surfaces[1]->to_native_hndl();
    swap_chains[1] = gala_swap_chain_create(engine, &cmds, &swap_chain_desc);

    render_target_view_desc.storage = swap_chains[0];
    render_target_views[0] = gala_render_target_view_create(engine, &cmds, &render_target_view_desc);
    render_target_view_desc.storage = swap_chains[1];
    render_target_views[1] = gala_render_target_view_create(engine, &cmds, &render_target_view_desc);

    engine->execute(engine, &cmds);
  }

  while (!complete) {
    gala_command_buffer_t cmds = command_buffer();

    gala_start_of_frame(&cmds);
    
    gala_set_render_and_depth_stencil_targets(&cmds, 1, &render_target_views[0], GALA_INVALID_DEPTH_STENCIL_TARGET_VIEW_HANDLE);
    gala_clear_render_targets(&cmds, 159.f / 255.0f, 43.f / 255.0f, 104.f / 255.0f, 1.0f);
    
    gala_set_render_and_depth_stencil_targets(&cmds, 1, &render_target_views[1], GALA_INVALID_DEPTH_STENCIL_TARGET_VIEW_HANDLE);
    gala_clear_render_targets(&cmds, 18.f / 255.0f, 98.f / 255.0f, 108.f / 255.0f, 1.0f);
    
    gala_present(&cmds, swap_chains[0]);
    gala_present(&cmds, swap_chains[1]);
    
    gala_end_of_frame(&cmds, NULL);

    engine->execute(engine, &cmds);

    surfaces[0]->update(&on_surface_event);
    surfaces[1]->update(&on_surface_event);
  }

  {
    gala_command_buffer_t cmds = command_buffer();

    gala_render_target_view_destroy(engine, &cmds, render_target_views[0]);
    gala_render_target_view_destroy(engine, &cmds, render_target_views[1]);
    
    gala_swap_chain_destroy(engine, &cmds, swap_chains[0]);
    gala_swap_chain_destroy(engine, &cmds, swap_chains[1]);

    engine->execute(engine, &cmds);
  }

  surfaces[0]->destroy();
  surfaces[1]->destroy();
}

void on_surface_event(Surface *surface,
                      const Surface::Event *event,
                      void *) {
  switch (event->type) {
    case Surface::Event::CLOSED:
      complete = true;
      break;
  }
}

} // swap_chain_tests
} // test
} // gala
