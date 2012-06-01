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
#include <stdio.h>
#include <assert.h>

#include <GL/glew.h>
#include <Cg/cg.h>
#include <Cg/cgGL.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern aglAllocCallback aglAlloc;
extern aglFreeCallback  aglFree;

#if defined(AGL_PLATFORM_WINDOWS)
    #include "win_gl.incl"
#elif defined(AGL_PLATFORM_LINUX)
    #include "xlib_gl.incl"
#elif defined(AGL_PLATFORM_OSX)
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
};

aglInputLayout* AGL_API aglCreateInputLayout( const size_t num_descs, const aglInputElementDesc* descs )
{
    uint32_t i;
    aglInputLayout* input_layout = NULL;
    aglInputLayoutAttrib* attrib = NULL;

    assert(num_descs);
    assert(descs);

    input_layout = (aglInputLayout*)aglAlloc(sizeof(aglInputLayout));
    input_layout->num_attribs = num_descs;
    input_layout->attribs     = (aglInputLayoutAttrib*)aglAlloc(sizeof(aglInputLayoutAttrib) * num_descs);

    for( i = 0; i < num_descs; ++i )
    {
        input_layout->attribs[i].index          = (GLuint)descs[i].attrib_index;
        input_layout->attribs[i].num_components = (GLint)descs[i].num_components;

        switch( descs[i].element_type )
        {
            case AGL_IE_FLOAT:  input_layout->attribs[i].type = GL_FLOAT; break;
            case AGL_IE_DOUBLE: input_layout->attribs[i].type = GL_DOUBLE; break;
            case AGL_IE_INT8:   input_layout->attribs[i].type = GL_BYTE; break;
            case AGL_IE_UINT8:  input_layout->attribs[i].type = GL_UNSIGNED_BYTE; break;
            case AGL_IE_INT16:  input_layout->attribs[i].type = GL_SHORT; break;
            case AGL_IE_UINT16: input_layout->attribs[i].type = GL_UNSIGNED_SHORT; break;
            case AGL_IE_INT32:  input_layout->attribs[i].type = GL_INT; break;
            case AGL_IE_UINT32: input_layout->attribs[i].type = GL_UNSIGNED_INT; break;
        }

        input_layout->attribs[i].normalized = (descs[i].normalize == AGL_IE_NORMALIZE) ? GL_TRUE : GL_FALSE;
        input_layout->attribs[i].stride     = descs[i].stride;
        input_layout->attribs[i].offset     = (const GLvoid*)descs[i].offset;
        input_layout->attribs[i].slot       = descs[i].slot;
        input_layout->attribs[i].divisor    = (GLuint)descs[i].step_rate;
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

static GLenum aglBlendToOpenGL( AGL_BLEND blend )
{
    switch( blend )
    {
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

static GLenum aglBlendOpToOpenGL( AGL_BLEND_OP blend_op )
{
    switch( blend_op )
    {
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

typedef struct aglDepthStencilOp {
    GLenum sfail;
    GLenum dpfail;
    GLenum dppass;
    GLenum func;
} aglDepthStencilOp;

struct aglDepthStencilState {
    GLboolean depth_test;
    GLboolean depth_mask;
    GLboolean stencil_test;
    GLenum    depth_func;
    aglDepthStencilOp front_face;
    aglDepthStencilOp back_face;
};

static GLenum aglComparisonFuncToOpenGL( AGL_COMPARISON_FUNC cmp_func )
{
    switch( cmp_func )
    {
        case AGL_COMPARISON_NEVER: return GL_NEVER; break;
        case AGL_COMPARISON_LESS: return GL_LESS; break;
        case AGL_COMPARISON_EQUAL: return GL_EQUAL; break;
        case AGL_COMPARISON_LESS_EQUAL: return GL_LEQUAL; break;
        case AGL_COMPARISON_GREATER: return GL_GREATER; break;
        case AGL_COMPARISON_NOT_EQUAL: return GL_NOTEQUAL; break;
        case AGL_COMPARISON_GREATER_EQUAL: return GL_GEQUAL; break;
        case AGL_COMPARISON_ALWAYS: return GL_ALWAYS; break;
    }
}

static GLenum aglStencilOpToOpenGL( AGL_STENCIL_OP stencil_op )
{
    switch( stencil_op )
    {
        case AGL_STENCIL_OP_KEEP: return GL_KEEP; break;
        case AGL_STENCIL_OP_ZERO: return GL_ZERO; break;
        case AGL_STENCIL_OP_REPLACE: return GL_REPLACE; break;
        case AGL_STENCIL_OP_INCR_SAT: return GL_INCR; break;
        case AGL_STENCIL_OP_DECR_SAT: return GL_DECR; break;
        case AGL_STENCIL_OP_INVERT: return GL_INVERT; break;
        case AGL_STENCIL_OP_INCR: return GL_INCR_WRAP; break;
        case AGL_STENCIL_OP_DECR: return GL_DECR_WRAP; break;
    }
}

aglDepthStencilState* AGL_API aglCreateDepthStencilState( const aglDepthStencilDesc* desc )
{
    aglDepthStencilState* depth_stencil_state = NULL;
    assert(desc);

    depth_stencil_state = (aglDepthStencilState*)aglAlloc(sizeof(aglDepthStencilState));
    depth_stencil_state->depth_test   = desc->enable_depth_test ? GL_TRUE : GL_FALSE;
    depth_stencil_state->depth_mask   = desc->enable_depth_write ? GL_TRUE : GL_FALSE;
    depth_stencil_state->stencil_test = desc->enable_stencil_test ? GL_TRUE : GL_FALSE;
    depth_stencil_state->front_face.sfail  = aglStencilOpToOpenGL(desc->front_face.stencil_fail);
    depth_stencil_state->front_face.dpfail = aglStencilOpToOpenGL(desc->front_face.stencil_depth_fail);
    depth_stencil_state->front_face.dppass = aglStencilOpToOpenGL(desc->front_face.stencil_pass);
    depth_stencil_state->front_face.func = aglComparisonFuncToOpenGL(desc->front_face.stencil_func);
    depth_stencil_state->back_face.sfail  = aglStencilOpToOpenGL(desc->front_face.stencil_fail);
    depth_stencil_state->back_face.dpfail = aglStencilOpToOpenGL(desc->front_face.stencil_depth_fail);
    depth_stencil_state->back_face.dppass = aglStencilOpToOpenGL(desc->front_face.stencil_pass);
    depth_stencil_state->back_face.func = aglComparisonFuncToOpenGL(desc->back_face.stencil_func);

    return depth_stencil_state;
}

void AGL_API aglDestroyDepthStencilState( aglDepthStencilState* depth_stencil_state )
{
    assert(depth_stencil_state);
    aglFree(depth_stencil_state);
}

////////////////////////////////////////////////////////////////////////////////

static GLenum aglUsageToOpenGL( AGL_USAGE usage )
{
    switch( usage )
    {
        case AGL_USAGE_DEFAULT: return GL_STATIC_DRAW; break;
        case AGL_USAGE_IMMUTABLE: return GL_STATIC_DRAW; break;
        case AGL_USAGE_DYNAMIC: return GL_DYNAMIC_DRAW; break;
        case AGL_USAGE_STAGING: return GL_DYNAMIC_READ; break;
    }
}

static GLenum aglMapToOpenGL( AGL_MAP map )
{
    switch( map )
    {
        case AGL_MAP_READ: return GL_READ_ONLY; break;
        case AGL_MAP_WRITE: return GL_WRITE_ONLY; break;
        case AGL_MAP_READ_WRITE: return GL_READ_WRITE; break;
    }
}

struct aglVertexBuffer {
    GLuint id;
    GLenum access;
};

aglVertexBuffer* AGL_API aglCreateVertexBuffer( AGL_USAGE usage, uint32_t access_flags, size_t num_bytes, const void* data )
{
    aglVertexBuffer* vertex_buffer = (aglVertexBuffer*)aglAlloc(sizeof(aglVertexBuffer));

    glGenBuffers(1, &vertex_buffer->id);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->id);
    glBufferData(GL_ARRAY_BUFFER, num_bytes, data, aglUsageToOpenGL(usage));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    switch( access_flags ) {
        case AGL_CPU_ACCESS_READ: vertex_buffer->access = GL_READ_ONLY; break;
        case AGL_CPU_ACCESS_WRITE: vertex_buffer->access = GL_WRITE_ONLY; break;
        case AGL_CPU_ACCESS_READ | AGL_CPU_ACCESS_WRITE: vertex_buffer->access = GL_READ_WRITE; break;
    }

    return vertex_buffer;
}

void AGL_API aglDestroyVertexBuffer( aglVertexBuffer* vertex_buffer )
{
    assert(vertex_buffer);
    glDeleteBuffers(1, &vertex_buffer->id);
}

void* AGL_API aglMapVertexBuffer( aglVertexBuffer* vertex_buffer, AGL_MAP map )
{
    assert(vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->id);
    return glMapBuffer(GL_ARRAY_BUFFER, aglMapToOpenGL(map));
}

void AGL_API aglUnmapVertexBuffer( aglVertexBuffer* vertex_buffer )
{
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->id);
    glUnmapBuffer(GL_ARRAY_BUFFER);
}

struct aglIndexBuffer {
    GLuint id;
    GLenum access;
};

aglIndexBuffer* AGL_API aglCreateIndexBuffer( AGL_USAGE usage, uint32_t access_flags, size_t num_bytes, const void* data )
{
    aglIndexBuffer* index_buffer = (aglIndexBuffer*)aglAlloc(sizeof(aglIndexBuffer));

    glGenBuffers(1, &index_buffer->id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer->id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_bytes, data, aglUsageToOpenGL(usage));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    switch( access_flags ) {
        case AGL_CPU_ACCESS_READ: index_buffer->access = GL_READ_ONLY; break;
        case AGL_CPU_ACCESS_WRITE: index_buffer->access = GL_WRITE_ONLY; break;
        case AGL_CPU_ACCESS_READ | AGL_CPU_ACCESS_WRITE: index_buffer->access = GL_READ_WRITE; break;
    }

    return index_buffer;
}

void AGL_API aglDestroyIndexBuffer( aglIndexBuffer* index_buffer )
{
    assert(index_buffer);
    glDeleteBuffers(1, &index_buffer->id);
}

void* AGL_API aglMapIndexBuffer( aglIndexBuffer* index_buffer, AGL_MAP map )
{
    assert(index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer->id);
    return glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, aglMapToOpenGL(map));
}

void AGL_API aglUnmapIndexBuffer( aglIndexBuffer* index_buffer )
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer->id);
    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
}

struct aglConstantBuffer {
    GLuint id;
    GLenum access;
    CGbuffer cg_buffer;
};

aglConstantBuffer* AGL_API aglCreateConstantBuffer( AGL_USAGE usage, uint32_t access_flags, size_t num_bytes, const void* data )
{
    aglContext* context = aglGetActiveContext();
    aglConstantBuffer* constant_buffer = (aglConstantBuffer*)aglAlloc(sizeof(aglConstantBuffer));

    glGenBuffers(1, &constant_buffer->id);
    glBindBuffer(GL_UNIFORM_BUFFER, constant_buffer->id);
    glBufferData(GL_UNIFORM_BUFFER, num_bytes, data, aglUsageToOpenGL(usage));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    switch( access_flags ) {
        case AGL_CPU_ACCESS_READ: constant_buffer->access = GL_READ_ONLY; break;
        case AGL_CPU_ACCESS_WRITE: constant_buffer->access = GL_WRITE_ONLY; break;
        case AGL_CPU_ACCESS_READ | AGL_CPU_ACCESS_WRITE: constant_buffer->access = GL_READ_WRITE; break;
    }

    constant_buffer->cg_buffer = cgGLCreateBufferFromObject(context->cg_context, constant_buffer->id, CG_FALSE);
}

void AGL_API aglDestroyConstantBuffer( aglConstantBuffer* constant_buffer )
{
    assert(constant_buffer);
}

void* AGL_API aglMapConstantBuffer( aglConstantBuffer* constant_buffer, AGL_MAP map )
{
    assert(constant_buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, constant_buffer->id);
    return glMapBuffer(GL_UNIFORM_BUFFER, aglMapToOpenGL(map));
}

void AGL_API aglUnmapConstantBuffer( aglConstantBuffer* constant_buffer )
{
    glBindBuffer(GL_UNIFORM_BUFFER, constant_buffer->id);
    glUnmapBuffer(GL_UNIFORM_BUFFER);
}

////////////////////////////////////////////////////////////////////////////////

struct aglTexture {
    GLuint id;
    GLenum target;
    GLenum format;
    GLenum type;
};

static void aglTextureFormatToOpenGL( AGL_TEXTURE_FORMAT texture_format, GLenum* internal_format, GLenum* format, GLenum* type )
{
    switch( texture_format )
    {
        case AGL_TEXTURE_R8G8B8: *internal_format = GL_RGB8; *format = GL_RGB; *type = GL_UNSIGNED_BYTE; break;
        case AGL_TEXTURE_R8G8B8A8: *internal_format = GL_RGBA8; *format = GL_RGBA; *type = GL_UNSIGNED_BYTE; break;
        case AGL_TEXTURE_R8G8B8A8_SRGB: *internal_format = GL_SRGB8_ALPHA8; *format = GL_RGBA; *type = GL_UNSIGNED_BYTE; break;
        case AGL_TEXTURE_R16G16B16A16F: *internal_format = GL_RGBA16F; *format = GL_RGBA; *type = GL_FLOAT; break;
        case AGL_TEXTURE_D24S8: *internal_format = GL_DEPTH24_STENCIL8; *format = GL_DEPTH_STENCIL; *type = GL_UNSIGNED_INT_24_8; break;
    }
}

// TODO: Use render buffers when !bind_shader_resource
aglTexture* AGL_API aglCreateTexture2D( const aglTextureDesc2D* desc, const void* data )
{
    GLenum internal_format;
    GLenum format;
    GLenum type;

    aglTexture* texture = NULL;
    assert(desc);
    assert((desc->width > 0) && (desc->height > 0));

    texture = (aglTexture*)aglAlloc(sizeof(aglTexture));
    glGenTextures(1, &texture->id);
    texture->target = GL_TEXTURE_2D;

    aglTextureFormatToOpenGL(desc->format, &internal_format, &format, &type);
    texture->format = format;
    texture->type = type;

    glBindTexture(texture->target, texture->id);
    glTexImage2D(texture->target, 0, internal_format, desc->width, desc->height, 0, format, type, data);

    return texture;
}

void AGL_API aglDestroyTexture( aglTexture* texture )
{
    assert(texture);
    glDeleteTextures(1, &texture->id);
}

// TRAP: http://www.opengl.org/wiki/Floating_point_and_mipmapping_and_filtering
void AGL_API aglGenerateMips( aglTexture* texture )
{
    glBindTexture(texture->target, texture->id);
    glGenerateMipmap(texture->target);
}

void AGL_API aglUpdateTexture2D( aglTexture* texture, const aglBox* box, uint32_t mipmap, const void* data )
{
    assert(texture);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexSubImage2D(GL_TEXTURE_2D, mipmap, box->left, box->right, (box->right - box->left), (box->bottom - box->top), texture->format, texture->type, data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

////////////////////////////////////////////////////////////////////////////////

struct aglRenderTarget {
    GLuint id;
    aglTexture* depth_stencil;
    aglTexture* color[4];
};

aglRenderTarget* aglCreateRenderTarget( const aglRenderTargetDesc* desc )
{
    aglRenderTarget* render_target = NULL;
    assert(desc);

    render_target = (aglRenderTarget*)aglAlloc(sizeof(aglRenderTarget));
    glGenFramebuffers(1, &render_target->id);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, render_target->id);
    render_target->depth_stencil = desc->depth_stencil;
    render_target->color[0] = desc->color[0];
    render_target->color[1] = desc->color[1];
    render_target->color[2] = desc->color[2];
    render_target->color[3] = desc->color[3];
    if( desc->depth_stencil ) glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, desc->depth_stencil->id, 0);
    if( desc->color[0] ) glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, desc->color[0]->id, 0);
    if( desc->color[1] ) glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, desc->color[1]->id, 0);
    if( desc->color[2] ) glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, desc->color[2]->id, 0);
    if( desc->color[3] ) glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, desc->color[3]->id, 0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    return render_target;
}

