//===-- gala.cc -----------------------------------------------*- C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//

#include "gala.h"

GALA_BEGIN_EXTERN_C

// HACK(mtwilliams): Force nVidia and AMD drivers to use discrete GPU.
#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  __declspec(dllexport) unsigned long NvOptimusEnablement = 1;
  __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
#endif

void __gala__(void) {
  // HACK(mtwilliams): Export at least one symbol. This is to make sure shitty
  // linkers like Microsoft's actually produce a dynamically-linked library.
}

GALA_END_EXTERN_C
