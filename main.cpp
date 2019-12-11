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
                    gl_Position = vec4(vertPosition, 1.0f);
                    
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

            piyo::Vertex3 a = piyo::Vertex3();
            piyo::Vertex3 b = piyo::Vertex3();
            piyo::Vertex3 c = piyo::Vertex3();

            a.position = piyo::Vector3(0.0f, 0.0f, 0.0f);
            a.color = piyo::Color(255, 0, 0, 0);
            b.position = piyo::Vector3(1.0f, 1.0f, 0.0f);
            b.color = piyo::Color(0, 255, 0, 0);
            c.position = piyo::Vector3(1.0f, 0.0f, 0.0f);
            c.color = piyo::Color(0, 0, 255, 0);

            this->_mesh.AddIndex(this->_mesh.AddVertex(a));
            this->_mesh.AddIndex(this->_mesh.AddVertex(c));
            this->_mesh.AddIndex(this->_mesh.AddVertex(b));
        }
        virtual void OnDestroy() override {
            delete this->_shader;
        }
        virtual void OnUpdate() override {
        }
        virtual void OnDraw() override {
            this->_shader->Render(this->_mesh);
        }

    private:
        piyo::GLShader *_shader;
        piyo::Mesh _mesh;
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
