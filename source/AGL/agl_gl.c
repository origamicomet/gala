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

#include <AGL/agl.h>

#include <stdlib.h>
#include <assert.h>

extern aglAllocCallback aglAlloc;
extern aglFreeCallback  aglFree;

#include <GL/glew.h>

#if defined(_WIN32)
    #include "win_gl.incl"
#elif defined(__linux__)
    #include "xlib_gl.incl"
#elif defined(__APPLE__) && defined(__MACH__)
    #include "ns_gl.incl"
#else
    #error Not supported.
#endif

////////////////////////////////////////////////////////////////////////////////

typedef struct aglInputLayoutAttrib {
    GLuint        index;
    GLint         num_components;
    GLenum        type;
    GLboolean     normalized;
    GLsizei       stride;
    const GLvoid* offset;
    uint32_t      slot;
    GLuint        divisor;
} aglInputLayoutAttrib;

struct aglInputLayout {
    size_t num_attribs;
    aglInputLayoutAttrib* attribs;
} aglInputLayout;

aglInputLayout* AGL_API aglCreateInputLayout( const size_t num_descs, const aglInputElementDesc* descs )
{
    aglInputLayout* input_layout = NULL;

    assert(num_descs);
    assert(descs);

    input_layout = (aglInputLayout*)aglAlloc(sizeof(aglInputLayout) + sizeof(aglInputLayoutAttrib) * num_descs);
    input_layout->num_attribs = num_descs;
    input_layout->attribs     = (aglInputLayoutAttrib*)(input_layout + sizeof(aglInputLayout));

    for( uint32_t i = 0; i < num_descs; ++i ) {
        aglInputLayoutAttrib* attrib = &input_layout->attribs[i];
        attrib->index          = (GLuint)descs[i].attrib_index;
        attrib->num_components = (GLint)descs[i].num_components;

        switch( descs[i].element_type ) {
            case AGL_IE_FLOAT:  attrib->type = GL_FLOAT; break;
            case AGL_IE_DOUBLE: attrib->type = GL_DOUBLE; break;
            case AGL_IE_INT8:   attrib->type = GL_BYTE; break;
            case AGL_IE_UINT8:  attrib->type = GL_UNSIGNED_BYTE; break;
            case AGL_IE_INT16:  attrib->type = GL_SHORT; break;
            case AGL_IE_UINT16: attrib->type = GL_UNSIGNED_SHORT; break;
            case AGL_IE_INT32:  attrib->type = GL_INT; break;
            case AGL_IE_UINT32: attrib->type = GL_UNSIGNED_INT; break;
        }

        attrib->normalized = (descs[i].normalize == AGL_IE_NORMALIZE) ? GL_TRUE : GL_FALSE;
        attrib->stride     = descs[i].stride;
        attrib->offset     = (const GLvoid*)descs[i].offset;
        attrib->slot       = descs[i].slot;
        attrib->divisor    = (GLuint)descs[i].step_rate;
    }

    return input_layout;
}

void AGL_API aglDestroyInputLayout( aglInputLayout* input_layout )
{
    assert(input_layout);
    aglFree(input_layout);
}

////////////////////////////////////////////////////////////////////////////////

struct aglRasterizerState {
    GLenum    fill_mode;
    GLboolean cull;
    GLenum    cull_face;
    GLenum    front_face;
    GLboolean scissor;
};

aglRasterizerState* AGL_API aglCreateRasterizerState( const aglRasterizerDesc* desc )
{
    aglRasterizerState* rasterizer_state = NULL;
    assert(desc);

    rasterizer_state = (aglRasterizerState*)aglAlloc(sizeof(aglRasterizerState));

    switch( desc->fill_mode ) {
        case AGL_FILL_WIREFRAME: rasterizer_state->fill_mode = GL_LINE; break;
        case AGL_FILL_SOLID: rasterizer_state->fill_mode = GL_FILL; break;
    }

    rasterizer_state->cull = GL_TRUE;
    switch( desc->cull_mode ) {
        case AGL_CULL_NONE:  rasterizer_state->cull = GL_FALSE; break;
        case AGL_CULL_FRONT: rasterizer_state->cull_face = GL_FRONT; break;
        case AGL_CULL_BACK:  rasterizer_state->cull_face = GL_BACK;  break;
    }

    switch( desc->front_face ) {
        case AGL_CLOCKWISE: rasterizer_state->front_face = GL_CW; break;
        case AGL_COUNTER_CLOCKWISE: rasterizer_state->front_face = GL_CCW; break;
    }

    rasterizer_state->scissor = (desc->enable_scissor ? GL_TRUE : GL_FALSE);

    return rasterizer_state;
}

