//===-- gala/foundation.h ---------------------------------------*- C++ -*-===//
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
/// \brief Imports Foundation.
///
//===----------------------------------------------------------------------===//

#ifndef _GALA_FOUNDATION_H_
#define _GALA_FOUNDATION_H_

//============================================================================//

#include "gala/config.h"

//===----------------------------------------------------------------------===//

#ifndef __BITBYTE_FOUNDATION_IMPORT__
  #define __BITBYTE_FOUNDATION_IMPORT__
#endif // __BITBYTE_FOUNDATION_IMPORT__

#include "bitbyte/foundation/tier0.h"
#include "bitbyte/foundation/tier1.h"
#include "bitbyte/foundation/tier2.h"
#include "bitbyte/foundation/tier3.h"
#include "bitbyte/foundation/tier4.h"

#undef __BITBYTE_FOUNDATION_IMPORT__

//============================================================================//

/// \def gala_assert
/// \copydoc bitbyte_gala_assert
#define gala_assert bitbyte_foundation_assert

//===----------------------------------------------------------------------===//

/// \def gala_assertf
/// \copydoc bitbyte_gala_assertf
#define gala_assertf bitbyte_foundation_assertf

//===----------------------------------------------------------------------===//

/// \def gala_assertf_always
/// \copydoc bitbyte_gala_assertf_always
#define gala_assertf_always(_Format, ...) \
  bitbyte_foundation_assertf(0, _Format, ##__VA_ARGS__)

//===----------------------------------------------------------------------===//

/// \def gala_assert_debug
/// \copydoc bitbyte_foundation_assert
#if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
  #define gala_assert_debug bitbyte_foundation_assert
#else
  #define gala_assert_debug
#endif

/// \def gala_assertf_debug
/// \copydoc bitbyte_foundation_assertf
#if GALA_CONFIGURATION == GALA_CONFIGURATION_DEBUG
  #define gala_assertf_debug bitbyte_foundation_assertf
#else
  #define gala_assertf_debug
#endif

//===----------------------------------------------------------------------===//

/// \def gala_assert_development
/// \copydoc bitbyte_foundation_assert
#if GALA_CONFIGURATION == GALA_CONFIGURATION_DEVELOPMENT
  #define gala_assert_development bitbyte_foundation_assert
#else
  #define gala_assert_development
#endif

/// \def gala_assertf_development
/// \copydoc bitbyte_foundation_assertf
#if GALA_CONFIGURATION == GALA_CONFIGURATION_DEVELOPMENT
  #define gala_assertf_development bitbyte_foundation_assertf
#else
  #define gala_assertf_development
#endif

//===----------------------------------------------------------------------===//

/// \def gala_assert_release
/// \copydoc bitbyte_foundation_assert
#if GALA_CONFIGURATION == GALA_CONFIGURATION_RELEASE
  #define gala_assert_release bitbyte_foundation_assert
#else
  #define gala_assert_release
#endif

/// \def gala_assertf_release
/// \copydoc bitbyte_foundation_assertf
#if GALA_CONFIGURATION == GALA_CONFIGURATION_RELEASE
  #define gala_assertf_release bitbyte_foundation_assertf
#else
  #define gala_assertf_release
#endif

//============================================================================//

#endif // _GALA_FOUNDATION_H_

//============================================================================//
