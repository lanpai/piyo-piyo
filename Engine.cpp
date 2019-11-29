#include "Engine.hpp"

#include <chrono>
#include <thread>
#include <cstdio>

#include <GL/glew.h>

#include "Component/Window.hpp"

using namespace std::chrono_literals;

namespace piyo {
    Engine::~Engine() {
        for (std::pair<unsigned int, Component *> pair : this->_components)
            pair.second->OnDestroy();
    }

    void Engine::Run() {
        this->_shouldRun = true;
        std::printf("window count: %d\n", this->_windowCount);
        while (this->_shouldRun && this->_windowCount != 0) {
            // Updating
            for (std::pair<unsigned int, Component *> pair : this->_components)
                pair.second->OnPreUpdate();

            // Update current scene here

            for (std::pair<unsigned int, Component *> pair : this->_components)
                pair.second->OnPostUpdate();

            // Drawing
            for (std::pair<unsigned int, Component *> pair : this->_components) {
                if (pair.second->GetType() == ComponentType::WINDOW) {
                    static_cast<Window *>(pair.second)->MakeContextCurrent();
                    static_cast<Window *>(pair.second)->Clear(0.0f, 1.0f, 0.0f, 1.0f);
                }
                pair.second->OnPreDraw();
            }

            // Draw current scene here

            for (std::pair<unsigned int, Component *> pair : this->_components) {
                pair.second->OnPostDraw();
                if (pair.second->GetType() == ComponentType::WINDOW)
                    static_cast<Window *>(pair.second)->MakeContextCurrent();
                    static_cast<Window *>(pair.second)->SwapBuffers();
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

        unsigned int newId;
        if (this->_components.size() == 0)
            newId = 0;
        else
            newId = this->_components.rbegin()->first + 1;

        component->SetParent(this, newId);
        component->OnInit();
        this->_components.insert(std::pair<unsigned int, Component *>(newId, component));
    }

    void Engine::RemoveComponent(unsigned int id) {
        if (this->_components.at(id)->GetType() == ComponentType::WINDOW)
            this->_windowCount--;

        this->_components.erase(id);
    }
}
