//===-- test/surface.cc ----------------------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//
//
// TODO(mtwilliams): Document the purpose of this file.
//
//===----------------------------------------------------------------------===//

#include "surface.h"

#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  #include <Windows.h>
#elif GALA_PLATFORM == GALA_PLATFORM_MAC_OS_X
#elif GALA_PLATFORM == GALA_PLATFORM_LINUX
#elif GALA_PLATFORM == GALA_PLATFORM_IOS
#elif GALA_PLATFORM == GALA_PLATFORM_ANDROID
#endif

namespace gala {
namespace test {

#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  static LRESULT WINAPI _WindowProcW(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#elif GALA_PLATFORM == GALA_PLATFORM_MAC_OS_X
#elif GALA_PLATFORM == GALA_PLATFORM_LINUX
#elif GALA_PLATFORM == GALA_PLATFORM_IOS
#elif GALA_PLATFORM == GALA_PLATFORM_ANDROID
#endif

Surface::Surface() {
  this->native_hndl_ = NULL;
}

Surface::~Surface() {
}

Surface *Surface::create(const Surface::Description &desc) {
  gala_assert_development(desc.title != NULL);
  gala_assert_development(desc.dimensions.width > 0);
  gala_assert_development(desc.dimensions.width <= 65535);
  gala_assert_development(desc.dimensions.height > 0);
  gala_assert_development(desc.dimensions.height <= 65535);
#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  Surface *surface = new Surface();

  WNDCLASSEXW wcx;
  memset(&wcx, 0, sizeof(wcx));
  wcx.cbSize        = sizeof(WNDCLASSEX);
  // TODO(mtwilliams): Investigate if CS_OWNDC needs to be specified.
  wcx.style         = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
  wcx.lpfnWndProc   = &_WindowProcW;
  wcx.hInstance     = ::GetModuleHandle(NULL);
  wcx.hCursor       = ::LoadCursor(NULL, IDC_ARROW);
  wcx.hIcon         = ::LoadIconW(wcx.hInstance, MAKEINTRESOURCEW(IDI_APPLICATION));
  wcx.hIconSm       = ::LoadIconW(wcx.hInstance, MAKEINTRESOURCEW(IDI_APPLICATION));
  wcx.lpszClassName = L"31ed42b8-325e-4877-8b7d-ea9ffa929470";

  // NOTE(mtwilliams): This is not thread-safe. Not that any of this stuff is.
  static const bool registered_class_succesfully = (::RegisterClassExW(&wcx) != 0);
  gala_assert(registered_class_succesfully);

  const DWORD styles = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
  const DWORD ex_styles = WS_EX_APPWINDOW | WS_EX_OVERLAPPEDWINDOW;

  WCHAR title_w[256];
  ::MultiByteToWideChar(CP_UTF8, 0, desc.title, -1, title_w, 256);

  // TODO(mtwilliams): Refactor?
  RECT client_area = { 0, 0, desc.dimensions.width, desc.dimensions.height };
  ::AdjustWindowRectEx(&client_area, styles, FALSE, ex_styles);
  const DWORD adjusted_width = client_area.right - client_area.left;
  const DWORD adjusted_height = client_area.bottom - client_area.top;

  HWND hndl = ::CreateWindowExW(ex_styles, wcx.lpszClassName, title_w, styles, 0, 0,
                                adjusted_width, adjusted_height, NULL, NULL,
                                ::GetModuleHandle(NULL), NULL);

  const bool created_windowed_succesfully = (hndl != NULL);
  gala_assert(created_windowed_succesfully);

  // TODO(mtwilliams): Use the (global) atom table?
  const bool inserted_ref_to_inst_successfully = !!(::SetPropA(hndl, "surface", (HANDLE)surface));
  gala_assert(inserted_ref_to_inst_successfully);

  // HACK(mtwilliams): Center the window on the encompassing monitor.
  HMONITOR encompassing_monitor = ::MonitorFromWindow(hndl, MONITOR_DEFAULTTONULL);
  MONITORINFO encompassing_monitor_info;
  ::memset((void *)&encompassing_monitor_info, 0, sizeof(MONITORINFO));
  encompassing_monitor_info.cbSize = sizeof(MONITORINFO);
  ::GetMonitorInfo(encompassing_monitor, &encompassing_monitor_info);
  RECT encompassing_area;
  ::GetWindowRect(hndl, &encompassing_area);
  const DWORD monitor_width = encompassing_monitor_info.rcMonitor.right - encompassing_monitor_info.rcMonitor.left;
  const DWORD monitor_height = encompassing_monitor_info.rcMonitor.bottom - encompassing_monitor_info.rcMonitor.top;
  const DWORD encompassing_width = encompassing_area.right - encompassing_area.left - 1;
  const DWORD encompassing_height = encompassing_area.bottom - encompassing_area.top - 1;
  const DWORD centered_pos_x = (monitor_width - encompassing_width) / 2 + encompassing_monitor_info.rcMonitor.left;
  const DWORD centered_pos_y = (monitor_height - encompassing_height) / 2 + encompassing_monitor_info.rcMonitor.top;
  ::SetWindowPos(hndl, HWND_TOP, centered_pos_x, centered_pos_y, 0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE);

  // Make it visible.
  ::ShowWindow(hndl, SW_SHOW);

  surface->native_hndl_ = (uintptr_t)hndl;

  return surface;
#elif GALA_PLATFORM == GALA_PLATFORM_MAC_OS_X
#elif GALA_PLATFORM == GALA_PLATFORM_LINUX
#elif GALA_PLATFORM == GALA_PLATFORM_IOS
#elif GALA_PLATFORM == GALA_PLATFORM_ANDROID
#endif
}

void Surface::destroy() {
#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  ::DestroyWindow((HWND)native_hndl_);
#elif GALA_PLATFORM == GALA_PLATFORM_MAC_OS_X
#elif GALA_PLATFORM == GALA_PLATFORM_LINUX
#elif GALA_PLATFORM == GALA_PLATFORM_IOS
#elif GALA_PLATFORM == GALA_PLATFORM_ANDROID
#endif
}

void Surface::update(EventHandler event_handler,
                     void *event_handler_ctx) {
  gala_assert_debug(event_handler != NULL);
#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  ::SetPropA((HWND)native_hndl_, "event_handler", (HANDLE)event_handler);
  ::SetPropA((HWND)native_hndl_, "event_handler_ctx", (HANDLE)event_handler_ctx);

  MSG msg;
  while (::PeekMessage(&msg, (HWND)native_hndl_, 0, 0, PM_REMOVE)) {
    // TODO(mtwilliams): Translate and pass messages to |event_handler|.
    ::TranslateMessage(&msg);
    ::DispatchMessage(&msg);
  }
#elif GALA_PLATFORM == GALA_PLATFORM_MAC_OS_X
#elif GALA_PLATFORM == GALA_PLATFORM_LINUX
#elif GALA_PLATFORM == GALA_PLATFORM_IOS
#elif GALA_PLATFORM == GALA_PLATFORM_ANDROID
#endif
}

void Surface::dimensions(gala_uint32_t *width, gala_uint32_t *height) const {
  gala_assert_debug(width != NULL);
  gala_assert_debug(height != NULL);
#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  RECT client_area;
  ::GetClientRect((HWND)native_hndl_, &client_area);
  *width = client_area.right - client_area.left;
  *height = client_area.bottom - client_area.top;
#elif GALA_PLATFORM == GALA_PLATFORM_MAC_OS_X
#elif GALA_PLATFORM == GALA_PLATFORM_LINUX
#elif GALA_PLATFORM == GALA_PLATFORM_IOS
#elif GALA_PLATFORM == GALA_PLATFORM_ANDROID
#endif
}

void Surface::resize(gala_uint32_t new_width, gala_uint32_t new_height) {
  gala_assert_development(new_width > 0);
  gala_assert_development(new_width <= 65535);
  gala_assert_development(new_height > 0);
  gala_assert_development(new_height <= 65535);
#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  const DWORD styles = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
  const DWORD ex_styles = WS_EX_APPWINDOW | WS_EX_OVERLAPPEDWINDOW;

  RECT new_client_area = { 0, 0, new_width, new_height };
  ::AdjustWindowRectEx(&new_client_area, styles, FALSE, ex_styles);
  const DWORD adjusted_width = new_client_area.right - new_client_area.left;
  const DWORD adjusted_height = new_client_area.bottom - new_client_area.top;

  ::SetWindowPos((HWND)native_hndl_, NULL, 0, 0, adjusted_width, adjusted_height,
                 SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
#elif GALA_PLATFORM == GALA_PLATFORM_MAC_OS_X
#elif GALA_PLATFORM == GALA_PLATFORM_LINUX
#elif GALA_PLATFORM == GALA_PLATFORM_IOS
#elif GALA_PLATFORM == GALA_PLATFORM_ANDROID
#endif
}

uintptr_t Surface::to_native_hndl() const {
  return this->native_hndl_;
}

#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
static LRESULT WINAPI _WindowProcW(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  Surface *surface = (Surface *)::GetPropA(hWnd, "surface");

  Surface::EventHandler event_handler = (Surface::EventHandler)::GetPropA(hWnd, "event_handler");
  void *event_handler_ctx = (void *)::GetPropA(hWnd, "event_handler_ctx");

  switch (uMsg) {
    case WM_CLOSE: {
      Surface::Event event;
      event.type = Surface::Event::CLOSED;
      event_handler(surface, &event, event_handler_ctx);
    } return TRUE;

    case WM_NCDESTROY: {
      // According to MSDN, all entries in the property list of a window must
      // be removed (via RemoveProp) before it is destroyed. In practice, this
      // doesn't make any material difference--perhaps a (small) memory leak?
      ::RemovePropA(hWnd, "surface");

      // And of course, we free any memory we've associated with |hWnd|.
      free((void *)surface);
    } return TRUE;
  }

  return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}
#endif

} // test
} // gala
