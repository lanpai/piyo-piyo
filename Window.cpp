#include "Component/Window.hpp"

#if defined(__WAYLAND)
#elif defined(__linux__)
#elif defined(_WIN32)
#elif defined(__APPLE__)
#else
    #error "Could not detect OS during compile-time!"
#endif

#include <cstdio>

namespace piyo {
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

        // Fetching X display
        this->_xDisplay = XOpenDisplay(0);
        if (this->_xDisplay == NULL) {
            std::printf("Could not connect to X server\n");
            exit(0);
        }

        // Fetching the root window
        ::Window root = DefaultRootWindow(this->_xDisplay);

        XVisualInfo *visualInfo;
        GLint attr[] = { GLX_RGBA, GLX_DOUBLEBUFFER, None };
        visualInfo = glXChooseVisual(this->_xDisplay, 0, attr);
        if (visualInfo == NULL) {
            std::printf("No appropriate visual found\n");
            exit(0);
        }

        // Setting window attributes
        XSetWindowAttributes setWinAttr;
        setWinAttr.colormap = XCreateColormap(this->_xDisplay, root, visualInfo->visual, AllocNone);
        setWinAttr.event_mask = ExposureMask | KeyPressMask;

        // Creating the window
        this->_xWindow = XCreateWindow(
                this->_xDisplay,
                root,
                0, 0,
                this->_width, this->_height,
                0,
                visualInfo->depth,
                InputOutput,
                visualInfo->visual,
                CWColormap | CWEventMask,
                &setWinAttr
                );

        // Setting title
        XStoreName(this->_xDisplay, this->_xWindow, this->_windowName.c_str());

        // Creating OpenGL context
        this->_xContext = glXCreateContext(this->_xDisplay, visualInfo, NULL, GL_TRUE);
        if (this->_xContext == NULL) {
            std::printf("Failed to create rendering context\n");
            exit(0);
        }

        // Mapping the window and enabling the context
        XMapWindow(this->_xDisplay, this->_xWindow);
        this->MakeContextCurrent();
#elif defined(_WIN32)
        this->_display = DisplayType::WIN;
#elif defined(__APPLE__)
        this->_display = DisplayType::DARWIN;
#endif
    }

    void Window::Clear(float r, float g, float b, float a) {
#if defined(__WAYLAND)
#elif defined(__linux__)
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#elif defined(_WIN32)
#elif defined(__APPLE__)
#endif
    }

    void Window::SwapBuffers() {
#if defined(__WAYLAND)
#elif defined(__linux__)
        glXSwapBuffers(this->_xDisplay, this->_xWindow);
#elif defined(_WIN32)
#elif defined(__APPLE__)
#endif
    }

    void Window::MakeContextCurrent() {
#if defined(__WAYLAND)
#elif defined(__linux__)
        glXMakeCurrent(this->_xDisplay, this->_xWindow, this->_xContext);
#elif defined(_WIN32)
#elif defined(__APPLE__)
#endif
    }
}
