/*===-- gala/commands.h -----------------------------------------*- C++ -*-===*/
/*
 *  Gala
 *
 *  This file is distributed under the terms described in LICENSE.
 *
 *  Author(s):
 *
 *    * Michael Williams <mike@origamicomet.com>
 *                                                                            */
/*===----------------------------------------------------------------------===*/
/*!
 *  \file
 *  \brief
 *                                                                            */
/*===----------------------------------------------------------------------===*/

#ifndef _GALA_COMMANDS_H_
#define _GALA_COMMANDS_H_

/*============================================================================*/

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"

/*===----------------------------------------------------------------------===*/

#include "gala/command.h"

/*============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*===----------------------------------------------------------------------===*/

/*! ... */
typedef struct gala_command_nop {
  struct gala_command __command__;
} gala_command_nop_t;

/*===----------------------------------------------------------------------===*/

/*! ... */
typedef struct gala_command_fence {
  struct gala_command __command__;
  gala_fence_t fence;
  gala_fence_t *writeback;
} gala_command_fence_t;

/*===----------------------------------------------------------------------===*/

#ifdef __cplusplus
}
#endif // __cplusplus

/*============================================================================*/

#endif // _GALA_COMMANDS_H_

/*============================================================================*/
