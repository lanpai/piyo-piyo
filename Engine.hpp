#pragma once

#include "Component.hpp"

#include <vector>

class Engine {
    public:
        ~Engine();

        void Run();

        void AddComponent(Component *component);

    private:
        bool _shouldRun;

        std::vector<Component *> _components;
};
