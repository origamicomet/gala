/*
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org/>
 */

#ifndef _AGL_H_
#define _AGL_H_

#include <agl/config.h>
#include <agl/detect.h>
#include <agl/compat.h>
#include <agl/api.h>
#include <agl/atomic.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ==========================================================================
    Errors (agl_error_t):
   ========================================================================== */

/*! Represents error or success. */
typedef enum agl_err {
  /*! No error; success. */
  AGL_ENONE       = 0,
  /*! One or more supplied arguments were invalid. */
  AGL_EINVALIDARG = -1,
  /*! Failed, but don't know why. */
  AGL_EUNKNOWN    = -2
} agl_err_t;

/* ==========================================================================
    Requests (agl_request_t):
   ========================================================================== */

/*!  */
typedef uint agl_request_t;

/*! */
typedef uint agl_request_response_t;

/*! @def AGL_FULFILLED_REQUEST
  Represents an answered or fulfilled request. */
#define AGL_FULFILLED_REQUEST ((uintptr_t)0x0000000000000000ull)

/*! @def AGL_UNFULFILLED_REQUEST
  Represents an unanswered or unfulfilled request. */
#define AGL_UNFULFILLED_REQUEST ((uintptr_t)0xffffffffffffffffull)

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* ==========================================================================
    C++ Wrapper/Interface:
   ========================================================================== */

#ifdef __cplusplus
namespace agl {
  namespace Error {
    /*! See agl_err_t. */
    enum _ {
      /*! See agl_err_t::AGL_ENONE. */
      None       = ::AGL_ENONE,
      /*! See agl_err_t::AGL_EINVALIDARG. */
      InvalidArg = ::AGL_EINVALIDARG,
      /*! See agl_err_t::AGL_EUNKNOWN. */
      Unknown    = ::AGL_EUNKNOWN
    };
  } typedef Error::_ Error_;

  /*! See agl_request_t. */
  class Request {
    private:
      Request(const Request &);
      Request& operator=(const Request &);

    public:
      Request()
        : _(AGL_UNFULFILLED_REQUEST)
      {}

      ~Request()
      {}

    public:
      /*! Determines if the requested has been fulfilled or answered. */
      bool is_fulfilled() const {
        return (agl_atomic_compr_and_swap(
          (volatile uint *)&_,
          AGL_UNFULFILLED_REQUEST,
          AGL_UNFULFILLED_REQUEST
        ) != AGL_UNFULFILLED_REQUEST);
      }

      /*! See Request::is_fulfilled. */
      bool is_answered() const
      { return is_fulfilled(); }

      /*! Determines if the requested has not been fulfilled or answered. */
      bool is_not_fulfilled() const {
        return (agl_atomic_compr_and_swap(
          (volatile uint *)&_,
          AGL_UNFULFILLED_REQUEST,
          AGL_UNFULFILLED_REQUEST
        ) == AGL_UNFULFILLED_REQUEST);
      }

      /*! See Request::is_not_fulfilled. */
      bool is_not_answered() const
      { return is_not_fulfilled(); }

      /*! Gets the associated response. */
      const agl_request_response_t &response() const
      { return _response; }

    public: /* pseduo-private: */
      mutable agl_request_t _;
      agl_request_response_t _response;
  };
} /* agl */
#endif /* __cplusplus */

#endif /* _AGL_H_ */
