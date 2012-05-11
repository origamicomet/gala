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

#ifndef _AGL_H_
#define _AGL_H_

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef NULL
    #ifdef __cplusplus
        #define NULL 0
    #else
        #define NULL ((void*)0)
    #endif
#endif /* NULL */

#ifndef offsetof
    #ifdef __GNUC__
        #define offsetof(st, m) __builtin_offsetof(st, m)
    #else
        #define offsetof(st, m) ((size_t)((char*)&((st*)0)->m - (char*)0))
    #endif
#endif /* offsetof */

#define AGL_API __stdcall

#ifdef AGL_BUILD_DLL
    #error Not implemented.
#endif /* AGL_BUILD_DLL */

#ifdef AGL_BUILD_LIBARY
    #define AGL_EXPORT( x ) extern x
#endif /* AGL_BUILD_LIBARY */

// switch to packet based?

typedef enum AGL_ERROR {
    AGL_SUCCESS = 1
} AGL_ERROR;

typedef void* (AGL_API *aglAllocCallback)( size_t );
typedef void (AGL_API *aglFreeCallback)( void* );

AGL_EXPORT(uint32_t AGL_API aglInit( aglAllocCallback alloc_callback, aglFreeCallback free_callback ));

////////////////////////////////////////////////////////////////////////////////

typedef struct aglContextSettings {
    uint32_t width;
    uint32_t height;
    uint32_t samples;
    unsigned vsync      : 1;
    unsigned fullscreen : 1;
    unsigned reserved   : 6;
} aglContextSettings;

typedef struct aglContext aglContext;

AGL_EXPORT(void AGL_API aglSwapBuffers( aglContext* context ));

////////////////////////////////////////////////////////////////////////////////

typedef struct aglInputLayout aglInputLayout;

typedef enum AGL_INPUT_ELEMENT_TYPE {
    AGL_IE_UNKNOWN   = 0,
    AGL_IE_FLOAT     = 1,
    AGL_IE_DOUBLE    = 2,
    AGL_IE_INT8      = 3,
    AGL_IE_UINT8     = 4,
    AGL_IE_INT16     = 5,
    AGL_IE_UINT16    = 6,
    AGL_IE_INT32     = 7,
    AGL_IE_UINT32    = 8
} AGL_INPUT_ELEMENT_TYPE;

typedef enum AGL_INPUT_ELEMENT_NORMALIZE {
    AGL_IE_DONT_NORMALIZE = 0,
    AGL_IE_NORMALIZE      = 1,
} AGL_INPUT_ELEMENT_NORMALIZE;

typedef struct aglInputElementDesc {
    const char* param_name;
    AGL_INPUT_ELEMENT_TYPE element_type;
    uint32_t num_components;
    AGL_INPUT_ELEMENT_NORMALIZE normalize;
    uint32_t slot;
    uint32_t step_rate;
    uint32_t stride;
    uint32_t offset;
} aglInputElementDesc;

AGL_EXPORT(aglInputLayout* AGL_API aglCreateInputLayout( const size_t num_descs, const aglInputElementDesc* descs ));
AGL_EXPORT(void AGL_API aglDestroyInputLayout( aglInputLayout* input_layout ));

////////////////////////////////////////////////////////////////////////////////

typedef struct aglRasterizerState aglRasterizerState;

typedef enum AGL_FILL_MODE {
    AGL_FILL_WIREFRAME = 1,
    AGL_FILL_SOLID     = 2
} AGL_FILL_MODE;

typedef enum AGL_CULL_MODE {
    AGL_CULL_NONE      = 1,
    AGL_CULL_FRONT     = 2,
    AGL_CULL_BACK      = 3
} AGL_CULL_MODE;

typedef enum AGL_FRONT_FACE {
    AGL_CLOCKWISE         = 1,
    AGL_COUNTER_CLOCKWISE = 2
} AGL_FRONT_FACE;

typedef enum aglRasterizerDesc {
    AGL_FILL_MODE  fill_mode;
    AGL_CULL_MODE  cull_mode;
    AGL_FRONT_FACE front_face;
    unsigned       enable_scissor : 1;
    unsigned       reserved : 7;
} aglRasterizerDesc;

AGL_EXPORT(aglRasterizerState* AGL_API aglCreateRasterizerState( const aglRasterizerDesc* desc ));
AGL_EXPORT(void AGL_API aglDestroyRasterizerState( aglRasterizerState* rasterizer_state ));

