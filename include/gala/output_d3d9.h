//===-- gala/output_d3d9.h --------------------------------------*- C++ -*-===//
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

#ifndef _GALA_OUTPUT_D3D9_H_
#define _GALA_OUTPUT_D3D9_H_

//============================================================================//

#include "gala/output.h"

//===----------------------------------------------------------------------===//

#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  #define _WIN32_LEAN_AND_MEAN
  #include <windows.h>
  #include <d3d9.h>
#endif

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_output_d3d9 {
  gala_output_t __output__;
  ///
  HMONITOR monitor;
} gala_output_d3d9_t;

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_output_mode_d3d9 {
  gala_output_mode_t __output_mode__;
  ///
  UINT mode;
} gala_output_mode_d3d9_t;

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//===----------------------------------------------------------------------===//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace gala {
namespace d3d9 {

//===----------------------------------------------------------------------===//

/// \copydoc ::gala_output_d3d9_t
class Output
{
 public:
  /// \copydoc ::gala_output_mode_d3d9_t
  class Mode
  {
   private:
    Mode();
    Mode(const Mode &output_mode);
    Mode &operator=(const Mode &output_mode);
    ~Mode();

   public:
    operator ::gala::Output::Mode *() { return (::gala::Output::Mode *)this; }
    operator const ::gala::Output::Mode *() const { return (const ::gala::Output::Mode *)this; }

   public:
    /// \copydoc ::gala_output_mode_d3d9_t::mode
    const UINT mode() const { return __output_mode_d3d9__.mode; }

   private:
    ::gala_output_mode_d3d9_t __output_mode_d3d9__;
  };

 private:
  Output();
  Output(const Output &output);
  Output &operator=(const Output &output);
  ~Output();

 public:
  operator ::gala::Output *() { return (::gala::Output *)this; }
  operator const ::gala::Output *() const { return (const ::gala::Output *)this; }

 public:
  /// \copydoc ::gala_output_d3d9_t::monitor
  const HMONITOR monitor() const { return __output_d3d9__.monitor; }

 private:
  ::gala_output_d3d9_t __output_d3d9__;
};

//===----------------------------------------------------------------------===//

} // d3d9
} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_OUTPUT_D3D9_H_

//============================================================================//
