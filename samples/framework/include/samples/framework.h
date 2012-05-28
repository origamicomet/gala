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

#ifndef _AGL_SAMPLES_FRAMEWORK_HPP_
#define _AGL_SAMPLES_FRAMEWORK_HPP_

#include <AGL/agl.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum FW_KEY {

} FW_KEY;

typedef enum FW_MOUSE_BUTTON {
    FW_MOUSE_LEFT_BTN   = 1,
    FW_MOUSE_RIGHT_BTN  = 2,
    FW_MOUSE_MIDDLE_BTN = 3
} FW_MOUSE_BUTTON;

typedef enum FW_EVENT_TYPE {
    FW_RESIZE_EVENT       = 1,
    FW_CLOSE_EVENT        = 2,
    FW_KEY_DOWN_EVENT     = 3,
    FW_KEY_UP_EVENT       = 4,
    FW_MOUSE_MOVE_EVENT   = 5,
    FW_MOUSE_BUTTON_EVENT = 6,
    FW_MOUSE_WHEEL_EVENT  = 7
} FW_EVENT_TYPE;

typedef struct fwEvent {
    FW_EVENT_TYPE type;
    union {
        struct {
            uint32_t width;
            uint32_t height;
        } resize;

        struct {
            uint32_t reserved;
        } close;

        struct {
            FW_KEY key : 32;
        } key_down;

        struct {
            FW_KEY key : 32;
        } key_up;

        struct {
            int32_t x;
            int32_t y;
        } mouse_move;

        struct {
            FW_MOUSE_BUTTON button : 32;
        } mouse_button;

        struct {
            int32_t wheel;
        } mouse_wheel;
    } data;
} fwEvent;

int32_t frameworkInitialize( uint32_t width, uint32_t height, const char* title );
void    frameworkDeinitialize();
aglContext* frameworkGetContext();
int32_t frameworkGetNextEvent( fwEvent* event );

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _AGL_SAMPLES_FRAMEWORK_HPP_ */