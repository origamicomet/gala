#include "gala.h"

#include "surface.h"
#include "command_buffer.h"

namespace gala {
namespace test {
namespace end_to_end_tests {

struct Vertex {
  f32 x, y;
  u8 r, g, b, a;
};

static const Vertex VERTICES[2][9] = {
  {
    { -1.0f, -1.0f, 0xff, 0x00, 0x00, 0xff },
    {  0.0f, -1.0f, 0xff, 0x00, 0x00, 0xff },
    { -1.0f,  0.0f, 0xff, 0x00, 0x00, 0xff },

    {  0.0f, -1.0f, 0x00, 0xff, 0x00, 0xff },
    {  1.0f, -1.0f, 0x00, 0xff, 0x00, 0xff },
    {  0.0f,  0.0f, 0x00, 0xff, 0x00, 0xff },

    { -1.0f,  0.0f, 0x00, 0x00, 0xff, 0xff },
    {  0.0f,  0.0f, 0x00, 0x00, 0xff, 0xff },
    { -1.0f,  1.0f, 0x00, 0x00, 0xff, 0xff },
  },

  {
    { -1.0f,  1.0f, 0xff, 0xff, 0xff, 0x00 },
    {  1.0f, -1.0f, 0xff, 0xff, 0xff, 0x00 },
    {  1.0f,  1.0f, 0xff, 0xff, 0xff, 0xff },

    { -1.0f,  0.0f, 0x80, 0x00, 0x00, 0xff },
    {  0.0f, -1.0f, 0x00, 0x80, 0x00, 0xff },
    {  0.0f,  0.0f, 0x00, 0x00, 0x80, 0xff },

    { 0.0f, 0.0f, 0x00, 0x00, 0x00, 0x00 },
  }
};

static const char *VERTEX_SHADER_SOURCE =
  "layout (location = 0) in vec2 position;\n" \
  "layout (location = 1) in vec4 color;\n" \
  "\n" \
  "out vec4 frag_color;\n" \
  "\n" \
  "void main(void) {\n" \
  "  gl_Position = vec4(position.x, position.y, 0.0f, 1.0f);\n" \
  "  frag_color = color;\n" \
  "}\n";

static const char *PIXEL_SHADER_SOURCE =
  "in vec4 frag_color;\n" \
  "\n" \
  "layout (location = 0) out vec4 color;\n"
  "\n" \
  "void main(void) {\n" \
  "  color = frag_color;\n" \
  "}\n";

static bool complete;

void on_surface_event(Surface *surface,
                      const Surface::Event *event,
                      void *);

void run(gala_engine_t *engine) {
  complete = false;

  Surface *surface = Surface::create({"End-to-End Tests", {1280, 720}});

  gala_swap_chain_handle_t swap_chain;
  gala_render_target_view_handle_t render_target_view;

  gala_pipeline_handle_t pipeline;

  gala_shader_handle_t vertex_shader;
  gala_shader_handle_t pixel_shader;

  gala_input_layout_handle_t input_layout;

  gala_buffer_handle_t vertex_buffers[2];

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
    render_target_view_desc.dimensionality = GALA_TWO_DIMENSIONAL;
    render_target_view_desc.width = swap_chain_desc.width;
    render_target_view_desc.height = swap_chain_desc.height;
    render_target_view_desc.storage = swap_chain;

    render_target_view = gala_render_target_view_create(engine, &cmds, &render_target_view_desc);

    gala_pipeline_desc_t pipeline_desc;
    pipeline_desc.winding = GALA_CW;
    pipeline_desc.fill = GALA_SOLID;
    pipeline_desc.cull = GALA_CULL_NONE;
    pipeline_desc.color.blend = true;
    pipeline_desc.color.src = GALA_BLEND_SRC_ALPHA;
    pipeline_desc.color.dst = GALA_BLEND_INV_SRC_ALPHA;
    pipeline_desc.color.op = GALA_BLEND_OP_ADD;
    pipeline_desc.color.mask = 0xffffffff;
    pipeline_desc.depth.test = false;
    pipeline_desc.depth.mask = 0x00000000;
    pipeline_desc.stencil.test = false;
    pipeline_desc.stencil.ref = 0x00000000;
    pipeline_desc.stencil.mask = 0x00000000;

    pipeline = gala_pipeline_create(engine, &cmds, &pipeline_desc);

    {
      gala_shader_desc_t shader_desc;
      shader_desc.type = GALA_VERTEX_SHADER;
      shader_desc.encoding = GALA_SHADER_SOURCE;
      shader_desc.magic = 0;
      shader_desc.source = VERTEX_SHADER_SOURCE;
      shader_desc.length = 0;

      vertex_shader = gala_shader_create(engine, &cmds, &shader_desc);
    }

    {
      gala_shader_desc_t shader_desc;
      shader_desc.type = GALA_PIXEL_SHADER;
      shader_desc.encoding = GALA_SHADER_SOURCE;
      shader_desc.magic = 0;
      shader_desc.source = PIXEL_SHADER_SOURCE;
      shader_desc.length = 0;

      pixel_shader = gala_shader_create(engine, &cmds, &shader_desc);
    }

    gala_input_layout_desc_t input_layout_desc;
    input_layout_desc.count = 2;
    
    input_layout_desc.attributes[0].slot = 0;
    input_layout_desc.attributes[0].name = "POSITION";
    input_layout_desc.attributes[0].index = 0;
    input_layout_desc.attributes[0].format = GALA_FORMAT_XY_F32;
    input_layout_desc.attributes[0].stride = sizeof(Vertex);
    input_layout_desc.attributes[0].rate = 0;

    input_layout_desc.attributes[1].slot = 0;
    input_layout_desc.attributes[1].name = "COLOR";
    input_layout_desc.attributes[1].index = 1;
    input_layout_desc.attributes[1].format = GALA_FORMAT_XYZW_UN8;
    input_layout_desc.attributes[1].stride = sizeof(Vertex);
    input_layout_desc.attributes[1].rate = 0;

    input_layout = gala_input_layout_create(engine, &cmds, &input_layout_desc);

    // TODO(mtwilliams): Move to `gala_buffer_desc_t`.
    vertex_buffers[0] = gala_buffer_create(engine, &cmds,
                                       GALA_IMMUTABLE,
                                       GALA_VERTEX_BUFFER,
                                       sizeof(VERTICES[0]),
                                       (const void *)&VERTICES[0][0]);

    vertex_buffers[1] = gala_buffer_create(engine, &cmds,
                                           GALA_IMMUTABLE,
                                           GALA_VERTEX_BUFFER,
                                           sizeof(VERTICES[1]),
                                           (const void *)&VERTICES[1][0]);

    engine->execute(engine, &cmds);
  }

