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
/*! @file include/agl/log.h
     Provides a level based logging interface.                                */
/* ========================================================================== */

#ifndef _AGL_LOG_H_
#define _AGL_LOG_H_

#include <agl/config.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ========================================================================== */
/*  Configuration:                                                            */
/*   * agl_log                                                                */
/*   * agl_get_log_level                                                      */
/*   * agl_set_log_level                                                      */
/* ========================================================================== */

/*! */
typedef enum agl_log_level {
  /*! Log nothing. */
  AGL_LOG_NOTHING = 0,
  /*! Log non-recoverable errors. */
  AGL_LOG_ERROR = 1,
  /*! Log warning messages. */
  AGL_LOG_WARNING = 2,
  /*! Log normal messages. */
  AGL_LOG_INFO = 3,
  /*! Log useful debug information. */
  AGL_LOG_DEBUG = 4,
  /*! Log everything. */
  AGL_LOG_SPEW = 5
} agl_log_level_t;

/* ========================================================================== */
/*  agl_log:                                                                  */
/* ========================================================================== */

/*! */
extern AGL_EXPORT void agl_log(const agl_log_level_t lvl, const char *fmt, ...);

/* ========================================================================== */
/*  agl_get_log_level:                                                        */
/* ========================================================================== */

/*! */
extern AGL_EXPORT agl_log_level_t agl_get_log_level(void);

/* ========================================================================== */
/*  agl_set_log_level:                                                        */
/* ========================================================================== */

/*! */
extern AGL_EXPORT agl_log_level_t agl_set_log_level(const agl_log_level_t lvl);

/* ========================================================================== */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _AGL_LOG_H_ */
