//===-- agl/compat/alignof.h ------------------------------------*- C++ -*-===//
//
//  Abstract Graphics Library (AGL)
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//    * Michael Williams <mwilliams@bitbyte.ca>
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Provide a fallback implementation of _Alignof and alignof.
///
//===----------------------------------------------------------------------===//

#ifndef _AGL_COMPAT_ALIGNOF_H_
#define _AGL_COMPAT_ALIGNOF_H_

//============================================================================//

#if defined(__cplusplus)
  // Bless me, Father, for I have sinned.
  template <typename _Type> struct __agl_alignof;
  template <int _SzDiff> struct __agl_alignof_ {
    template <typename _Type> struct E { enum { _ = _SzDiff }; }; };
  template <> struct __agl_alignof_<0> {
    template <typename _Type> struct E { enum { _ = __agl_alignof<_Type>::_ }; }; };
  template <typename _Type> struct __agl_alignof {
    struct C { _Type __; char _; };
    enum { D = (sizeof(C) - sizeof(_Type)), _ = __agl_alignof_<D>::template E<C>::_ }; };
  #define __agl_alignof__(_Type) ((size_t)__agl_alignof<_Type>::_)
#else
  #define __agl_alignof__(_Type) ((size_t)offsetof(struct{char _; _Type __;},__))
#endif

//===----------------------------------------------------------------------===//

#if defined(_MSC_VER)
  // Prevent xkeycheck.h from bitching about redefining keywords in 2012+.
  // See http://msdn.microsoft.com/en-us/library/bb531344.aspx.
  #define _ALLOW_KEYWORD_MACROS

  // Microsoft Visual Studio 2010
  #if _MSC_VER < 1600
    #define alignof __agl_alignof__
    #define _Alignof __agl_alignof__
  #else
    #define alignof __alignof
    #define _Alignof __alignof
  #endif
#else
  #ifndef __alignof_is_defined
    #define alignof __agl_alignof__
    #define _Alignof __agl_alignof__
    #define __alignof_is_defined 1
  #else // ifdef __alignof_is_defined
  #endif
#endif

//============================================================================//

#endif // _AGL_COMPAT_ALIGNOF_H_

//============================================================================//