void aglDestroyRenderTarget( aglRenderTarget* render_target )
{
    assert(render_target);
    glDeleteFramebuffers(1, &render_target->id);
    aglFree(render_target);
}

////////////////////////////////////////////////////////////////////////////////

struct aglVertexShader {
    CGprogram cg_program;
};

struct aglPixelShader {
    CGprogram cg_program;
};

aglVertexShader* AGL_API aglCreateVertexShader( const char* objcode )
{
    aglContext* context = aglGetActiveContext();
    aglVertexShader* vertex_shader = NULL;
    CGprogram cg_program;
    assert(objcode);

    cg_program = cgCreateProgram(context->cg_context, CG_OBJECT, objcode, context->cg_vs_profile, "vs_main", NULL);
    if( !cg_program ) return NULL;
    cgGLLoadProgram(cg_program);

    vertex_shader = (aglVertexShader*)aglAlloc(sizeof(aglVertexShader));
    vertex_shader->cg_program   = cg_program;
    return vertex_shader;
}

void AGL_API aglDestroyVertexShader( aglVertexShader* vertex_shader )
{
    assert(vertex_shader);
    cgDestroyProgram(vertex_shader->cg_program);
}

aglPixelShader* AGL_API aglCreatePixelShader( const char* objcode )
{
    aglContext* context = aglGetActiveContext();
    aglPixelShader* pixel_shader = NULL;
    CGprogram cg_program;
    assert(objcode);

    cg_program = cgCreateProgram(context->cg_context, CG_OBJECT, objcode, context->cg_ps_profile, "ps_main", NULL);
    if( !cg_program ) return NULL;
    cgGLLoadProgram(cg_program);

    pixel_shader = (aglPixelShader*)aglAlloc(sizeof(aglPixelShader));
    pixel_shader->cg_program   = cg_program;
    return pixel_shader;
}

