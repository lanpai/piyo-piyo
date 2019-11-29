#pragma once

#if defined(__WAYLAND)
#elif defined(__linux__)
#include <X11/Xlib.h>
#include <GL/glew.h>
#include <GL/glx.h>
#elif defined(_WIN32)
#elif defined(__APPLE__)
#else
    #error "Could not detect OS during compile-time!"
#endif


#include "../Component.hpp"

namespace piyo {
    enum class DisplayType {
        X11,
        WAYLAND,
        WIN,
        DARWIN
    };

    class Window : public Component {
        public:
            Window(std::string windowName, int width, int height);

            virtual void OnInit() override;
            virtual void OnDestroy() override;
            virtual void OnPreUpdate() override;

            void Clear(float r, float g, float b, float a);
            void SwapBuffers();
            void MakeContextCurrent();

        private:
            std::string _windowName;
            int _width, _height;

            DisplayType _display;

#if defined(__WAYLAND)
#elif defined(__linux__)
            Display *_xDisplay;
            ::Window _xWindow;
            GLXContext _xContext;
#elif defined(_WIN32)
#elif defined(__APPLE__)
#endif
    };
}
