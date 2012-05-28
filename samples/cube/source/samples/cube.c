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

int main( int argc, char** argv )
{
    fwEvent event;
    aglContext* context;

    aglClearCommand clear_cmd;
    aglSwapCommand swap_cmd;

    AGL_INIT_CMD(Clear, clear_cmd);
    clear_cmd.bits     = AGL_CLEAR_COLOR | AGL_CLEAR_DEPTH;
    clear_cmd.color[0] =  53.0f / 255.0f;
    clear_cmd.color[1] = 191.0f / 255.0f;
    clear_cmd.color[2] = 239.0f / 255.0f;
    clear_cmd.color[3] = 255.0f / 255.0f;
    clear_cmd.depth    = 1.0f;

    AGL_INIT_CMD(Swap, swap_cmd);

    if( !frameworkInitialize(800, 600, "cube") ) exit(EXIT_FAILURE);
    context = frameworkGetContext();

    while( TRUE )
    {
        while( frameworkGetNextEvent(&event) )
        {
            switch( event.type )
            {
                case FW_CLOSE_EVENT: goto exit; break;
            }
        }

        aglExecuteCommands(1, (aglCommand*)&clear_cmd);
        aglExecuteCommands(1, (aglCommand*)&swap_cmd);
    }

exit:
    frameworkDeinitialize();
    return EXIT_SUCCESS;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */