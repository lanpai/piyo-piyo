#include "Engine.hpp"
#include "Component/Window.hpp"
#include "Scene.hpp"
#include "GLShader.hpp"

class TestScene : public piyo::Scene {
    public:
        virtual void OnInit() override {
            piyo::GLProgramSource source;
            source.VertexSource = R"(
                #version 330 core

                layout(location = 0) in vec3 vertPosition;
                layout(location = 1) in vec4 vertColor;

                out vec3 fragPosition;
                out vec4 fragColor;

                uniform mat4 view;

                void main() {
                    gl_Position = view * vec4(vertPosition, 1.0f);
                    
                    fragPosition = vertPosition;
                    fragColor = vertColor;
                }
            )";
            source.FragmentSource = R"(
                #version 330 core

                in vec3 fragPosition;
                in vec4 fragColor;

                out vec4 color;

                void main() {
                    color = fragColor;
                }
            )";
            this->_shader = new piyo::GLShader(source);
        }
        virtual void OnDestroy() override {
            delete this->_shader;
        }
        virtual void OnUpdate() override {
        }
        virtual void OnDraw() override {
        }

    private:
        piyo::GLShader *_shader;
};

int main(int argc, char* argv[]) {
    piyo::Engine engine;

    piyo::Input input;
    engine.AddComponent(&input);

    piyo::Window window("Test Window", 100, 100);
    window.SetInput(&input);
    engine.AddComponent(&window);

    TestScene scene;
    engine.SwitchScene(&scene);

    engine.Run();

    return 0;
}
