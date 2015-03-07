/*===-- gala/command.h ------------------------------------------*- C++ -*-===*/
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

#ifndef _GALA_COMMAND_H_
#define _GALA_COMMAND_H_

/*============================================================================*/

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"

/*===----------------------------------------------------------------------===*/

#include "gala/fence.h"

/*============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*===----------------------------------------------------------------------===*/

/*! ... */
typedef enum gala_command_type {
  /*! No operation (do nothing). */
  GALA_COMMAND_TYPE_NOP = 0,
  /*! Writes a value when Gala has submitted all previous commands. */
  GALA_COMMAND_TYPE_FENCE_ON_SUBMISSION = 1,
  /*! Writes a value when the GPU has processed all previous commands.
   *  \warning This can take a substantial amount of time, and may even stall,
   *           on some backends.
   */
  GALA_COMMAND_TYPE_FENCE_ON_COMPLETION = 2,
  /*! \internal Force at least uint32_t storage and alignment. */
  GALA_COMMAND_TYPEE_FORCE_UINT32 = 0x7fffffff
} gala_command_type_t;

/*===----------------------------------------------------------------------===*/

/*! ... */
typedef struct gala_command {
  /*! ... */
  gala_command_type_t type;
  /*! ... */
  size_t len;
} gala_command_t;

/*===----------------------------------------------------------------------===*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*============================================================================*/

#endif /* _GALA_COMMAND_H_ */

/*============================================================================*/