void AGL_API aglDestroyPixelShader( aglPixelShader* pixel_shader )
{
    assert(pixel_shader);
    cgDestroyProgram(pixel_shader->cg_program);
}

////////////////////////////////////////////////////////////////////////////////

static aglRenderTarget* current_rt = NULL;

static GLuint aglClearBitsToOpenGL( AGL_CLEAR_BITS clear_bits )
{
    switch( clear_bits )
    {
        case AGL_CLEAR_COLOR: return GL_COLOR_BUFFER_BIT;
        case AGL_CLEAR_DEPTH: return GL_DEPTH_BUFFER_BIT;
        case AGL_CLEAR_STENCIL: return GL_STENCIL_BUFFER_BIT;
        case AGL_CLEAR_COLOR | AGL_CLEAR_DEPTH: return GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
        case AGL_CLEAR_COLOR | AGL_CLEAR_STENCIL: return GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
        case AGL_CLEAR_COLOR | AGL_CLEAR_DEPTH | AGL_CLEAR_STENCIL: return GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
        case AGL_CLEAR_DEPTH | AGL_CLEAR_STENCIL: return GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
    }
}

static GLenum aglPrimTopologyToOpenGL( AGL_PRIMITIVE_TOPOLOGY prim_topology )
{
    switch( prim_topology )
    {
        case AGL_PRIMITIVE_TOPOLOGY_POINTLIST: return GL_POINTS; break;
        case AGL_PRIMITIVE_TOPOLOGY_LINELIST: return GL_LINES; break;
        case AGL_PRIMITIVE_TOPOLOGY_LINESTRIP: return GL_LINE_STRIP; break;
        case AGL_PRIMITIVE_TOPOLOGY_TRIANGLELIST: return GL_TRIANGLES; break;
        case AGL_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP: return GL_TRIANGLE_STRIP; break;
        case AGL_PRIMITIVE_TOPOLOGY_LINELIST_ADJ: return GL_LINES_ADJACENCY; break;
        case AGL_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ: return GL_LINE_STRIP_ADJACENCY; break;
        case AGL_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ: return GL_TRIANGLES_ADJACENCY; break;
        case AGL_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ: return GL_TRIANGLE_STRIP_ADJACENCY; break;
    }
}

