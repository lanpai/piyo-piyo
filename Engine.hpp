#pragma once

#include "Component.hpp"

#include <vector>

namespace piyo {
    class Engine {
        public:
            ~Engine();

            void Run();

            void AddComponent(Component *component);

        private:
            bool _shouldRun;

            std::vector<Component *> _components;

            int _windowCount = 0;
    };
}
