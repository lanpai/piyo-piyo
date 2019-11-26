#include "Component/Window.hpp"

#if defined(__WAYLAND)
#elif defined(__linux__)
#include <xcb/xproto.h>
#elif defined(_WIN32)
#elif defined(__APPLE__)
#else
    #error "Could not detect OS during compile-time!"
#endif

#include <cstdio>

Window::Window(std::string windowName, int width, int height)
    : Component("Window", ComponentType::WINDOW)
    , _windowName(windowName)
    , _width(width)
    , _height(height) {
    // void
}

Window::~Window() {
#if defined(__WAYLAND)
#elif defined(__linux__)
    xcb_disconnect(this->xcbConnection);
#elif defined(_WIN32)
#elif defined(__APPLE__)
#endif
}

void Window::OnInit() {
    std::printf("Initializing %s...\n", this->_name.c_str());

#if defined(__WAYLAND)
    this->_display = DisplayType::WAYLAND;
#elif defined(__linux__)
    this->_display = DisplayType::X11;

    // Connecting to X server
    this->xcbConnection = xcb_connect(NULL, NULL);

    // Fetching the first screen
    this->xcbScreen = xcb_setup_roots_iterator(xcb_get_setup(this->xcbConnection)).data;

    // Creating the window
    this->xcbWindow = xcb_generate_id(this->xcbConnection);
    xcb_create_window(
            this->xcbConnection,
            XCB_COPY_FROM_PARENT,
            this->xcbWindow,
            this->xcbScreen->root,
            0, 0,
            this->_width, this->_height,
            10,
            XCB_WINDOW_CLASS_INPUT_OUTPUT,
            this->xcbScreen->root_visual,
            0, NULL);

    // Mapping the window to the screen
    xcb_map_window(this->xcbConnection, this->xcbWindow);

    // Set title
    xcb_change_property(
            this->xcbConnection,
            XCB_PROP_MODE_REPLACE,
            this->xcbWindow,
            XCB_ATOM_WM_NAME,
            XCB_ATOM_STRING,
            8,
            this->_windowName.length(),
            this->_windowName.c_str());

    // Flush X server
    xcb_flush(this->xcbConnection);
#elif defined(_WIN32)
    this->_display = DisplayType::WIN;
#elif defined(__APPLE__)
    this->_display = DisplayType::DARWIN;
#endif
}
