#include "Engine.hpp"

#include <chrono>
#include <thread>
#include <cstdio>

#include <GL/glew.h>

#include "Component/Window.hpp"

using namespace std::chrono_literals;

namespace piyo {
    Engine::~Engine() {
        for (Component *component : this->_components)
            delete component;
    }

    void Engine::Run() {
        this->_shouldRun = true;
        std::printf("window count: %d\n", this->_windowCount);
        while (this->_shouldRun && this->_windowCount != 0) {
            // Updating
            for (Component *component : this->_components)
                component->OnPreUpdate();

            // Update current scene here

            for (Component *component : this->_components)
                component->OnPostUpdate();

            // Drawing
            for (Component *component : this->_components) {
                if (component->GetType() == ComponentType::WINDOW)
                    static_cast<Window *>(component)->Clear(0.0f, 0.0f, 0.0f, 1.0f);
                component->OnPreDraw();
            }

            // Draw current scene here

            for (Component *component : this->_components) {
                component->OnPostDraw();
                if (component->GetType() == ComponentType::WINDOW)
                    static_cast<Window *>(component)->SwapBuffers();
            }
        }
    }

    void Engine::AddComponent(Component *component) {
        switch (component->GetType()) {
            case ComponentType::WINDOW:
                this->_windowCount++;
                break;
            default:
                break;
        }

        component->SetParent(this);
        component->OnInit();
        this->_components.push_back(component);
    }
}
