//===-- gala/compat/alignof.h -----------------------------------*- C++ -*-===//
//
//  Gala
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//    * Michael Williams <mike@origamicomet.com>
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Provide a fallback implementation of _Alignof and alignof.
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_COMPAT_ALIGNOF_H_
#define _GALA_COMPAT_ALIGNOF_H_

//============================================================================//

#if defined(__cplusplus)
  // Bless me, Father, for I have sinned.
  template <typename _Type> struct __gala_alignof;
  template <int _SzDiff> struct __gala_alignof_ {
    template <typename _Type> struct E { enum { _ = _SzDiff }; }; };
  template <> struct __gala_alignof_<0> {
    template <typename _Type> struct E { enum { _ = __gala_alignof<_Type>::_ }; }; };
  template <typename _Type> struct __gala_alignof {
    struct C { _Type __; char _; };
    enum { D = (sizeof(C) - sizeof(_Type)), _ = __gala_alignof_<D>::template E<C>::_ }; };
  #define __gala_alignof__(_Type) ((size_t)__gala_alignof<_Type>::_)
#else
  #define __gala_alignof__(_Type) ((size_t)offsetof(struct{char _; _Type __;},__))
#endif

//===----------------------------------------------------------------------===//

#if defined(_MSC_VER)
  // Prevent xkeycheck.h from bitching about redefining keywords in 2012+.
  // See http://msdn.microsoft.com/en-us/library/bb531344.aspx.
  #define _ALLOW_KEYWORD_MACROS

  // Microsoft Visual Studio 2010
  #if _MSC_VER < 1600
    #define alignof __gala_alignof__
    #define _Alignof __gala_alignof__
  #else
    #define alignof __alignof
    #define _Alignof __alignof
  #endif
#else
  #ifndef __alignof_is_defined
    #define alignof __gala_alignof__
    #define _Alignof __gala_alignof__
    #define __alignof_is_defined 1
  #else // ifdef __alignof_is_defined
  #endif
#endif

//============================================================================//

#endif // _GALA_COMPAT_ALIGNOF_H_

//============================================================================//
