#pragma once

#include <map>

#include "Component.hpp"
#include "Scene.hpp"

namespace piyo {
    class Engine {
        public:
            ~Engine();

            void Run();
            void Stop() { this->_shouldRun = false; }

            void AddComponent(Component *component);
            void RemoveComponent(unsigned int id);
            void SwitchScene(Scene *scene);

        private:
            bool _shouldRun;

            std::map<unsigned int, Component *> _components;
            Scene *_currentScene = nullptr;
    };
}
