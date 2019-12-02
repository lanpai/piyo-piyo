#include "Engine.hpp"

#include "Component/Window.hpp"

namespace piyo {
    Engine::~Engine() {
        for (std::pair<unsigned int, Component *> pair : this->_components)
            pair.second->OnDestroy();
    }

    void Engine::Run() {
        this->_shouldRun = true;
        while (this->_shouldRun && this->_windowCount != 0) {
            // Pre Update
            for (std::pair<unsigned int, Component *> pair : this->_components)
                pair.second->OnPreUpdate();

            // Update current scene here

            // Post Update
            for (std::pair<unsigned int, Component *> pair : this->_components)
                pair.second->OnPostUpdate();

            // Pre Draw
            for (std::pair<unsigned int, Component *> pair : this->_components)
                pair.second->OnPreDraw();

            // Draw current scene here

            // Post Draw
            for (std::pair<unsigned int, Component *> pair : this->_components)
                pair.second->OnPostDraw();
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
