#pragma once

#if defined(__WAYLAND)
#elif defined(__linux__)
#include <X11/Xlib.h>
#elif defined(_WIN32)
#elif defined(__APPLE__)
#else
    #error "Could not detect OS during compile-time!"
#endif

#include <cstdio>
#include <string>
#include <map>

#include "../Component.hpp"

namespace piyo {
    enum class KeyState {
        UP,
        PRESSED,
        DOWN,
        RELEASED
    };

    enum class KeyCode {
        UNDEFINED,
        Escape, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
        Grave, Key1, Key2, Key3, Key4, Key5, Key6, Key7, Key8, Key9, Key0, Hyphen, Equals, Backspace,
        Tab, Q, W, E, R, T, Y, U, I, O, P, LeftBracket, RightBracket, Backslash,
        CapsLock, A, S, D, F, G, H, J, K, L, Semicolon, Apostrophe, Enter,
        LeftShift, Z, X, C, V, B, N, M, Comma, Period, ForwardSlash, RightShift,
        LeftCtrl, LeftSuper, LeftAlt, Space, RightAlt, RightSuper, Menu, RightCtrl,
        Print, ScrollLock, Break,
        Insert, Home, PageUp,
        Delete, End, PageDown,
        Up, Left, Down, Right,
        NumLock, NumDivide, NumMultiply, NumSubtract, NumAdd, NumEnter, NumDelete,
        Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
        Function
    };

#if defined(__WAYLAND)
#elif defined(__linux__)
    KeyCode TranslateKeyCode(unsigned int code);
#elif defined(_WIN32)
#elif defined(__APPLE__)
#endif

    class Input : public Component {
        public:
            Input();

            virtual void OnPostUpdate() override;

            void SetKeyState(KeyCode key, KeyState state) { this->_keyStates[key] = state; };
            KeyState GetKeyState(KeyCode key) { return this->_keyStates[key]; };

        private:
            std::map<KeyCode, KeyState> _keyStates;
    };
}
