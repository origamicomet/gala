////////////////////////////////////////////////////////////////////////////////
//
// This file is part of the Abstract Graphics Library.
//
// Copyright (c) 2012, bitbyte studios
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// 
////////////////////////////////////////////////////////////////////////////////

#include <samples/framework.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct SimpleVertex {
    float x, y, z;
} SimpleVertex;

static const SimpleVertex cube_vertices[] = {
    { -1.0f,  1.0f,  0.0f },
    { -1.0f, -1.0f,  0.0f },
    {  1.0f, -1.0f,  0.0f }
};

static aglVertexBuffer* cube_vb = NULL;

static const aglRasterizerDesc simple_rs_desc = {
    AGL_FILL_SOLID,
    AGL_CULL_BACK,
    AGL_COUNTER_CLOCKWISE,
    FALSE,
    AGL_RESERVED
};

static const aglBlendDesc simple_bs_desc = {
    TRUE,
    AGL_RESERVED,
    AGL_BLEND_ONE,
    AGL_BLEND_ZERO,
    AGL_BLEND_OP_ADD,
    AGL_BLEND_ONE,
    AGL_BLEND_ZERO,
    AGL_BLEND_OP_ADD
};

static const aglDepthStencilDesc simple_ds_desc = {
    TRUE,
    TRUE,
    FALSE,
    AGL_RESERVED,
    AGL_COMPARISON_LESS,
    { AGL_STENCIL_OP_KEEP, AGL_STENCIL_OP_KEEP, AGL_STENCIL_OP_KEEP, AGL_COMPARISON_ALWAYS },
    { AGL_STENCIL_OP_KEEP, AGL_STENCIL_OP_KEEP, AGL_STENCIL_OP_KEEP, AGL_COMPARISON_ALWAYS }
};

static const aglInputElementDesc simple_ia_desc[] = {
    { 0, AGL_IE_FLOAT, 3, AGL_IE_DONT_NORMALIZE, 0, 0, sizeof(SimpleVertex), offsetof(SimpleVertex, x) }
};

static aglRasterizerState*   simple_rs  = NULL;
static aglBlendState*        simple_bs  = NULL;
static aglDepthStencilState* simple_dss = NULL;
static aglInputLayout*       simple_ia  = NULL;
static aglVertexShader*      simple_vs  = NULL;
static aglPixelShader*       simple_ps  = NULL;

int main( int argc, char** argv )
{
    fwEvent event;
    aglContext* context;

    aglClearCommand clear_cmd;
    aglSwapCommand  swap_cmd;
    aglDrawCommand  draw_cmd;

    AGL_INIT_CMD(Clear, clear_cmd);
    AGL_INIT_CMD(Swap, swap_cmd);
    AGL_INIT_CMD(Draw, draw_cmd);

    if( !fwInitialize(800, 600, "cube") ) exit(EXIT_FAILURE);
    context = fwGetContext();

    cube_vb = aglCreateVertexBuffer(AGL_USAGE_IMMUTABLE, AGL_CPU_ACCESS_WRITE, sizeof(cube_vertices), (const void*)&cube_vertices[0]);
    if( !cube_vb ) exit(EXIT_FAILURE);

    simple_rs = aglCreateRasterizerState(&simple_rs_desc);
    if( !simple_rs ) exit(EXIT_FAILURE);

    simple_bs = aglCreateBlendState(&simple_bs_desc);
    if( !simple_bs ) exit(EXIT_FAILURE);

    simple_dss = aglCreateDepthStencilState(&simple_ds_desc);
    if( !simple_dss ) exit(EXIT_FAILURE);

    simple_ia = aglCreateInputLayout(1, &simple_ia_desc[0]);
    if( !simple_ia ) exit(EXIT_FAILURE);

    simple_vs = fwCreateVertexShaderFromFile("data/cube/simple.opengl.vsc");
    if( !simple_vs ) exit(EXIT_FAILURE);

    simple_ps = fwCreatePixelShaderFromFile("data/cube/simple.opengl.psc");
    if( !simple_ps ) exit(EXIT_FAILURE);

    clear_cmd.bits     = AGL_CLEAR_COLOR | AGL_CLEAR_DEPTH;
    clear_cmd.color[0] =  53.0f / 255.0f;
    clear_cmd.color[1] = 191.0f / 255.0f;
    clear_cmd.color[2] = 239.0f / 255.0f;
    clear_cmd.color[3] = 255.0f / 255.0f;
    clear_cmd.depth    = 1.0f;

    draw_cmd.rasterizer_state         = simple_rs;
    draw_cmd.blend_state              = simple_bs;
    draw_cmd.depth_stencil_state      = simple_dss;
    draw_cmd.stencil_ref              = 0;
    draw_cmd.input_layout             = simple_ia;
    draw_cmd.primitive_topology       = AGL_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    draw_cmd.vertex_shader            = simple_vs;
    draw_cmd.pixel_shader             = simple_ps;
    draw_cmd.textures[0]              = NULL;
    draw_cmd.textures[1]              = NULL;
    draw_cmd.textures[2]              = NULL;
    draw_cmd.textures[3]              = NULL;
    draw_cmd.index_type               = AGL_INDEX_UINT16;
    draw_cmd.index_buffer             = NULL;
    draw_cmd.vertex_buffers[0]        = cube_vb;
    draw_cmd.vs_constant_buffers[0]   = NULL;
    draw_cmd.vs_constant_buffers[1]   = NULL;
    draw_cmd.vs_constant_buffers[2]   = NULL;
    draw_cmd.vs_constant_buffers[3]   = NULL;
    draw_cmd.ps_constant_buffers[0]   = NULL;
    draw_cmd.ps_constant_buffers[1]   = NULL;
    draw_cmd.ps_constant_buffers[2]   = NULL;
    draw_cmd.ps_constant_buffers[3]   = NULL;
    draw_cmd.draw_type                = AGL_DRAW;
    draw_cmd.params.draw.start_vertex = 0;
    draw_cmd.params.draw.num_vertices = 3;

    while( TRUE )
    {
        while( fwGetNextEvent(&event) )
        {
            switch( event.type )
            {
                case FW_CLOSE_EVENT: goto exit; break;
            }
        }

        aglExecuteCommands(1, (aglCommand*)&clear_cmd);
        aglExecuteCommands(1, (aglCommand*)&draw_cmd);
        aglExecuteCommands(1, (aglCommand*)&swap_cmd);
    }

exit:
    fwDeinitialize();
    return EXIT_SUCCESS;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */