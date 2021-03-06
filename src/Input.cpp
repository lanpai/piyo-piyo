#include "Component/Input.hpp"

namespace piyo {
#if defined(__WAYLAND)
#elif defined(__linux__)
    KeyCode TranslateKeyCode(unsigned int code) {
        switch (code) {
            case 9:     return KeyCode::Escape;
            case 67:    return KeyCode::F1;
            case 68:    return KeyCode::F2;
            case 69:    return KeyCode::F3;
            case 70:    return KeyCode::F4;
            case 71:    return KeyCode::F5;
            case 72:    return KeyCode::F6;
            case 73:    return KeyCode::F7;
            case 74:    return KeyCode::F8;
            case 75:    return KeyCode::F9;
            case 76:    return KeyCode::F10;
            case 95:    return KeyCode::F11;
            case 96:    return KeyCode::F12;
            case 49:    return KeyCode::Grave;
            case 10:    return KeyCode::Key1;
            case 11:    return KeyCode::Key2;
            case 12:    return KeyCode::Key3;
            case 13:    return KeyCode::Key4;
            case 14:    return KeyCode::Key5;
            case 15:    return KeyCode::Key6;
            case 16:    return KeyCode::Key7;
            case 17:    return KeyCode::Key8;
            case 18:    return KeyCode::Key9;
            case 19:    return KeyCode::Key0;
            case 20:    return KeyCode::Hyphen;
            case 21:    return KeyCode::Equals;
            case 22:    return KeyCode::Backspace;
            case 23:    return KeyCode::Tab;
            case 24:    return KeyCode::Q;
            case 25:    return KeyCode::W;
            case 26:    return KeyCode::E;
            case 27:    return KeyCode::R;
            case 28:    return KeyCode::T;
            case 29:    return KeyCode::Y;
            case 30:    return KeyCode::U;
            case 31:    return KeyCode::I;
            case 32:    return KeyCode::O;
            case 33:    return KeyCode::P;
            case 34:    return KeyCode::LeftBracket;
            case 35:    return KeyCode::RightBracket;
            case 51:    return KeyCode::Backslash;
            case 66:    return KeyCode::CapsLock;
            case 38:    return KeyCode::A;
            case 39:    return KeyCode::S;
            case 40:    return KeyCode::D;
            case 41:    return KeyCode::F;
            case 42:    return KeyCode::G;
            case 43:    return KeyCode::H;
            case 44:    return KeyCode::J;
            case 45:    return KeyCode::K;
            case 46:    return KeyCode::L;
            case 47:    return KeyCode::Semicolon;
            case 48:    return KeyCode::Apostrophe;
            case 36:    return KeyCode::Enter;
            case 50:    return KeyCode::LeftShift;
            case 52:    return KeyCode::Z;
            case 53:    return KeyCode::X;
            case 54:    return KeyCode::C;
            case 55:    return KeyCode::V;
            case 56:    return KeyCode::B;
            case 57:    return KeyCode::N;
            case 58:    return KeyCode::M;
            case 59:    return KeyCode::Comma;
            case 60:    return KeyCode::Period;
            case 61:    return KeyCode::ForwardSlash;
            case 62:    return KeyCode::RightShift;
            case 37:    return KeyCode::LeftCtrl;
            case 133:   return KeyCode::LeftSuper;
            case 64:    return KeyCode::LeftAlt;
            case 65:    return KeyCode::Space;
            case 108:   return KeyCode::RightAlt;
            case 134:   return KeyCode::RightSuper;
            case 135:   return KeyCode::Menu;
            case 105:   return KeyCode::RightCtrl;
            case 107:   return KeyCode::Print;
            case 78:    return KeyCode::ScrollLock;
            case 127:   return KeyCode::Break;
            case 118:   return KeyCode::Insert;
            case 110:   return KeyCode::Home;
            case 112:   return KeyCode::PageUp;
            case 119:   return KeyCode::Delete;
            case 115:   return KeyCode::End;
            case 117:   return KeyCode::PageDown;
            case 111:   return KeyCode::Up;
            case 113:   return KeyCode::Left;
            case 116:   return KeyCode::Down;
            case 114:   return KeyCode::Right;
            case 77:    return KeyCode::NumLock;
            case 106:   return KeyCode::NumDivide;
            case 63:    return KeyCode::NumMultiply;
            case 82:    return KeyCode::NumSubtract;
            case 86:    return KeyCode::NumAdd;
            case 104:   return KeyCode::NumEnter;
            case 91:    return KeyCode::NumDelete;
            case 90:    return KeyCode::Num0;
            case 87:    return KeyCode::Num1;
            case 88:    return KeyCode::Num2;
            case 89:    return KeyCode::Num3;
            case 83:    return KeyCode::Num4;
            case 84:    return KeyCode::Num5;
            case 85:    return KeyCode::Num6;
            case 79:    return KeyCode::Num7;
            case 80:    return KeyCode::Num8;
            case 81:    return KeyCode::Num9;
            case 151:   return KeyCode::Function;
            default:    return KeyCode::UNDEFINED;
        }
    }
#elif defined(_WIN32)
#elif defined(__APPLE__)
#endif

    Input::Input()
        : Component("Window", ComponentType::INPUT) {
        // void
    }

    void Input::OnPostUpdate() {
        // Setting PRESSED to DOWN and RELEASED to UP
        for (const std::pair<KeyCode, KeyState> &key : this->_keyStates) {
            if (key.second == KeyState::PRESSED)
                this->SetKeyState(key.first, KeyState::DOWN);
            else if (key.second == KeyState::RELEASED)
                this->SetKeyState(key.first, KeyState::UP);
        }
    }
}
