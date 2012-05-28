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

#include <AGL/config.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
    #define AGL_COMPILER_MSVC
#endif

#if defined(__GNUC__)
    #define AGL_COMPILER_GCC
#endif

#if defined(__clang__)
    #define AGL_COMPILER_CLANG
#endif

////////////////////////////////////////////////////////////////////////////////

#if defined(_WIN32)
    #define AGL_PLATFORM_WIN32
#endif

#if defined(_WIN64)
    #define AGL_PLATFORM_WIN64
#endif

#if defined(AGL_PLATFORM_WIN32) || defined(AGL_PLATFORM_WIN64)
    #define AGL_PLATFORM_WINDOWS
#endif

#if defined(__linux__)
    #define AGL_PLATFORM_LINUX
#endif

#if defined(__APPLE__)
    #include "TargetConditionals.h"

    #if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
        #define AGL_PLATFORM_IOS
    #elif defined(TARGET_OS_MAC)
        #define AGL_PLATFORM_OSX
    #else
        #error Unknown platform.
    #endif
#endif

#if defined(ANDROID) || defined(__ANDROID__)
    #define AGL_PLATFORM_ANDROID
#endif

////////////////////////////////////////////////////////////////////////////////

#ifndef NULL
    #ifdef __cplusplus
        #define NULL 0
    #else
        #define NULL ((void*)0)
    #endif
#endif /* NULL */

#ifndef TRUE
    #define TRUE 1
#endif /* TRUE */

#ifndef FALSE
    #define FALSE 0
#endif /* FALSE */

#ifndef offsetof
    #if defined(AGL_COMPILER_GCC)
        #define offsetof(st, m) __builtin_offsetof(st, m)
    #else
        #define offsetof(st, m) ((size_t)((char*)&((st*)0)->m - (char*)0))
    #endif
#endif /* offsetof */

#if defined(AGL_DYNAMIC_LINK)
    #if defined(AGL_PLATFORM_WINDOWS)
        #if defined(AGL_BUILD)
            #define AGL_EXPORT( x ) __declspec(dllexport) x
        #else
            #define AGL_EXPORT( x ) __declspec(dllimport) x
        #endif
    #else
        #define AGL_EXPORT( x )
    #endif
#elif defined(AGL_STATIC_LINK)
    #define AGL_EXPORT( x ) x
#else /* AGL_STATIC_LINK */
    #error No link type specified.
#endif

typedef enum AGL_ERROR {
    AGL_SUCCESS = 1
} AGL_ERROR;

typedef void* (AGL_API *aglAllocCallback) ( size_t );
typedef void  (AGL_API *aglFreeCallback)  ( void* );

extern AGL_EXPORT(uint32_t AGL_API aglInit( aglAllocCallback alloc_callback, aglFreeCallback free_callback ));

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

extern AGL_EXPORT(void AGL_API aglSetActiveContext( aglContext* context ));
extern AGL_EXPORT(aglContext* AGL_API aglGetActiveContext( void ));

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
    uint32_t attrib_index;
    AGL_INPUT_ELEMENT_TYPE element_type : 8;
    uint32_t num_components;
    AGL_INPUT_ELEMENT_NORMALIZE normalize : 8;
    uint32_t slot;
    uint32_t step_rate;
    uint32_t stride;
    uint32_t offset;
} aglInputElementDesc;

extern AGL_EXPORT(aglInputLayout* AGL_API aglCreateInputLayout( const size_t num_descs, const aglInputElementDesc* descs ));
extern AGL_EXPORT(void AGL_API aglDestroyInputLayout( aglInputLayout* input_layout ));

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

typedef struct aglRasterizerDesc {
    AGL_FILL_MODE  fill_mode;
    AGL_CULL_MODE  cull_mode;
    AGL_FRONT_FACE front_face;
    unsigned       enable_scissor : 1;
    unsigned       reserved       : 7;
} aglRasterizerDesc;

extern AGL_EXPORT(aglRasterizerState* AGL_API aglCreateRasterizerState( const aglRasterizerDesc* desc ));
extern AGL_EXPORT(void AGL_API aglDestroyRasterizerState( aglRasterizerState* rasterizer_state ));

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