static GLenum aglIndexTypeToOpenGL( AGL_INDEX_TYPE index_type )
{
    switch( index_type )
    {
        case AGL_INDEX_UINT16: return GL_UNSIGNED_SHORT; break;
        case AGL_INDEX_UINT32: return GL_UNSIGNED_INT; break;
    }
}

static void aglExecuteClearCommand( aglCommand* cmd )
{
    aglClearCommand* clear_cmd = (aglClearCommand*)cmd;

    if( clear_cmd->bits & AGL_CLEAR_COLOR   ) glClearColor(clear_cmd->color[0], clear_cmd->color[1], clear_cmd->color[2], clear_cmd->color[3]);
    if( clear_cmd->bits & AGL_CLEAR_DEPTH   ) glClearDepth(clear_cmd->depth);
    if( clear_cmd->bits & AGL_CLEAR_STENCIL ) glClearStencil(clear_cmd->stencil);

    glDrawBuffer(GL_COLOR_ATTACHMENT0 + clear_cmd->buffer);
    glClear(aglClearBitsToOpenGL(clear_cmd->bits));
}

static void aglExecuteSwapCommand( aglCommand* cmd )
{
    aglSwapCommand* swap_cmd = (aglSwapCommand*)cmd;
    aglSwapBuffers();
}