void AGL_API aglDestroyRasterizerState( aglRasterizerState* rasterizer_state )
{
    assert(rasterizer_state);
    aglFree(rasterizer_state);
}

struct aglBlendState {
    GLboolean blend;
    GLenum    src_rgb;
    GLenum    dst_rgb;
    GLenum    src_alpha;
    GLenum    dst_alpha;
    GLenum    mode_rgb;
    GLenum    mode_alpha;
};

static GLenum aglBlendToOpenGL( AGL_BLEND blend ) {
    switch( blend ) {
        case AGL_BLEND_ZERO: return GL_ZERO; break;
        case AGL_BLEND_ONE:  return GL_ONE; break;
        case AGL_BLEND_SRC_COLOR: return GL_SRC_COLOR; break;
        case AGL_BLEND_INV_SRC_COLOR: return GL_ONE_MINUS_SRC_COLOR; break;
        case AGL_BLEND_SRC_ALPHA: return GL_SRC_ALPHA; break;
        case AGL_BLEND_INV_SRC_ALPHA: return GL_ONE_MINUS_SRC_ALPHA; break;
        case AGL_BLEND_DEST_ALPHA: return GL_DST_ALPHA; break;
        case AGL_BLEND_INV_DEST_ALPHA: return GL_ONE_MINUS_DST_ALPHA; break;
        case AGL_BLEND_DEST_COLOR: return GL_DST_COLOR; break;
        case AGL_BLEND_INV_DEST_COLOR: return GL_ONE_MINUS_DST_COLOR; break;
        case AGL_BLEND_SRC_ALPHA_SAT: return GL_SRC_ALPHA_SATURATE; break;
        case AGL_BLEND_BLEND_FACTOR: return GL_CONSTANT_COLOR; break;
        case AGL_BLEND_INV_BLEND_FACTOR: return GL_ONE_MINUS_CONSTANT_COLOR; break;
    }   
}

static GLenum aglBlendOpToOpenGL( AGL_BLEND_OP blend_op ) {
    switch( blend_op ) {
        case AGL_BLEND_OP_ADD: return GL_FUNC_ADD; break;
        case AGL_BLEND_OP_SUBTRACT: return GL_FUNC_SUBTRACT; break;
        case AGL_BLEND_OP_REV_SUBTRACT: return GL_FUNC_REVERSE_SUBTRACT; break;
        case AGL_BLEND_OP_MIN: return GL_MIN; break;
        case AGL_BLEND_OP_MAX: return GL_MAX; break;
    }
}

aglBlendState* AGL_API aglCreateBlendState( const aglBlendDesc* desc )
{
    aglBlendState* blend_state = NULL;
    assert(desc);

    blend_state = (aglBlendState*)aglAlloc(sizeof(aglBlendState));
    blend_state->blend      = desc->enable_blend ? GL_TRUE : GL_FALSE;
    blend_state->src_rgb    = aglBlendToOpenGL(desc->src_blend);
    blend_state->dst_rgb    = aglBlendToOpenGL(desc->dest_blend);
    blend_state->src_alpha  = aglBlendToOpenGL(desc->src_blend_alpha);
    blend_state->dst_alpha  = aglBlendToOpenGL(desc->dest_blend_alpha);
    blend_state->mode_rgb   = aglBlendOpToOpenGL(desc->blend_op);
    blend_state->mode_alpha = aglBlendOpToOpenGL(desc->blend_op_alpha);
    return blend_state;
}

void AGL_API aglDestroyBlendState( aglBlendState* blend_state )
{
    assert(blend_state);
    aglFree(blend_state);
}

struct aglDepthStencilOp {
    GLenum sfail;
    GLenum dpfail;
    GLenum dppass;
    GLenum func;
};

struct aglDepthStencilState {
    GLboolean depth_test;
    GLboolean depth_mask;
    GLboolean stencil_test;
    GLenum    depth_func;
    aglDepthStencilOp front_face;
    aglDepthStencilOp back_face;
};

aglDepthStencilState* AGL_API aglCreateDepthStencilState( const aglDepthStencilDesc* desc )
{
}

void AGL_API aglDestroyDepthstencilState( aglDepthStencilState* depth_stencil_state )
{
}