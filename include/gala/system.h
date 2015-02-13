//===-- gala/system.h -------------------------------------------*- C++ -*-===//
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
/// \brief
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_SYSTEM_H_
#define _GALA_SYSTEM_H_

//============================================================================//

#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
  #endif
  #ifndef WIN32_EXTRA_LEAN
    #define WIN32_EXTRA_LEAN
  #endif

  #include <windows.h>

  #undef NEAR
  #undef FAR
  #undef near
  #undef far
  #undef NO_ERROR
  #undef ERROR
  #undef MK_SHIFT
  #undef MK_ALT
  #undef min
  #undef max
  #undef rad1

  #undef WIN32_EXTRA_LEAN
  #undef WIN32_LEAN_AND_MEAN
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM __BITBYTE_FOUNDATION_TIER0_SYSTEM_ANDROID__
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM __BITBYTE_FOUNDATION_TIER0_SYSTEM_IOS__
#endif

//============================================================================//

#endif // _GALA_SYSTEM_H_

//============================================================================//
