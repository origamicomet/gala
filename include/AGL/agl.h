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

typedef void (AGL_API *aglContextResized)( struct aglContext*, uint32_t width, uint32_t height );
typedef void (AGL_API *aglContextClosed)( struct aglContext* );

typedef struct aglContextSettings {
    uint32_t width;
    uint32_t height;
    unsigned vsync      : 1;
    unsigned fullscreen : 1;
    unsigned resizeable : 1;
    unsigned reserved   : 5;
    aglContextResized resized;
    aglContextResized closed;
} aglContextSettings;

typedef struct aglContext aglContext;

AGL_EXPORT(void AGL_API aglSetContextTitle( aglContext* context, const char* title ));

////////////////////////////////////////////////////////////////////////////////

typedef uint32_t (AGL_API *aglCommandBufferCallback)( struct aglCommandBuffer*, const size_t );

typedef struct aglCommandBuffer {
    void* begin;
    void* end;
    void* current;
    aglCommandBufferCallback callback;
} aglCommandBuffer;

typedef struct aglCompiledCommandBuffer aglCompiledCommandBuffer;

AGL_EXPORT(aglCompiledCommandBuffer* AGL_API aglCompileCommandBuffer( const aglCommandBuffer* cmd_buffer ));

AGL_EXPORT(void AGL_API aglExecuteCommands( aglContext* context, const aglCommandBuffer* cmd_buffer ));
AGL_EXPORT(void AGL_API aglExecuteCompiledCommands( aglContext* context, const aglCompiledCommandBuffer* cmd_buffer ));

////////////////////////////////////////////////////////////////////////////////

AGL_EXPORT(aglContext* AGL_API aglCreateDeferredContext( aglCommandBuffer* cmd_buffer ));

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

AGL_EXPORT(void AGL_API aglSetInputLayout( aglCommandBuffer* cmd_buffer, const aglInputLayout* input_layout ));

typedef struct aglVertexBuffer   aglVertexBuffer;
typedef struct aglIndexBuffer    aglIndexBuffer;
typedef struct aglConstantBuffer aglConstantBuffer;

typedef struct aglVertexShader aglVertexShader;
typedef struct aglPixelShader  aglPixelShader;

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _AGL_H_ */