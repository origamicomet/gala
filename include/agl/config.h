/* ========================================================================== */
/*                                                                            */
/* This file is part of the Abstract Graphics Library.                        */
/*                                                                            */
/* Author(s):                                                                 */
/*                                                                            */
/*   Michael Williams <devbug@bitbyte.ca>                                     */
/*                                                                            */
/* This is free and unencumbered software released into the public domain.    */
/*                                                                            */
/* Anyone is free to copy, modify, publish, use, compile, sell, or distribute */
/* this software, either in source code form or as a compiled binary, for any */
/* purpose, commercial or non-commercial, and by any means.                   */
/*                                                                            */
/* In jurisdictions that recognize copyright laws, the author or authors of   */
/* this software dedicate any and all copyright interest in the software to   */
/* the public domain. We make this dedication for the benefit of the public   */
/* large and to the detriment of our heirs and successors. We intend this     */
/* dedication to be an overt act of relinquishment in perpetuity of all       */
/* present and future rights to this software under copyright law.            */
/*                                                                            */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    */
/* THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER   */
/* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,      */
/* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR      */
/* OTHER DEALINGS IN THE SOFTWARE.                                            */
/*                                                                            */
/* For more information, please refer to <http://unlicense.org/>              */
/*                                                                            */
/* ========================================================================== */
/*! @file include/agl/config.h
     Documents a collection of pre-processor defines used for the
     configuration of AGL's compile-, link-, and runtime behaviour.           */
/* ========================================================================== */

#ifndef _AGL_CONFIG_H_
#define _AGL_CONFIG_H_

/* ========================================================================== */
/*  Configuration:                                                            */
/*   * Compiler, architecture, and platform autodetection;                    */
/*   * Paranoid and/or debug, development, and release selection;             */
/*   * Linkage.                                                               */
/* ========================================================================== */

/* ========================================================================== */
/*  Compiler, architecture, and platform autodetection:                       */
/* ========================================================================== */

/*! @def AGL_DONT_AUTODETECT_COMPILER
  AGL won't attempt to detect the current compiler based on pre-processor defines, if defined.
  See include/agl/detect/compiler.h for more details. */

/*! @def AGL_DONT_AUTODETECT_PLATFORM
  AGL won't attempt to detect the current platform based on pre-processor defines, if defined.
  See include/agl/detect/platform.h for more details. */

/*! @def AGL_DONT_AUTODETECT_ARCHITECTURE
  AGL won't attempt to detect the current architecture based on pre-processor defines, if defined.
  See include/agl/detect/architecture.h for more details. */

/* ========================================================================== */
/*  Paranoid and/or debug, development, and release selection:                */
/* ========================================================================== */

/*! @def AGL_PARANOID
  Specifies how paranoid AGL is; if defined AGL will perform more sanity checks. */

/*! @def AGL_DEBUG
  Enables debugging (and higher) checks and profiling. */
#define AGL_DEBUG 1

/*! @def AGL_DEVELOPMENT
  Enables development (and higher) checks and profiling. */
#define AGL_DEVELOPMENT 2

/*! @def AGL_RELEASE
  Enables release checks. */
#define AGL_RELEASE 3

/*! @def AGL_CONFIGURATION
  Specifies how "loose and fast" AGL is. */
#ifndef AGL_CONFIGURATION
  #error ("Please specify a configuration by defining `AGL_CONFIGURATION`.")
#endif

/* ========================================================================== */
/*  Linkage:                                                                  */
/* ========================================================================== */

/*! @def AGL_LINK_STATICALLY
  Linking to AGL statically, e.g., using libagl.a. */
#define AGL_LINK_STATICALLY 1

/*! @def AGL_LINK_DYNAMICALLY
  Linking to AGL dynamically, e.g., using libagl.so. */
#define AGL_LINK_DYNAMICALLY 2

/*! @def AGL_LINKAGE
  Specifies if AGL is being linked to statically, or dynamically. */
#ifndef AGL_LINKAGE
  #error ("Please specify how you are linking to AGL by defining `AGL_LINKAGE`.")
#endif

/* ========================================================================== */

#endif /* _AGL_CONFIG_H_ */