typedef enum AGL_BLEND {
    AGL_BLEND_ZERO             = 1,
    AGL_BLEND_ONE              = 2,
    AGL_BLEND_SRC_COLOR        = 3,
    AGL_BLEND_INV_SRC_COLOR    = 4,
    AGL_BLEND_SRC_ALPHA        = 5,
    AGL_BLEND_INV_SRC_ALPHA    = 6,
    AGL_BLEND_DEST_ALPHA       = 7,
    AGL_BLEND_INV_DEST_ALPHA   = 8,
    AGL_BLEND_DEST_COLOR       = 9,
    AGL_BLEND_INV_DEST_COLOR   = 10,
    AGL_BLEND_SRC_ALPHA_SAT    = 11,
    AGL_BLEND_BLEND_FACTOR     = 14,
    AGL_BLEND_INV_BLEND_FACTOR = 15
} AGL_BLEND;

typedef enum AGL_BLEND_OP {
    AGL_BLEND_OP_ADD          = 1,
    AGL_BLEND_OP_SUBTRACT     = 2,
    AGL_BLEND_OP_REV_SUBTRACT = 3,
    AGL_BLEND_OP_MIN          = 4,
    AGL_BLEND_OP_MAX          = 5 
} AGL_BLEND_OP;

typedef enum aglBlendDesc {
    unsigned     enable_blend : 1;
    unsigned     reserved     : 7;
    AGL_BLEND    src_blend;
    AGL_BLEND    dest_blend;
    AGL_BLEND_OP blend_op;
    AGL_BLEND    src_blend_alpha;
    AGL_BLEND    dest_blend_alpha;
    AGL_BLEND_OP blend_op_alpha;
} aglBlendDesc;

typedef struct aglBlendState aglBlendState;

AGL_EXPORT(aglBlendState* AGL_API aglCreateBlendState( const aglBlendDesc* desc ));
AGL_EXPORT(void AGL_API aglDestroyBlendState( aglBlendState* blend_state ));

typedef enum AGL_COMPARISON_FUNC {
    AGL_COMPARISON_NEVER         = 1,
    AGL_COMPARISON_LESS          = 2,
    AGL_COMPARISON_EQUAL         = 3,
    AGL_COMPARISON_LESS_EQUAL    = 4,
    AGL_COMPARISON_GREATER       = 5,
    AGL_COMPARISON_NOT_EQUAL     = 6,
    AGL_COMPARISON_GREATER_EQUAL = 7,
    AGL_COMPARISON_ALWAYS        = 8 
} AGL_COMPARISON_FUNC;

typedef enum AGL_COMPARISON_FUNC {
  AGL_COMPARISON_NEVER          = 1,
  AGL_COMPARISON_LESS           = 2,
  AGL_COMPARISON_EQUAL          = 3,
  AGL_COMPARISON_LESS_EQUAL     = 4,
  AGL_COMPARISON_GREATER        = 5,
  AGL_COMPARISON_NOT_EQUAL      = 6,
  AGL_COMPARISON_GREATER_EQUAL  = 7,
  AGL_COMPARISON_ALWAYS         = 8 
} AGL_COMPARISON_FUNC;

typedef struct aglDepthStencilOpDesc {
    AGL_STENCIL_OP stencil_fail;
    AGL_STENCIL_OP stencil_depth_fail;
    AGL_STENCIL_OP stencil_pass;
    AGL_COMPARISON_FUNC stencil_func;
} aglDepthStencilOpDesc;

typedef struct aglDepthStencilDesc {
    unsigned enable_depth_test   : 1;
    unsigned enable_depth_write  : 1;
    unsigned enable_stencil_test : 1;
    unsigned reserved            : 6;
    AGL_COMPARISON_FUNC depth_func;
    aglDepthStencilOpDesc front_face;
    aglDepthStencilOpDesc back_face;
} aglDepthStencilDesc;

typedef struct aglDepthStencilState aglDepthStencilState;

AGL_EXPORT(aglDepthStencilState* AGL_API aglCreateDepthStencilState( const aglDepthStencilDesc* desc ));
AGL_EXPORT(void AGL_API aglDestroyDepthstencilState( aglDepthStencilState* depth_stencil_state ));

////////////////////////////////////////////////////////////////////////////////