  while (!complete) {
    gala_command_buffer_t cmds = command_buffer();

    gala_start_of_frame(&cmds);

    gala_set_viewport(&cmds, 0, 0, 1280, 720);
    gala_set_scissor(&cmds, 0, 0, 1280, 720);

    gala_set_pipeline(&cmds, pipeline);

    gala_set_shaders(&cmds, vertex_shader, pixel_shader);

    gala_set_input_layout(&cmds, input_layout);

    gala_set_topology(&cmds, GALA_TRIANGLES);

    gala_set_render_and_depth_stencil_targets(&cmds, 1, &render_target_view, GALA_INVALID_DEPTH_STENCIL_TARGET_VIEW_HANDLE);
    gala_clear_render_targets(&cmds, 0.5f, 0.5f, 0.5f, 1.0f);

    {
      gala_draw_t draw;
      draw.indicies = GALA_INVALID_BUFFER_HANDLE;
      draw.vertices = vertex_buffers[0];
      draw.constants[0] = GALA_INVALID_BUFFER_HANDLE;
      draw.constants[1] = GALA_INVALID_BUFFER_HANDLE;
      draw.constants[2] = GALA_INVALID_BUFFER_HANDLE;
      draw.constants[3] = GALA_INVALID_BUFFER_HANDLE;
      draw.constants[4] = GALA_INVALID_BUFFER_HANDLE;
      draw.constants[5] = GALA_INVALID_BUFFER_HANDLE;
      draw.constants[6] = GALA_INVALID_BUFFER_HANDLE;
      draw.constants[7] = GALA_INVALID_BUFFER_HANDLE;
      draw.first = 0;
      draw.count = sizeof(VERTICES[0]) / sizeof(Vertex);

      gala_draw(&cmds, &draw);
    }

    {
      gala_draw_t draw;
      draw.indicies = GALA_INVALID_BUFFER_HANDLE;
      draw.vertices = vertex_buffers[1];
      draw.constants[0] = GALA_INVALID_BUFFER_HANDLE;
      draw.constants[1] = GALA_INVALID_BUFFER_HANDLE;
      draw.constants[2] = GALA_INVALID_BUFFER_HANDLE;
      draw.constants[3] = GALA_INVALID_BUFFER_HANDLE;
      draw.constants[4] = GALA_INVALID_BUFFER_HANDLE;
      draw.constants[5] = GALA_INVALID_BUFFER_HANDLE;
      draw.constants[6] = GALA_INVALID_BUFFER_HANDLE;
      draw.constants[7] = GALA_INVALID_BUFFER_HANDLE;
      draw.first = 0;
      draw.count = sizeof(VERTICES[1]) / sizeof(Vertex);

      gala_draw(&cmds, &draw);
    }

    gala_present(&cmds, swap_chain);

    gala_end_of_frame(&cmds, NULL);

    engine->execute(engine, &cmds);

    surface->update(&on_surface_event);
  }

  {
    gala_command_buffer_t cmds = command_buffer();

    gala_input_layout_destroy(engine, &cmds, input_layout);

    gala_shader_destroy(engine, &cmds, pixel_shader);
    gala_shader_destroy(engine, &cmds, vertex_shader);

    gala_pipeline_destroy(engine, &cmds, pipeline);

    gala_render_target_view_destroy(engine, &cmds, render_target_view);
    gala_swap_chain_destroy(engine, &cmds, swap_chain);
    
    engine->execute(engine, &cmds);
  }

  surface->destroy();
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

} // end_to_end_tests
} // test
} // gala
