#include "Engine.hpp"

#include "Component/Window.hpp"

namespace piyo {
    Engine::~Engine() {
        for (const std::pair<unsigned int, Component *> &pair : this->_components)
            pair.second->OnDestroy();
    }

    void Engine::Run() {
        this->_shouldRun = true;
        while (this->_shouldRun) {
            // Pre Update
            for (std::pair<unsigned int, Component *> pair : this->_components)
                pair.second->OnPreUpdate();

            if (this->_currentScene != nullptr)
                this->_currentScene->OnUpdate();

            // Post Update
            for (std::pair<unsigned int, Component *> pair : this->_components)
                pair.second->OnPostUpdate();

            // Pre Draw
            for (std::pair<unsigned int, Component *> pair : this->_components)
                pair.second->OnPreDraw();

            if (this->_currentScene != nullptr)
                this->_currentScene->OnDraw();

            // Post Draw
            for (std::pair<unsigned int, Component *> pair : this->_components)
                pair.second->OnPostDraw();
        }
    }

    void Engine::AddComponent(Component *component) {
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
        this->_components.erase(id);
    }

    void Engine::SwitchScene(Scene *scene) {
        if (this->_currentScene != nullptr)
            this->_currentScene->OnDestroy();
        this->_currentScene = scene;
        scene->_parent = this;
        scene->OnInit();
    }
}