typedef enum AGL_USAGE {
    AGL_USAGE_DEFAULT   = 0,
    AGL_USAGE_IMMUTABLE = 1,
    AGL_USAGE_DYNAMIC   = 2,
    AGL_USAGE_STAGING   = 3 
} AGL_USAGE;

typedef enum AGL_CPU_ACCESS_FLAG {
    AGL_CPU_ACCESS_WRITE   = 0x10000L,
    AGL_CPU_ACCESS_READ    = 0x20000L 
} AGL_CPU_ACCESS_FLAG;

////////////////////////////////////////////////////////////////////////////////

typedef struct aglVertexBuffer aglVertexBuffer;

AGL_EXPORT(aglVertexBuffer* AGL_API aglCreateVertexBuffer( AGL_USAGE usage, uint32_t access_flags, size_t num_bytes, const void* data ));
AGL_EXPORT(void AGL_API aglDestroyVertexBuffer( aglVertexBuffer* vertex_buffer ));

typedef struct aglIndexBuffer aglIndexBuffer;

AGL_EXPORT(aglIndexBuffer* AGL_API aglCreateIndexBuffer( AGL_USAGE usage, uint32_t access_flags, size_t num_bytes, const void* data ));
AGL_EXPORT(void AGL_API aglDestroyIndexBuffer( aglIndexBuffer* index_buffer ));

typedef struct aglConstantBuffer aglConstantBuffer;

AGL_EXPORT(aglConstantBuffer* AGL_API aglCreateConstantBuffer( AGL_USAGE usage, uint32_t access_flags, size_t num_bytes, const void* data ));
AGL_EXPORT(void AGL_API aglDestroyConstantBuffer( aglConstantBuffer* constant_buffer ));

////////////////////////////////////////////////////////////////////////////////

typedef struct aglTexture aglTexture;



typedef struct aglRenderTarget aglRenderTarget;

////////////////////////////////////////////////////////////////////////////////

typedef struct aglVertexShader aglVertexShader;
typedef struct aglPixelShader aglPixelShader;

////////////////////////////////////////////////////////////////////////////////

#define AGL_INIT_CMD( type, st ) { memset((void*)&(st), 0, sizeof(agl##type##Command)); (st)._cmd.type = AGL_COMMAND_##type; }

typedef enum AGL_COMMAND_TYPE {
    AGL_COMMAND_Clear = 1,
    AGL_COMMAND_Swap  = 2,
    AGL_COMMAND_Draw  = 3,
} AGL_COMMAND_TYPE;

typedef struct aglCommand {
    AGL_COMMAND_TYPE type : 8;
} aglCommand;

typedef AGL_CLEAR_BITS {
    AGL_CLEAR_COLOR   = (1 << 0),
    AGL_CLEAR_DEPTH   = (1 << 1),
    AGL_CLEAR_STENCIL = (1 << 2)
} AGL_CLEAR_BITS;

typedef struct aglClearCommand {
    aglCommand _cmd;
    AGL_CLEAR_BITS bits : 8;
    float   color[4];
    float   depth;
    uint8_t stencil;
} aglClearCommand;

typedef struct aglSwapCommand {
    aglCommand _cmd;
} aglSwapCommand;

typedef enum AGL_DRAW_TYPE {
    AGL_DRAW         = 1,
    AGL_DRAW_INDEXED = 2,
} AGL_DRAW_TYPE;

typedef struct aglDrawCommand {
    aglCommand _cmd;
    aglRasterizerState*     rasterizer_state;
    aglBlendState*          blend_state;
    aglDepthStencilState*   depth_stencil_state;
    aglRenderTarget*        render_target;
    aglInputLayout*         input_layout;
    AGL_PRIMITIVE_TOPOLOGY  primitive_topology : 8;
    aglVertexShader*        vertex_shader;
    aglPixelShader*         pixel_shader;
    aglTexture*             textures[8];
    aglIndexBuffer*         index_buffer;
    aglVertexBuffer*        vertex_buffers[8];
    AGL_DRAW_TYPE           draw_type : 8;
    union params {
        struct draw {
            uint32_t num_vertices;
            uint32_t start_vertex;
        };

        struct draw_indexed {
            uint32_t num_indices;
            uint32_t start_index;
        };
    };
} aglDrawCommand;

AGL_EXPORT(void AGL_API aglExecuteCommands( aglContext* context, const aglCommand* cmds, size_t num_commands ));

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _AGL_H_ */