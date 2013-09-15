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
#include <agl/alignof.h>
#include <agl/assert.h>
#include <agl/atomic.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ========================================================================== */
/*  Integration:                                                              */
/*   * Errors & Error Handling                                                */
/*   * Memory Management                                                      */
/* ========================================================================== */

/* ==========================================================================
    Errors (agl_err_t):
   ========================================================================== */

/*! Represents error or success. */
typedef enum agl_err {
  /*! No error; success. */
  AGL_ENONE        = 0,
  /*! One or more supplied arguments were invalid. */
  AGL_EINVALIDARG  = -1,
  /*! Failed, but don't know why. */
  AGL_EUNKNOWN     = -2,
  /*! Ran out of memory. */
  AGL_EOUTOFMEMORY = -3
} agl_err_t;

/* ========================================================================== */

/*! A user-defined error handler.
  @note If the handler returns a SIGABRT signal will be raised. */
typedef void (*agl_error_handler_fn)(
  const agl_err_t error);

/*! Gets the user-defined error handler.
  @returns The user-defiend error handler. */
extern AGL_API agl_error_handler_fn agl_error_handler();

/*! Sets the user-defined error handler.
  @params[in] handler The user-defined error handler to use. */
extern AGL_API void agl_set_error_handler(
  agl_error_handler_fn handler);

/* ==========================================================================
    Allocators (agl_allocator_t):
   ========================================================================== */

/*! */
typedef struct agl_allocator {
  void *(*alloc)(
    struct agl_allocator *allocator,
    const size_t num_of_bytes,
    const size_t alignment);

  void *(*realloc)(
    struct agl_allocator *allocator,
    void *ptr,
    const size_t num_of_bytes,
    const size_t alignment);

  void (*free)(
    struct agl_allocator *allocator,
    void *ptr);
} agl_allocator_t;

/* ========================================================================== */

/*! */
extern AGL_API agl_allocator_t *agl_allocator();

/*! */
extern AGL_API void agl_set_allocator(
  agl_allocator_t *allocator);

/* ========================================================================== */
/*  Common/Types:                                                             */
/*   * Pixel Formats                                                          */
/* ========================================================================== */

/* ==========================================================================
    Pixel Formats (agl_pixel_format_t):
   ========================================================================== */

/*! @def AGL_PIXEL_FORMAT_IS_COLOR
  Specifies a pixel format that supports color. */
#define AGL_PIXEL_FORMAT_IS_COLOR (1 << 31)

/*! @def AGL_PIXEL_FORMAT_IS_DEPTH
  Specifies a pixel format that supports depth. */
#define AGL_PIXEL_FORMAT_IS_DEPTH (1 << 30)

/*! @def AGL_PIXEL_FORMAT_IS_STENCIL
  Specifies a pixel format that supports stencil. */
#define AGL_PIXEL_FORMAT_IS_STENCIL (1 << 29)

/*! @def AGL_PIXEL_FORMAT_IS_COMPRESSED
  Specifies a pixel format that is compressed. */
#define AGL_PIXEL_FORMAT_IS_COMPRESSED (1 << 28)

/*! Specifies the format and type of pixel data. */
typedef enum agl_pixel_format {
  /*! An unknown pixel format. */
  AGL_PIXEL_FORMAT_UNKNOWN = 0,

  /*! A three-component, 24-bit unsigned-integer format that supports 8 bits
    per-channel excluding alpha.
    @note Can only be a back-buffer format. */
  AGL_R8G8B8 = 1 |
    AGL_PIXEL_FORMAT_IS_COLOR,

  /*! A four-component, 32-bit unsigned-integer format that supports 8 bits
    per-channel including alpha. */
  AGL_R8G8B8A8 = 2 |
    AGL_PIXEL_FORMAT_IS_COLOR,

  /*! A 32-bit depth-buffer format that supports 24 bits for depth and 8 bits
    for stencil. */
  AGL_D24_S8 = 3 |
    AGL_PIXEL_FORMAT_IS_DEPTH |
    AGL_PIXEL_FORMAT_IS_STENCIL
} agl_pixel_format_t;

/* ========================================================================== */
/*  Infrastructure:                                                           */
/*   * Adapters                                                               */
/*   * Outputs                                                                */
/*   * Display Modes                                                          */
/* ========================================================================== */

/* ==========================================================================
    Adapters (agl_adapter_t):
   ========================================================================== */

/* ... */

