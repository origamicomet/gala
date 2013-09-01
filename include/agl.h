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

#ifndef _AGL_CONF_H_
  #include <agl_conf.h>
#endif /* _AGL_CONF_H_ */

#if defined(AGL_DEBUG_BUILD)
  #define AGL_BUILD "dbg"
  #define AGL_BUILD_SUFFIX "-dbg"
#elif defined(AGL_RELEASE_BUILD)
  #define AGL_BUILD ""
  #define AGL_BUILD_SUFFIX ""
#else
  #define AGL_BUILD "unknown"
  #define AGL_BUILD_SUFFIX ""
#endif

/* Tries to auto-detect the compiler based on preprocessor macros: */
#ifndef AGL_DONT_AUTODETECT_COMPILER
/* Microsoft Visual Studio C/C++: */
#if defined(_MSC_VER)
  #define AGL_COMPILER "msvc"
  #define AGL_COMPILER_MSVC _MSC_VER
  #define AGL_MICROSOFT_VISUAL_STUDIO_2012 1700
  #define AGL_MICROSOFT_VISUAL_STUDIO_2010 1600
  #define AGL_MICROSOFT_VISUAL_STUDIO_2008 1500
  #define AGL_MICROSOFT_VISUAL_STUDIO_2005 1400
  #define AGL_MICROSOFT_VISUAL_STUDIO_2003 1310
/* Clang / LLVM: */
#elif defined(__clang__)
  #define AGL_COMPILER "clang/llvm"
  #define AGL_COMPILER_CLANG \
    ((__clang_major__ * 100) + (__clang_minor__ * 10) + (__clang_patchlevel__ * 1))
