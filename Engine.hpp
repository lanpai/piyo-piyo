#pragma once

#include "Component.hpp"

#include <map>

namespace piyo {
    class Engine {
        public:
            ~Engine();

            void Run();

            void AddComponent(Component *component);
            void RemoveComponent(unsigned int id);

        private:
            bool _shouldRun;

            std::map<unsigned int, Component *> _components;

            int _windowCount = 0;
    };
}
