#include "Engine.hpp"
#include "Component/Window.hpp"

int main(int argc, char* argv[]) {
    piyo::Engine engine;

    piyo::Window window("Test Window", 1280, 720);
    engine.AddComponent(&window);
    piyo::Window windowb("Test Window B", 720, 1280);
    engine.AddComponent(&windowb);

    engine.Run();

    return 0;
}
