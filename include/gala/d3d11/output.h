//===-- gala/d3d11/output.h -------------------------------------*- C++ -*-===//
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

#ifndef _GALA_D3D11_OUTPUT_H_
#define _GALA_D3D11_OUTPUT_H_

//============================================================================//

#include "gala/config.h"
#include "gala/linkage.h"
#include "gala/foundation.h"

//===----------------------------------------------------------------------===//

#include "gala/output.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef struct gala_d3d11_output gala_d3d11_output_t;

//===----------------------------------------------------------------------===//

/// \brief
/// \param output
/// \returns
///
extern GALA_PUBLIC void
gala_d3d11_output_destroy(
  gala_d3d11_output_t *output);

//===----------------------------------------------------------------------===//

/// \brief
/// \param output
/// \returns
///
extern GALA_PUBLIC size_t
gala_d3d11_output_num_display_modes(
  const gala_d3d11_output_t *output);

//===----------------------------------------------------------------------===//

/// \brief
/// \param output
/// \param display_mode
/// \returns
///
extern GALA_PUBLIC void
gala_d3d11_output_display_mode(
  const gala_d3d11_output_t *output,
  const size_t idx,
  gala_display_mode_t *display_mode);

//===----------------------------------------------------------------------===//

/// \brief
/// \param output
/// \param buf
/// \param buf_sz
/// \returns
///
extern GALA_PUBLIC int
gala_d3d11_output_to_s(
  const gala_d3d11_output_t *output,
  char buf[],
  const int buf_sz);

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace gala {

//===----------------------------------------------------------------------===//

/// \copydoc ::gala_d3d11_output_t
class GALA_PUBLIC D3D11Output : public ::gala::Output {
 public:
  /// \copydoc ::gala_d3d11_output_destroy
  void destroy();

 public:
  /// \copydoc ::gala_d3d11_output_num_display_modes
  size_t num_display_modes() const;

  /// \copyodc ::gala_d3d11_output_display_mode
  void display_mode(const size_t idx, ::gala::DisplayMode *display_mode) const;

 public:
  /// \copydoc ::gala_d3d11_output_to_s
  int to_s(char buf[], const int buf_sz) const;
};

//===----------------------------------------------------------------------===//

} // gala

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _GALA_D3D11_OUTPUT_H_

//============================================================================//
