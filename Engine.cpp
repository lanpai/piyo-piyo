#include "Engine.hpp"

#include <chrono>
#include <thread>

using namespace std::chrono_literals;

Engine::~Engine() {
    for (Component *component : this->_components)
        delete component;
}

void Engine::Run() {
    this->_shouldRun = true;
    while (this->_shouldRun) {
        std::this_thread::sleep_for(5s);
    }
}

void Engine::AddComponent(Component *component) {
    component->SetParent(this);
    component->OnInit();
    this->_components.push_back(component);
}