/* ==========================================================================
    Outputs (agl_outputs_t):
   ========================================================================== */

/* ... */

/* ==========================================================================
    Display Modes (agl_display_mode_t):
   ========================================================================== */

/* ... */

/* ========================================================================== */
/*  Runtime:                                                                  */
/*   * Contexts                                                               */
/*   * Command Lists                                                          */
/*   * Requests                                                               */
/*   * Resources                                                              */
/* ========================================================================== */

/* ==========================================================================
    Contexts (agl_context_t):
   ========================================================================== */

/* ... */

/* ==========================================================================
    Command Lists (agl_command_list_t):
   ========================================================================== */

/*! A user-controlled slice of memory used to queue up commands. */
typedef struct agl_command_list {
  /*! @defgroup Slice @{ */
  uintptr_t begin;
  uintptr_t end;
  uintptr_t current;
  /*! @} */

  /*! Called when there is not enough space left to accomodate a command.
    @param[in,out] command_list The command list that must be resized.
    @return True if the command list was resized to potentially accomodate the
            command; or false if the command list was not resized. */
  bool (*exhausted)(
    struct agl_command_list *command_list);
} agl_command_list_t;

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

/*! @def AGL_ERRORED_REQUEST
  Represents an error occuring during a request. */
#define AGL_ERRORED_REQUEST ((uintptr_t)0x0000000000000001ull)

/* ==========================================================================
    Resources (agl_resource_t):
   ========================================================================== */

/*! Specifies a resource type. */
typedef enum agl_resource_type {
  AGL_RESOURCE_TYPE_UNKNOWN = 0
} agl_resource_type_t;

/*! An opaque handle that represents a resource. */
typedef struct agl_resource {
  agl_resource_type_t _type;
  uint _ops;
  uintptr_t _internal;
} agl_resource_t;

/*! @def AGL_INVALID_RESOURCE
  A invalid resource. */
#define AGL_INVALID_RESOURCE ((agl_resource_t *)NULL)

/* ========================================================================== */

/*! Determines the resource type.
  @param[in] resource The resource.
  @returns AGL_RESOURCE_TYPE_UNKNOWN if the specifed resource is unknown or
           non-existent; or an agl_resource_type_t. */
extern AGL_API agl_resource_type_t agl_resource_type(
  const agl_resource_t *resource);

/*! Determines the number of pending operations.
  @param[in] resource The resource. */
extern AGL_API uint agl_resource_ops(
  const agl_resource_t *resource);

/* ========================================================================== */

/*! Determines if the resource is existent.
  @param[in] resource The resource.
  @returns True if the resource is existent; or
           false if the resource is non-existent. */
extern AGL_API bool agl_resource_is_available(
  const agl_resource_t *resource);

/*! Determines if the resource has any outstanding operations.
  @param[in] resource The resource.
  @returns True if the resource has not outstanding operations; or
           false if the resource ihas outstanding operations. */
