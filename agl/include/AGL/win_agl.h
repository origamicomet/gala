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

#ifndef _WIN_AGL_H_
#define _WIN_AGL_H_

#ifndef _AGL_H_
    #include <AGL/agl.h>
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern AGL_EXPORT(aglContext* AGL_API waglCreateContext( const aglContextSettings* settings ));
extern AGL_EXPORT(void AGL_API waglDestroyContext( aglContext* context ));
extern AGL_EXPORT(HWND AGL_API waglGetWindowHandle( aglContext* context ));

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _WIN_AGL_H_ */