typedef struct aglBlendDesc {
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

extern AGL_EXPORT(aglBlendState* AGL_API aglCreateBlendState( const aglBlendDesc* desc ));
extern AGL_EXPORT(void AGL_API aglDestroyBlendState( aglBlendState* blend_state ));

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

typedef enum AGL_STENCIL_OP {
    AGL_STENCIL_OP_KEEP     = 1,
    AGL_STENCIL_OP_ZERO     = 2,
    AGL_STENCIL_OP_REPLACE  = 3,
    AGL_STENCIL_OP_INCR_SAT = 4,
    AGL_STENCIL_OP_DECR_SAT = 5,
    AGL_STENCIL_OP_INVERT   = 6,
    AGL_STENCIL_OP_INCR     = 7,
    AGL_STENCIL_OP_DECR     = 8 
} AGL_STENCIL_OP;

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

extern AGL_EXPORT(aglDepthStencilState* AGL_API aglCreateDepthStencilState( const aglDepthStencilDesc* desc ));
extern AGL_EXPORT(void AGL_API aglDestroyDepthStencilState( aglDepthStencilState* depth_stencil_state ));

////////////////////////////////////////////////////////////////////////////////

typedef enum AGL_USAGE {
    AGL_USAGE_DEFAULT   = 0,
    AGL_USAGE_IMMUTABLE = 1,
    AGL_USAGE_DYNAMIC   = 2,
    AGL_USAGE_STAGING   = 3 
} AGL_USAGE;

typedef enum AGL_CPU_ACCESS_FLAG {
    AGL_CPU_ACCESS_WRITE   = (1 << 0),
    AGL_CPU_ACCESS_READ    = (1 << 1) 
} AGL_CPU_ACCESS_FLAG;

typedef enum AGL_MAP {
    AGL_MAP_READ               = 1,
    AGL_MAP_WRITE              = 2,
    AGL_MAP_READ_WRITE         = 3
} AGL_MAP;

////////////////////////////////////////////////////////////////////////////////

typedef struct aglVertexBuffer aglVertexBuffer;

extern AGL_EXPORT(aglVertexBuffer* AGL_API aglCreateVertexBuffer( AGL_USAGE usage, uint32_t access_flags, size_t num_bytes, const void* data ));
extern AGL_EXPORT(void AGL_API aglDestroyVertexBuffer( aglVertexBuffer* vertex_buffer ));

extern AGL_EXPORT(void* AGL_API aglMapVertexBuffer( aglVertexBuffer* vertex_buffer, AGL_MAP map ));
extern AGL_EXPORT(void AGL_API aglUnmapVertexBuffer( aglVertexBuffer* vertex_buffer ));

typedef struct aglIndexBuffer aglIndexBuffer;

extern AGL_EXPORT(aglIndexBuffer* AGL_API aglCreateIndexBuffer( AGL_USAGE usage, uint32_t access_flags, size_t num_bytes, const void* data ));
extern AGL_EXPORT(void AGL_API aglDestroyIndexBuffer( aglIndexBuffer* index_buffer ));

extern AGL_EXPORT(void* AGL_API aglMapIndexBuffer( aglIndexBuffer* index_buffer, AGL_MAP map ));
extern AGL_EXPORT(void AGL_API aglUnmapIndexBuffer( aglIndexBuffer* index_buffer ));

typedef struct aglConstantBuffer aglConstantBuffer;

extern AGL_EXPORT(aglConstantBuffer* AGL_API aglCreateConstantBuffer( AGL_USAGE usage, uint32_t access_flags, size_t num_bytes, const void* data ));
extern AGL_EXPORT(void AGL_API aglDestroyConstantBuffer( aglConstantBuffer* constant_buffer ));

extern AGL_EXPORT(void* AGL_API aglMapConstantBuffer( aglConstantBuffer* constant_buffer, AGL_MAP map ));
extern AGL_EXPORT(void AGL_API aglUnmapConstantBuffer( aglConstantBuffer* constant_buffer ));

////////////////////////////////////////////////////////////////////////////////

typedef struct aglTexture aglTexture;

typedef enum AGL_TEXTURE_FORMAT {
    AGL_TEXTURE_R8G8B8        = 1,
    AGL_TEXTURE_R8G8B8A8      = 2,
    AGL_TEXTURE_R8G8B8A8_SRGB = 3,
    AGL_TEXTURE_R16G16B16A16F = 4,
    AGL_TEXTURE_D24S8         = 6
} AGL_TEXTURE_FORMAT;

typedef struct aglTextureDesc2D {
    uint32_t width;
    uint32_t height;
    AGL_TEXTURE_FORMAT format     : 8;
    unsigned generate_mips        : 1;
    unsigned bind_render_target   : 1;
    unsigned bind_depth_stencil   : 1;
    unsigned bind_shader_resource : 1;
    unsigned reserved0            : 20;
} aglTextureDesc2D;

typedef struct aglBox {
    uint32_t left;
    uint32_t top;
    uint32_t front;
    uint32_t right;
    uint32_t bottom;
    uint32_t back;
} aglBox;

extern AGL_EXPORT(aglTexture* AGL_API aglCreateTexture2D( const aglTextureDesc2D* desc, const void* data ));
extern AGL_EXPORT(void AGL_API aglDestroyTexture( aglTexture* texture ));

extern AGL_EXPORT(void AGL_API aglGenerateMips( aglTexture* texture ));
extern AGL_EXPORT(void AGL_API aglUpdateTexture2D( aglTexture* texture, const aglBox* box, uint32_t mipmap, const void* data ));

////////////////////////////////////////////////////////////////////////////////

typedef struct aglRenderTarget aglRenderTarget;

typedef struct aglRenderTargetDesc {
    aglTexture* depth_stencil;
    aglTexture* color[4];
} aglRenderTargetDesc;

extern AGL_EXPORT(aglRenderTarget* aglCreateRenderTarget( const aglRenderTargetDesc* desc ));
extern AGL_EXPORT(void aglDestroyRenderTarget( aglRenderTarget* render_target ));

////////////////////////////////////////////////////////////////////////////////

typedef struct aglVertexShader aglVertexShader;
typedef struct aglPixelShader  aglPixelShader;

extern AGL_EXPORT(aglVertexShader* AGL_API aglCreateVertexShader( const char* objcode ));
extern AGL_EXPORT(void AGL_API AGL_API aglDestroyVertexShader( aglVertexShader* vertex_shader ));

extern AGL_EXPORT(aglPixelShader* AGL_API aglCreatePixelShader( const char* objcode ));
extern AGL_EXPORT(void AGL_API aglDestroyPixelShader( aglPixelShader* pixel_shader ));

////////////////////////////////////////////////////////////////////////////////

#define AGL_INIT_CMD( type, st ) { memset((void*)&(st), 0, sizeof(agl##type##Command); (st)._cmd.type = AGL_COMMAND_##type; }

typedef enum AGL_COMMAND_TYPE {
    AGL_COMMAND_Clear           = 1,
    AGL_COMMAND_Swap            = 2,
    AGL_COMMAND_Draw            = 3,
    AGL_COMMAND_SetRenderTarget = 4
} AGL_COMMAND_TYPE;

typedef struct aglCommand {
    AGL_COMMAND_TYPE type : 8;
} aglCommand;

typedef enum AGL_CLEAR_BITS {
    AGL_CLEAR_COLOR   = (1 << 0),
    AGL_CLEAR_DEPTH   = (1 << 1),
    AGL_CLEAR_STENCIL = (1 << 2)
} AGL_CLEAR_BITS;

typedef struct aglClearCommand {
    aglCommand      _cmd;
    AGL_CLEAR_BITS  bits : 8;
    uint32_t        buffer;
    float           color[4];
    float           depth;
    uint8_t         stencil;
} aglClearCommand;

typedef struct aglSwapCommand {
    aglCommand _cmd;
} aglSwapCommand;

typedef enum AGL_PRIMITIVE_TOPOLOGY {
    AGL_PRIMITIVE_TOPOLOGY_UNDEFINED         = 0,
    AGL_PRIMITIVE_TOPOLOGY_POINTLIST         = 1,
    AGL_PRIMITIVE_TOPOLOGY_LINELIST          = 2,
    AGL_PRIMITIVE_TOPOLOGY_LINESTRIP         = 3,
    AGL_PRIMITIVE_TOPOLOGY_TRIANGLELIST      = 4,
    AGL_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP     = 5,
    AGL_PRIMITIVE_TOPOLOGY_LINELIST_ADJ      = 6,
    AGL_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ     = 7,
    AGL_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ  = 8,
    AGL_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ = 9
} AGL_PRIMITIVE_TOPOLOGY;

typedef enum AGL_INDEX_TYPE {
    AGL_INDEX_UINT16    = 1,
    AGL_INDEX_UINT32    = 2
} AGL_INDEX_TYPE;

typedef enum AGL_DRAW_TYPE {
    AGL_DRAW         = 1,
    AGL_DRAW_INDEXED = 2
} AGL_DRAW_TYPE;

typedef struct aglDrawCommand {
    aglCommand _cmd;
    aglRasterizerState*     rasterizer_state; // TODO: move out of command
    aglBlendState*          blend_state;
    aglDepthStencilState*   depth_stencil_state;
    uint32_t                stencil_ref;
    aglInputLayout*         input_layout;
    AGL_PRIMITIVE_TOPOLOGY  primitive_topology : 8;
    aglVertexShader*        vertex_shader;
    aglPixelShader*         pixel_shader;
    aglTexture*             textures[4];
    AGL_INDEX_TYPE          index_type : 8;
    aglIndexBuffer*         index_buffer;
    aglVertexBuffer*        vertex_buffers[4];
    aglConstantBuffer*      vs_constant_buffers[4];
    aglConstantBuffer*      ps_constant_buffers[4];
    AGL_DRAW_TYPE           draw_type : 8;
    union {
        struct {
            uint32_t start_vertex;
            uint32_t num_vertices;
        } draw;

        struct {
            uint32_t start_index;
            uint32_t num_indices;
        } draw_indexed;
    } params;
} aglDrawCommand;

typedef struct aglSetRenderTargetCommand {
    aglCommand _cmd;
    aglRenderTarget* render_target;
} aglSetRenderTargetCommand;

extern AGL_EXPORT(void AGL_API aglExecuteCommands( size_t num_commands, aglCommand* cmds ));

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _AGL_H_ */