extern AGL_API bool agl_resource_is_reflective(
  const agl_resource_t *resource);

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
      None        = ::AGL_ENONE,
      /*! See agl_err_t::AGL_EINVALIDARG. */
      InvalidArg  = ::AGL_EINVALIDARG,
      /*! See agl_err_t::AGL_EUNKNOWN. */
      Unknown     = ::AGL_EUNKNOWN,
      /*! See agl_err_t::AGL_EOUTOFMEMORY. */
      OutOfMemory = ::AGL_EOUTOFMEMORY
    };
  } typedef Error::_ Error_;

  /*! See agl_allocator_t. */
  class Allocator {
    private:
      Allocator(const Allocator &);
      Allocator& operator=(const Allocator &);

    protected:
      Allocator()
      {
        _self = this;
        _.alloc = &Allocator::_alloc;
        _.realloc = &Allocator::_realloc;
        _.free = &Allocator::_free;
      }

      virtual ~Allocator()
      {}

    public:
      /*! See agl_allocator_t::alloc. */
      virtual void *alloc(
        const size_t num_of_bytes,
        const size_t alignment) const = 0;

      /*! See agl_allocator_t::realloc. */
      virtual void *realloc(
        void *ptr,
        const size_t num_of_bytes,
        const size_t alignment) const = 0;

      /*! See agl_allocator_t::free. */
      virtual void free(
        void *ptr) const = 0;

    private:
      static void *_alloc(
        ::agl_allocator_t *allocator,
        const size_t num_of_bytes,
        const size_t alignment)
      {
        static const size_t offset =
          (offsetof(Allocator, _self) - offsetof(Allocator, _));
        Allocator *allocator_ =
          *(Allocator**)(((uintptr_t)allocator) + offset);
        return allocator_->alloc(num_of_bytes, alignment);
      }

      static void *_realloc(
        ::agl_allocator_t *allocator,
        void *ptr,
        const size_t num_of_bytes,
        const size_t alignment)
      {
        static const size_t offset =
          (offsetof(Allocator, _self) - offsetof(Allocator, _));
        Allocator *allocator_ =
          *(Allocator**)(((uintptr_t)allocator) + offset);
        return allocator_->realloc(ptr, num_of_bytes, alignment);
      }

      static void _free(
        ::agl_allocator_t *allocator,
        void *ptr)
      {
        static const size_t offset =
          (offsetof(Allocator, _self) - offsetof(Allocator, _));
        Allocator *allocator_ =
          *(Allocator**)(((uintptr_t)allocator) + offset);
        return allocator_->free(ptr);
      }

    public: /* private */
      ::agl_allocator_t _;
      Allocator *_self;
  };

  /*! See agl_allocator. */
  static Allocator *allocator() {
    static const size_t offset =
      (offsetof(Allocator, _self) - offsetof(Allocator, _));
    ::agl_allocator_t *allocator = agl_allocator();
    if (!allocator) return NULL;
    return *(Allocator**)(((uintptr_t)allocator) + offset);
  }

  /*! See agl_set_allocator. */
  static void set_allocator(Allocator *allocator) {
    agl_assert(debug, allocator != NULL);
    agl_set_allocator(&allocator->_);
  }

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

  namespace PixelFormat {
    /*! See AGL_PIXEL_FORMAT_IS_COLOR. */
    static const uint IsColor = AGL_PIXEL_FORMAT_IS_COLOR;

    /*! See AGL_PIXEL_FORMAT_IS_DEPTH. */
    static const uint IsDepth = AGL_PIXEL_FORMAT_IS_DEPTH;

    /*! See AGL_PIXEL_FORMAT_IS_STENCIL. */
    static const uint IsStencil = AGL_PIXEL_FORMAT_IS_STENCIL;

    /*! See AGL_PIXEL_FORMAT_IS_COMPRESSED. */
    static const uint IsCompressed = AGL_PIXEL_FORMAT_IS_COMPRESSED;

    /*! See agl_pixel_format_t. */
    enum _ {
      /*! See agl_pixel_format_t::AGL_PIXEL_FORMAT_UNKNOWN. */
      UNKNOWN =  ::AGL_PIXEL_FORMAT_UNKNOWN,
      /*! See agl_pixel_format_t::AGL_R8G8B8. */
      R8G8B8 =   ::AGL_R8G8B8,
      /*! See agl_pixel_format_t::AGL_R8G8B8A8. */
      R8G8B8A8 = ::AGL_R8G8B8A8,
      /*! See agl_pixel_format_t::AGL_D24_S8. */
      D24_S8 =   ::AGL_D24_S8
    };
  } typedef PixelFormat::_ PixelFormat_;

  /*! See agl_command_list_t. */
  typedef ::agl_command_list_t CommandList;

  /*! See agl_resource_t. */
  class Resource : private ::agl_resource_t {
    public:
      struct Type {
        /*! See agl_resource_type_t. */
        enum _ {
          /*! See agl_resource_type_t::AGL_RESOURCE_TYPE_UNKNOWN. */
          Unknown = ::AGL_RESOURCE_TYPE_UNKNOWN
        };
      }; typedef Type::_ Type_;

    private:
      Resource(const Resource &);
      Resource& operator=(const Resource &);

    protected:
      Resource()
      {}

      ~Resource()
      {}

    public:
      /*! See agl_resource_type. */
      Type_ type() const {
        return (Type_)agl_resource_type((const ::agl_resource_t *)this);
      }

      /*! See agl_resource_ops. */
      uint ops() const {
        return agl_resource_ops((const ::agl_resource_t *)this);
      }

    public:
      /*! See agl_resource_is_available. */
      bool is_available() const {
        return agl_resource_is_available((const ::agl_resource_t *)this);
      }

      /*! See agl_resource_is_reflective. */
      bool is_reflective() const {
        return agl_resource_is_reflective((const ::agl_resource_t *)this);
      }
  };
} /* agl */
#endif /* __cplusplus */

#endif /* _AGL_H_ */