static void aglExecuteDrawCommand( aglCommand* cmd )
{
    uint32_t i;
    char cbuffer_name[9] = { 0, };
    aglDrawCommand* draw_cmd = (aglDrawCommand*)cmd;
    aglContext* context = aglGetActiveContext();

    // rasterizer_state:
    glPolygonMode(GL_FRONT_AND_BACK, draw_cmd->rasterizer_state->fill_mode);
    if( draw_cmd->rasterizer_state->cull ) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
    glCullFace(draw_cmd->rasterizer_state->cull_face);
    glFrontFace(draw_cmd->rasterizer_state->front_face);
    if( draw_cmd->rasterizer_state->scissor ) glEnable(GL_SCISSOR_TEST); else glDisable(GL_SCISSOR_TEST);

    // blend_state:
    if( draw_cmd->blend_state->blend ) glEnable(GL_BLEND); else glDisable(GL_BLEND);
    glBlendFuncSeparate(draw_cmd->blend_state->src_rgb, draw_cmd->blend_state->dst_rgb, draw_cmd->blend_state->src_alpha, draw_cmd->blend_state->dst_alpha);
    glBlendEquationSeparate(draw_cmd->blend_state->mode_rgb, draw_cmd->blend_state->mode_alpha);

    // depth_stencil_state:
    if( draw_cmd->depth_stencil_state->depth_test ) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
    glDepthMask(draw_cmd->depth_stencil_state->depth_mask);
    if( draw_cmd->depth_stencil_state->stencil_test ) glEnable(GL_STENCIL_TEST); else glDisable(GL_STENCIL_TEST);
    glDepthFunc(draw_cmd->depth_stencil_state->depth_func);

    glStencilOpSeparate(GL_FRONT, draw_cmd->depth_stencil_state->front_face.sfail, draw_cmd->depth_stencil_state->front_face.dpfail, draw_cmd->depth_stencil_state->front_face.dppass);
    glStencilFuncSeparate(GL_FRONT, draw_cmd->depth_stencil_state->front_face.func, draw_cmd->stencil_ref, 0xFFFFFFFF);
    
    glStencilOpSeparate(GL_BACK, draw_cmd->depth_stencil_state->back_face.sfail, draw_cmd->depth_stencil_state->back_face.dpfail, draw_cmd->depth_stencil_state->back_face.dppass);
    glStencilFuncSeparate(GL_BACK, draw_cmd->depth_stencil_state->back_face.func, draw_cmd->stencil_ref, 0xFFFFFFFF);

    // input_layout:
    for( i = 0; i < draw_cmd->input_layout->num_attribs; ++i )
    {
        aglInputLayoutAttrib* attrib = &draw_cmd->input_layout->attribs[i];
        glEnableVertexAttribArray(attrib->index);
        glBindBuffer(GL_ARRAY_BUFFER, draw_cmd->vertex_buffers[attrib->slot]->id);
        glVertexAttribPointer(attrib->index, attrib->num_components, attrib->type, attrib->normalized, attrib->stride, attrib->offset);
        glVertexAttribDivisor(attrib->index, attrib->divisor);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // index_buffer:
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, draw_cmd->index_buffer ? draw_cmd->index_buffer->id : 0);

    // textures:
    for( i = 0; i < 4; ++i )
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, draw_cmd->textures[i] ? draw_cmd->textures[i]->id : 0);
    }

    // vs_constant_buffers:
    for( i = 0; i < 4; ++i ) {
        if( !draw_cmd->vs_constant_buffers[i] ) continue;
        sprintf(&cbuffer_name[0], "cbuffer%u", i);
        cgSetUniformBufferParameter(cgGetNamedProgramUniformBuffer(draw_cmd->vertex_shader->cg_program, &cbuffer_name[0]), draw_cmd->vs_constant_buffers[i]->cg_buffer);
    }

    // ps_constant_buffers:
    for( i = 0; i < 4; ++i ) {
        if( !draw_cmd->ps_constant_buffers[i] ) continue;
        sprintf(&cbuffer_name[0], "cbuffer%u", i);
        cgSetUniformBufferParameter(cgGetNamedProgramUniformBuffer(draw_cmd->pixel_shader->cg_program, &cbuffer_name[0]), draw_cmd->ps_constant_buffers[i]->cg_buffer);
    }

    // vertex_shader:
    cgGLEnableProfile(context->cg_vs_profile);
    cgGLBindProgram(draw_cmd->vertex_shader->cg_program);

    // pixel shader:
    cgGLEnableProfile(context->cg_ps_profile);
    cgGLBindProgram(draw_cmd->pixel_shader->cg_program);

    // draw:
    switch( draw_cmd->draw_type )
    {
        case AGL_DRAW:
        {
            glDrawArrays(aglPrimTopologyToOpenGL(draw_cmd->primitive_topology), draw_cmd->params.draw.start_vertex, draw_cmd->params.draw.num_vertices);
        } break;
        
        case AGL_DRAW_INDEXED:
        {
            glDrawElements(aglPrimTopologyToOpenGL(draw_cmd->primitive_topology), draw_cmd->params.draw_indexed.num_indices, aglIndexTypeToOpenGL(draw_cmd->index_type), (const GLvoid*)NULL);
        } break;
    }

    // input_layout:
    for( i = 0; i < draw_cmd->input_layout->num_attribs; ++i )
    {
        aglInputLayoutAttrib* attrib = &draw_cmd->input_layout->attribs[i];
        glDisableVertexAttribArray(attrib->index);
    }
}

static void aglExecuteSetRenderTargetCommand( aglCommand* cmd )
{
    aglSetRenderTargetCommand* set_rt_cmd = (aglSetRenderTargetCommand*)cmd;
    current_rt = set_rt_cmd->render_target;
}

void AGL_API aglExecuteCommands( size_t num_commands, aglCommand* cmds )
{
    uint32_t i;
    assert(cmds);

    for( i = 0; i < num_commands; ++i )
    {
        switch( (*cmds).type )
        {
            case AGL_COMMAND_Clear: aglExecuteClearCommand(cmds); cmds += sizeof(aglClearCommand); break;
            case AGL_COMMAND_Swap: aglExecuteSwapCommand(cmds); cmds += sizeof(aglSwapCommand); break;
            case AGL_COMMAND_Draw: aglExecuteDrawCommand(cmds); cmds += sizeof(aglDrawCommand); break;
            case AGL_COMMAND_SetRenderTarget: aglExecuteSetRenderTargetCommand(cmds); cmds += sizeof(aglSetRenderTargetCommand); break;
        }
    }
}

#ifdef __cplusplus
}
#endif /* __cplusplus */