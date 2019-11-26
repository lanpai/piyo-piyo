#include "Engine.hpp"
#include "Component/Window.hpp"

int main(int argc, char* argv[]) {
    Engine engine;

    Window window("Test Window", 1280, 720);
    engine.AddComponent(&window);

    engine.Run();

    return 0;
}