/* GCC: */
#elif (defined(__GNUC__) || defined(__GNUG__)) && !(defined(__clang__) || defined(__INTEL_COMPILER))
  #define AGL_COMPILER "gcc"
  #if (__GNUC__ >= 3)
    #define AGL_COMPILER_GCC \
      ((__GNUC__ * 100) + (__GNUC_MINOR__ * 10) + (__GNUC_PATCHLEVEL__ * 1))
  #else
    #define AGL_COMPILER_GCC \
      ((__GNUC__ * 100) + (__GNUC_MINOR__ * 10)
  #endif
/* Intel C/C++ Compiler: */
#elif defined(__ICC) || defined(__INTEL_COMPILER)
  #define AGL_COMPILER "icc"
  #define AGL_COMPILER_ICC __INTEL_COMPILER
#else
  #error("Unknown or unsupported C/C++ compiler!")
#endif
#endif /* AGL_DONT_AUTODETECT_COMPILER */

/* Tries to auto-detect the target platform based on preprocessor macros: */
#ifndef AGL_DONT_AUTODETECT_PLATFORM
#if defined(_WIN32) || defined(_WIN64)
  #define AGL_PLATFORM "windows"
  #define AGL_PLATFORM_WINDOWS 1
#elif defined(__APPLE__)
  #include <TargetConditionals.h>
  #if defined(TARGET_OS_IPHONE)
    #define AGL_PLATFORM "ios"
    #define AGL_PLATFORM_IOS 1
    #define AGL_PLATFORM_POSIX 1
  #else
    #define AGL_PLATFORM "osx"
    #define AGL_PLATFORM_MACOSX 1
    #define AGL_PLATFORM_POSIX 1
  #endif
#elif defined(ANDROID)
  #define AGL_PLATFORM "android"
  #define AGL_PLATFORM_ANDROID 1
  #define AGL_PLATFORM_POSIX 1
#elif defined(__native_client__)
  #define AGL_PLATFORM "nacl"
  #define AGL_PLATFORM_NATIVE_CLIENT 1
#elif defined(__FreeBSD__)
  #define AGL_PLATFORM "freebsd"
  #define AGL_PLATFORM_FREEBSD 1
  #define AGL_PLATFORM_BSD 1
  #define AGL_PLATFORM_POSIX 1
#elif defined(__NetBSD__)
  #define AGL_PLATFORM "netbsd"
  #define AGL_PLATFORM_NETBSD 1
  #define AGL_PLATFORM_BSD 1
  #define AGL_PLATFORM_POSIX 1
#elif defined(__OpenBSD__)
  #define AGL_PLATFORM "openbsd"
  #define AGL_PLATFORM_OPENBSD 1
  #define AGL_PLATFORM_BSD 1
  #define AGL_PLATFORM_POSIX 1
#elif defined(__DragonflyBSD__)
  #define AGL_PLATFORM "dragonflybsd"
  #define AGL_PLATFORM_DRAGONFLYBSD 1
  #define AGL_PLATFORM_BSD 1
  #define AGL_PLATFORM_POSIX 1
#elif defined(__linux__)
  #define AGL_PLATFORM "linux"
  #define AGL_PLATFORM_LINUX 1
  #define AGL_PLATFORM_POSIX 1
#else
  #error("Unknown or unsupported platform!")
#endif
#endif /* AGL_DONT_AUTODETECT_PLATFORM */

/* Tries to auto-detect the target architecture based on preprocessor macros: */
#ifndef AGL_DONT_AUTODETECT_ARCHITECTURE
#if defined(_M_X64) || defined(__x86_64__)
  #define AGL_ARCHITECTURE "x86_64"
  #define AGL_ARCHITECTURE_X86 1
  #define AGL_ARCHITECTURE_X86_64 1
  #define AGL_ARCHITECTURE_64_BIT 1
  #define AGL_ARCHITECTURE_LITTLE_ENDIAN 1
#elif defined(_M_IX86) || defined(__i386__)
  #define AGL_ARCHITECTURE "x86"
  #define AGL_ARCHITECTURE_X86 1
  #define AGL_ARCHITECTURE_32_BIT 1
  #define AGL_ARCHITECTURE_LITTLE_ENDIAN 1
#elif defined(__ARMEL__)
  #define AGL_ARCHITECTURE "arm"
  #define AGL_ARCHITECTURE_ARM 1
  #define AGL_ARCHITECTURE_32_BIT 1
  #define AGL_ARCHITECTURE_LITTLE_ENDIAN 1
#elif defined(__pnacl__)
  #define AGL_ARCHITECTURE "nacl/bytecode"
  #define AGL_ARCHITECTURE_32_BIT 1
  #define AGL_ARCHITECTURE_LITTLE_ENDIAN 1
#elif defined(__MIPSEL__)
  #define AGL_ARCHITECTURE "mips"
  #define AGL_ARCHITECTURE_MIPS 1
  #define AGL_ARCHITECTURE_32_BIT 1
  #define AGL_ARCHITECTURE_LITTLE_ENDIAN 1
#else
  #error("Unknown or unsupported architecture!")
#endif
#endif /* AGL_DONT_AUTODETECT_ARCHITECTURE */

/* Defines AGL_API based on a configuration: */
#if defined(AGL_STATICALLY_LINKING)
  #define AGL_API
#elif defined(AGL_COMPILER_MSVC)
  #define AGL_RUNTIME __declspec(dllexport)
  #if defined(AGL_COMPILING)
    #define AGL_API __declspec(dllexport)
  #else
    #define AGL_API __declspec(dllimport)
  #endif
#else
  #define AGL_API
#endif

#include <agl_stdbool.h>
#include <agl_stdint.h>
#include <agl_inttypes.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* 1. Base types and definitions: */

/*! Represents an error or success state. */
typedef enum agl_err {
  /*! No error; success. */
  AGL_ENONE                 =  0,
  /*! One or more supplied arguments were invalid. */
  AGL_EINVALIDARG           = -1,
  /*! Unable to enqueue command due the specifed command list being exhausted. */
  AGL_ECOMMANDLISTEXHAUSTED = -2,
  /*! An underlying implemention or interface encountered an error. */
  AGL_ERUNTIME              = -3,
  /*! Unknown (usually a specific corner case). */
  AGL_EUNKNOWN              = -4,
} agl_err_t;

/*! @def AGL_UNANSWERED
  An invalid response, represents an unanswered/unfulfilled request. */
#define AGL_UNANSWERED ((uint)(0xffffffffffffffffull))

#define AGL_PIXEL_FORMAT_COLOR (1 << 31)
#define AGL_PIXEL_FORMAT_DEPTH (1 << 30)
#define AGL_PIXEL_FORMAT_STENCIL (1 << 29)
#define AGL_PIXEL_FORMAT_COMPRESSED (1 << 28)

/*! A per-component pixel format. */
typedef enum agl_pixel_format {
  AGL_R8G8B8A8 = 1 | AGL_PIXEL_FORMAT_COLOR,
} agl_pixel_format_t;

/* 2. Runtime: */

/*! Represents an underlying graphics interface. */
typedef enum agl_runtime {
  /*! OpenGL 2.1+. */
  AGL_OPENGL    = 1,
  /*! OpenGL ES 2+. */
  AGL_OPENGL_ES = 2,
  /*! Direct3D 9. */
  AGL_D3D9      = 3,
  /*! Direct3D 11 (with feature level support for 10). */
  AGL_D3D1x     = 4,
  /*! GCM. */
  AGL_GCM       = 5,
} agl_runtime_t;

/*! Determines if the `runtime` is supported by the current platform.

  @param[in] runtime The runtime to check for support.

  @returns True if the runtime is supported; or
           false if the runtime is not supported. */
extern AGL_API bool agl_is_runtime_supported(
  const agl_runtime_t runtime);

/*! Specifies an underlying graphics interface to use.

  @param[in] runtime The runtime to use.

  @returns AGL_ENONE if the specified runtime is now used; or
           AGL_EINVALIDARG if the specified runtime is not supported; or
           AGL_EUNKNOWN if the runtime could not be loaded. */
extern AGL_API agl_err_t agl_use_runtime(
  const agl_runtime_t runtime);

/* 3. Adapters and outputs: */

/*! */
typedef enum agl_driver {
  /*! */
  AGL_SOFTWARE = 1u,
  /*! */
  AGL_HARDWARE = 2u,
} agl_driver_t;

/*! */
typedef struct agl_display_mode {
  agl_pixel_format_t format;
  uint32_t width;
  uint32_t height;
} agl_display_mode_t;

/*! */
typedef size_t agl_display_mode_id_t;

/*! */
typedef struct agl_output {
  size_t num_of_display_modes;
  const agl_display_mode_t *display_modes;
} agl_output_t;

/*! */
typedef size_t agl_output_id_t;

/*! */
typedef struct agl_adapter {
  agl_driver_t driver;
  size_t memory;
  size_t num_of_outputs;
  const agl_output_t *outputs;
} agl_adapter_t;

/*! */
typedef size_t agl_adapter_id_t;

/*! Determines the number of currently available adapters.

  @param[out] num_of_adapters A pointer to the number of available adapters.

  @returns AGL_ENONE if the query was succesful. */
extern AGL_API agl_err_t agl_get_num_of_adapters(
  size_t *num_of_adapters);

/*! Gets a description of the adapter specifed by `id`.

  @param[in] id The adapter to query (from 0 to aglGetNumOfAdapters()).

  @returns A valid pointer if the specifed adapter exists; or
           null if the specifed adapter does not exist. */
extern AGL_API const agl_adapter_t *agl_get_adapter(
  const agl_adapter_id_t id);

/* 4. Command Lists: */

/*! A user controlled slice of memory used to queue up platform and runtime
  independent commands. */
typedef struct agl_command_list {
  uintptr_t start;
  uintptr_t end;
  uintptr_t current;

  /*! Called when there is not enough space left to accomodate a command.

    @param[in,out] command_list The command list the must be resized.
    @param[in]     len          The new length required to accomodate a command.

    @return True if the command list was resized to accomodate the command; or
            false if the command list was not resized and unable to accomodate
            the command. */
  bool (*exhausted)(
    struct agl_command_list *command_list,
    const size_t len);
} agl_command_list_t;

/* 5. Contexts: */
typedef struct agl_context agl_context_t;

/*! Creates a context that is used to call underlying graphics interface.

  @param[in]     adapter The adapater to use for underlying calls.
  @param[in,out] context A pointer to the created context.

  @returns AGL_ENONE if context creation was successful; or
           AGL_EINVALIDARG if one or more arguments were invalid; or
           AGL_ERUNTIME if the underlying implementation encountered an error. */
extern AGL_API agl_err_t agl_create_context(
  const agl_adapter_id_t adapter,
  agl_context_t **context);

/*! Consumes a command list, generating calls to underlying graphics interface.

  @param[in] context      The context to generate calls to.
  @param[in] command_list The command list to consume.

  @returns AGL_ENONE if the command list was succesfully queued; or
           AGL_ERUNTIME if one or more commands was unrecognized or ill-formed. */
extern AGL_API agl_err_t agl_dispatch(
  agl_context_t *context,
  const agl_command_list_t *command_list);

/*! Destroys a context (and all associated resources).

  @param[in] context The context to destroy.

  @returns AGL_ENONE if the context was succesfully destroyed. */
extern AGL_API agl_err_t agl_destroy_context(
  agl_context_t *context);

/* 6. Resources: */

/*! An opaque handle to a resource. */
typedef uintptr_t agl_id_t;

/*! @def AGL_INVALID_ID
  An invalid id, represents non-availability or error. */
#define AGL_INVALID_ID ((agl_id_t)0xFFFFFFFFFFFFFFFFull)

/*! Enqueues a command in `command_list` that determines if the resource
  specified by `id` is existent (created or a valid id).

  For example, calling agl_is_available() on a texture after calling
  agl_delete_texture() would determine if the user-allocated id can be freed.

  @param[in,out] command_list The command list to enqueue the command to.
  @param[in]     id           A pointer to an id that specifies a resource.
  @param[out]    avail        A pointer to uint that specifies the state of the
                              resource. It is set to AGL_UNANSWERED until the
                              request is fulfilled, at which point it is either
                              `0` or `1`. A value of `0` indicates that the
                              resource is unavailable. A value of `1` indicates
                              that the resource is available.

  @returns AGL_ENONE if the command was succesfully queued; or
           AGL_ECOMMANDLISTEXHAUSTED if the the command could not be enqueued. */
extern AGL_API agl_err_t agl_is_available(
  agl_command_list_t *command_list,
  const volatile agl_id_t *id,
  volatile uint *avail);

/*! Immediately determines if the resource specified by `id` is existent (created
  or a valid id).

  @param[in,out] context The context the resource belongs to.
  @param[in]     id      A pointer to an id that specifies a resource.

  @returns True if the resource is existent; or
           false if the resource is non-existent. */
extern AGL_API bool agl_is_available_sync(
  agl_context_t *context,
  const volatile agl_id_t *id);

/*! Enqueues a command in `command_list` that determines if the resource
  specified by `id` has no outstanding operations (is reflective of requested state).

  For example, calling agl_is_reflective() on texture after calling
  agl_tex_storage() would determine if the source data can be safely freed.

  @param[in,out] command_list The command list to enqueue the command to.
  @param[in]     id           A pointer to an id that specifies a resource.
  @param[out]    reflective   A pointer to uint that specifies the state of the
                              resource. It is set to AGL_UNANSWERED until the
                              request is fulfilled, at which point it is either
                              `0` or `1`. A value of `0` indicates that the
                              resource has outstanding operations. A value of
                              `1` indicates that the resource has no outstanding
                              operations.

  @returns AGL_ENONE if the command was succesfully queued; or
           AGL_ECOMMANDLISTEXHAUSTED if the the command could not be enqueued. */
extern AGL_API agl_err_t agl_is_reflective(
  agl_command_list_t *command_list,
  volatile agl_id_t *id,
  volatile uint *reflective);

/*! Immediately determines if the resource specified by `id` has no outstanding
  operations (is reflective of requested state).

  @param[in,out] context The context the resource belongs to.
  @param[in]     id      A pointer to an id that specifies a resource.

  @returns True if the resource is reflective of requested state; or
           false if the resource is not reflective of requested state; or
           false if the resource is non-existent (an invalid id). */
extern AGL_API bool agl_is_reflective_sync(
  agl_context_t *context,
  volatile agl_id_t *id);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _AGL_H_ */
