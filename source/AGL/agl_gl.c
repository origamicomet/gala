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

typedef enum AGL_CONTEXT_TYPE {
    AGL_OPENGL_CONTEXT   = 1,
    AGL_DEFERRED_CONTEXT = 2,
} AGL_CONTEXT_TYPE;

struct aglContext {
    AGL_CONTEXT_TYPE type : 8;
};

#if defined(_WIN32)
    #include "wagl_gl.incl"
#elif defined(__linux__)
    #include "xagl_gl.incl"
#elif defined(__APPLE__) && defined(__MACH__)
    #include "nsagl_gl.incl"
#else
    #error Not supported.
#endif

void AGL_API aglSetContextTitle( aglContext* context, const char* title );

////////////////////////////////////////////////////////////////////////////////

struct aglCompiledCommandBuffer {

};

aglCompiledCommandBuffer* AGL_API aglCompileCommandBuffer( const aglCommandBuffer* cmd_buffer ));

void AGL_API aglExecuteCommands( aglContext* context, const aglCommandBuffer* cmd_buffer );
void AGL_API aglExecuteCompiledCommands( aglContext* context, const aglCompiledCommandBuffer* cmd_buffer );

////////////////////////////////////////////////////////////////////////////////

typedef struct aglDeferredContext {
    aglContext _context;
    aglCommandBuffer* cmd_buffer;
} aglDeferredContext;

aglContext* AGL_API aglCreateDeferredContext( aglCommandBuffer* cmd_buffer )
{
    assert(cmd_buffer);

    aglDeferredContext* deferred_context = (aglDeferredContext*)aglAlloc(sizeof(aglDeferredContext));
    deferred_context->_context.type = AGL_DEFERRED_CONTEXT;
    deferred_context->cmd_buffer = cmd_buffer;

    return deferred_context;
}