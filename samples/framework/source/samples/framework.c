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

#if   defined(AGL_PLATFORM_WINDOWS)
    #include <AGL/win_agl.h>
#elif defined(AGL_PLATFORM_LINUX)
    #include <AGL/xlib_agl.h>
#elif defined(AGL_PLATFORM_OSX)
    #include <AGL/ns_agl.h>
#elif defined(AGL_PLATFORM_IOS)
    #error Not implemented.
#elif defined(AGL_PLATFORM_ANDROID)
    #error Not implemented.
#else
    #error Not supported.
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static aglContext* framework_context = NULL;

static void* AGL_API aglAlloc( size_t num_bytes ) { return malloc(num_bytes); }
static void  AGL_API aglFree( void* ptr ) { return free(ptr); }

int32_t frameworkInitialize( uint32_t width, uint32_t height, const char* title )
{
    const aglContextSettings context_settings = {
        width, height, 0, FALSE, FALSE
    };

    if( aglInit(&aglAlloc, &aglFree) != AGL_SUCCESS ) return FALSE;

#if   defined(AGL_PLATFORM_WINDOWS)
    framework_context = waglCreateContext(&context_settings);
    if( !framework_context ) return FALSE;
    aglSetActiveContext(framework_context);
    SetWindowTextA(waglGetWindowHandle(framework_context), title);
#elif defined(AGL_PLATFORM_LINUX)
#elif defined(AGL_PLATFORM_OSX)
#elif defined(AGL_PLATFORM_IOS)
#elif defined(AGL_PLATFORM_ANDROID)
#else
#endif

    return TRUE;
}

void frameworkDeinitialize()
{
    #if   defined(AGL_PLATFORM_WINDOWS)
        waglDestroyContext(framework_context);
        framework_context = NULL;
    #elif defined(AGL_PLATFORM_LINUX)
    #elif defined(AGL_PLATFORM_OSX)
    #elif defined(AGL_PLATFORM_IOS)
    #elif defined(AGL_PLATFORM_ANDROID)
    #else
    #endif
}

aglContext* frameworkGetContext()
{
    return framework_context;
}

int32_t frameworkGetNextEvent( fwEvent* event )
{
#if   defined(AGL_PLATFORM_WINDOWS)
    HWND hWnd = waglGetWindowHandle(framework_context);
    MSG  msg;

    if( PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE) )
    {
        switch( msg.message )
        {
            case WM_CLOSE: {
                event->type = FW_CLOSE_EVENT;
            } break;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
        return TRUE;
    }
    else
    {
        return FALSE;
    }

#elif defined(AGL_PLATFORM_LINUX)
#elif defined(AGL_PLATFORM_OSX)
#elif defined(AGL_PLATFORM_IOS)
#elif defined(AGL_PLATFORM_ANDROID)
#else
#endif
}

#ifdef __cplusplus
}
#endif /* __cplusplus */