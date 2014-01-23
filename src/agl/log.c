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
 #  include <agl/log.h>
/* ========================================================================== */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ========================================================================== */
/*  Configuration:                                                            */
/*   * agl_log                                                                */
/*   * agl_get_log_level                                                      */
/*   * agl_set_log_level                                                      */
/* ========================================================================== */

static agl_log_level_t log_level_ = AGL_LOG_NOTHING;

/* ========================================================================== */
/*  agl_log:                                                                  */
/* ========================================================================== */

void agl_log(const agl_log_level_t level, const char *format, ...) {
  if (level > log_level_)
    return;
  /* TODO(mtwilliams): Expose a ogger interface. */
  va_list va;
  va_start(va, format);
  vfprintf(stdout, format, va);
  va_end(va);
}

/* ========================================================================== */
/*  agl_get_log_level:                                                        */
/* ========================================================================== */

agl_log_level_t agl_get_log_level(void) {
  return log_level_;
}

/* ========================================================================== */
/*  agl_set_log_level:                                                        */
/* ========================================================================== */

agl_log_level_t agl_set_log_level(const agl_log_level_t level) {
  const agl_log_level_t previous = log_level_;
  log_level_ = level;
  return previous;
}

/* ========================================================================== */

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* ========================================================================== */
