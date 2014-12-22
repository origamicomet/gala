# Gala

[![Build Status](https://travis-ci.org/origamicomet/gala.png?branch=master)](http://travis-ci.org/origamicomet/gala)

Gala is a low-level abstraction layer for rendering.

What platforms does it support?
-------------------------------

| Platform  | Toolchain               | Supported             |
|:---------:|:-----------------------:|:---------------------:|
| Windows   | Microsoft Visual Studio |        Planned        |
| Windows   | MinGW/MSYS              |        Planned        |
| Windows   | Cygwin                  |         Never         |
| Mac OS X  | GCC or Clang            |        Planned        |
| Linux     | GCC or Clang            |        Planned        |
| BSD       | GCC or Clang            |        Planned        |
| Android   | GCC or Clang            |        Planned        |
| iOS       | GCC or Clang            |        Planned        |
| Web       | Native Client           |        Planned        |
| Web       | emscripten              |        Planned        |

What backends does it provide?
------------------------------

| Platform   | Backend               | Supported             |
|:----------:|:---------------------:|:---------------------:|
| Windows    | `GALA_BACKEND_D3D9`   |        Planned        |
| Windows    | `GALA_BACKEND_D3D11`  |        Planned        |
| Windows    | `GALA_BACKEND_GL21`   |        Planned        |
| Windows    | `GALA_BACKEND_GL31`   |        Planned        |
| Windows    | `GALA_BACKEND_MANTLE` |        Planned        |
|            |                       |                       |
| Mac OS X   | `GALA_BACKEND_GL21`   |        Planned        |
| Mac OS X   | `GALA_BACKEND_GL31`   |        Planned        |
| Mac OS X   | `GALA_BACKEND_MANTLE` |       Hopefully       |
|            |                       |                       |
| Linux      | `GALA_BACKEND_GL21`   |        Planned        |
| Linux      | `GALA_BACKEND_GL31`   |        Planned        |
| Linux      | `GALA_BACKEND_MANTLE` |       Hopefully       |
|            |                       |                       |
| Android    | `GALA_BACKEND_GLES`   |         Never         |
| Android    | `GALA_BACKEND_GLES2`  |        Planned        |
| Android    | `GALA_BACKEND_GLES3`  |        Planned        |
|            |                       |                       |
| iOS        | `GALA_BACKEND_GLES`   |         Never         |
| iOS        | `GALA_BACKEND_GLES2`  |        Planned        |
| iOS        | `GALA_BACKEND_GLES3`  |        Planned        |
| iOS        | `GALA_BACKEND_METAL`  |       Hopefully       |
|            |                       |                       |
| NaCl       | `GALA_BACKEND_GLES2`  |        Planned        |
| NaCl       | `GALA_BACKEND_GLES3`  |        Planned        |
|            |                       |                       |
| emscripten | `GALA_BACKEND_GLES2`  |        Planned        |
| emscripten | `GALA_BACKEND_GLES3`  |        Planned        |

How do I build it?
------------------

    $ git clone https://github.com/origamicomet/gala.git
    $ cd gala
    $ ./configure
    $ make

For more details please go [here](https://github.com/origamicomet/gala/wiki/Building).

How do I contribute?
--------------------

See our contribution guide [here](https://github.com/origamicomet/gala/wiki/Contributing).

How is it licensed?
-------------------

Under the public domain with licensing agreements for closed platforms.

```
Author(s):

  * Michael Williams <mike@origamicomet.com>

This is free and unencumbered software released into the public domain. Anyone
is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.

In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public large and to the
detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
