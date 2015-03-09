/*===-- gala/command_buffer.h -----------------------------------*- C++ -*-===*/
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

#ifndef _GALA_COMMAND_BUFFER_H_
#define _GALA_COMMAND_BUFFER_H_

/*============================================================================*/

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"

/*===----------------------------------------------------------------------===*/

#include "gala/command.h"

/*============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*===----------------------------------------------------------------------===*/

/*! A user-controlled slice of memory used to queue up commands. */
typedef struct gala_command_buffer {
  /*! The lowest address of the command-buffer. */
  uintptr_t start;
  /*! The highest address of the command-buffer. */
  uintptr_t end;
  /*! The lowest unoccupied address of the command-buffer. */
  uintptr_t current;

  /* Called when there is not enough space left to accomodate a command.
   * \param[in] command_buffer The command-buffer that is full.
   * \returns A non-zero value if the command-buffer can now sufficently
   * accomodate the command, or zero if the command-buffer was not resized.
   * \note You can do more than resize the command-buffer, e.g. start
   * consuming it in another thread.
   */
  bool (*exhausted)(struct gala_command_buffer *command_buffer);
} gala_command_buffer_t;

/*===----------------------------------------------------------------------===*/

/*! \brief Initializes a command-buffer to sane and helpful defaults.
 *  \param[out] command_buffer The command-buffer to initialize.
 */
extern GALA_PUBLIC void
gala_command_buffer_init(
  struct gala_command_buffer *command_buffer);

/*===----------------------------------------------------------------------===*/

/*! */
extern GALA_PUBLIC void *
gala_command_buffer_insert_yielded(
  struct gala_command_buffer *command_buffer,
  const size_t command_len);

/*! */
extern GALA_PUBLIC void
gala_command_buffer_insert_yielded_finish(
  struct gala_command_buffer *command_buffer,
  void *command);

/*===----------------------------------------------------------------------===*/

/*! */
extern GALA_PUBLIC void
gala_command_buffer_insert_nop(
  struct gala_command_buffer *command_buffer);

/*===----------------------------------------------------------------------===*/

/*! */
extern GALA_PUBLIC void
gala_command_buffer_insert_fence_on_submission(
  struct gala_command_buffer *command_buffer,
  gala_fence_t fence,
  gala_fence_t *writeback);

/*===----------------------------------------------------------------------===*/

/*! */
extern GALA_PUBLIC void
gala_command_buffer_insert_fence_on_completion(
  struct gala_command_buffer *command_buffer,
  gala_fence_t fence,
  gala_fence_t *writeback);

/*===----------------------------------------------------------------------===*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*============================================================================*/

#ifdef __cplusplus

/*===----------------------------------------------------------------------===*/

namespace gala {

/*===----------------------------------------------------------------------===*/

/*! \copydoc ::gala_command_buffer_t */
class GALA_PUBLIC CommandBuffer {
 protected:
  CommandBuffer();
  CommandBuffer(const CommandBuffer &command_buffer);
  CommandBuffer &operator=(const CommandBuffer &command_buffer);
  virtual ~CommandBuffer();

 public:
  /*! Returns the underlying ::gala_command_buffer_t. */
  ::gala_command_buffer_t *underlying() { return &__command_buffer__; }

  /*! Returns the underlying ::gala_command_buffer_t. */
  const ::gala_command_buffer_t *underlying() const { return &__command_buffer__; }

 public:
  /*! \copydoc ::gala_command_buffer::exhausted */
  virtual bool exhausted();

 public:
  /*! \copydoc ::gala_command_buffer_insert_nop */
  void insert_nop();

  /*! \copydoc ::gala_command_buffer_insert_fence_on_submission */
  void insert_fence_on_submission(::gala::Fence fence, ::gala::Fence *writeback);

  /*! \copydoc ::gala_command_buffer_insert_fence_on_completion */
  void insert_fence_on_completion(::gala::Fence fence, ::gala::Fence *writeback);

 private:
  ::gala_command_buffer_t __command_buffer__;
};

/*===----------------------------------------------------------------------===*/

} /* gala */

/*===----------------------------------------------------------------------===*/

#endif /* __cplusplus */

/*============================================================================*/

#endif /* _GALA_COMMAND_BUFFER_H_ */

/*============================================================================*/
