#include "Engine.hpp"
#include "Component/Window.hpp"

int main(int argc, char* argv[]) {
    piyo::Engine engine;

    piyo::Input input;
    engine.AddComponent(&input);

    piyo::Window window("Test Window", 100, 100);
    window.SetInput(&input);
    engine.AddComponent(&window);
    piyo::Window windowb("Test Window B", 720, 1280);
    windowb.SetInput(&input);
    engine.AddComponent(&windowb);

    engine.Run();

    return 0;
}
