#pragma once

#if defined(__WAYLAND)
#elif defined(__linux__)
#include <xcb/xcb.h>
#elif defined(_WIN32)
#elif defined(__APPLE__)
#else
    #error "Could not detect OS during compile-time!"
#endif


#include "../Component.hpp"

enum class DisplayType {
    X11,
    WAYLAND,
    WIN,
    DARWIN
};

class Window : public Component {
    public:
        Window(std::string windowName, int width, int height);
        ~Window();

        virtual void OnInit() override;

    private:
        std::string _windowName;
        int _width, _height;

        DisplayType _display;

#if defined(__WAYLAND)
#elif defined(__linux__)
        xcb_connection_t *xcbConnection;
        xcb_screen_t *xcbScreen;
        xcb_window_t xcbWindow;
#elif defined(_WIN32)
#elif defined(__APPLE__)
#endif
};
