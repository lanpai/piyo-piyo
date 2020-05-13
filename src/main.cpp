#include "Engine.hpp"
#include "Component/Window.hpp"
#include "Scene.hpp"
#include "GLShader.hpp"
#include "Type/Matrix.hpp"

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

            this->_projection = piyo::Mat4x4::Perspective(0.5 * 3.14f, 1280.0f/720.0f, 1.0f, 1000.0f);

            for (int i = 0; i < 4; i++)
                this->_view.data[i][i] = 1.0f;

            piyo::Vertex3 a = piyo::Vertex3();
            piyo::Vertex3 b = piyo::Vertex3();
            piyo::Vertex3 c = piyo::Vertex3();
            piyo::Vertex3 d = piyo::Vertex3();
            piyo::Vertex3 e = piyo::Vertex3();
            piyo::Vertex3 f = piyo::Vertex3();
            piyo::Vertex3 g = piyo::Vertex3();
            piyo::Vertex3 h = piyo::Vertex3();

            a.position = piyo::Vec3(-10.0f, -2.0f, -10.0f);
            b.position = piyo::Vec3(-10.0f, 2.0f, -10.0f);
            c.position = piyo::Vec3(10.0f, -2.0f, -10.0f);
            d.position = piyo::Vec3(10.0f, 2.0f, -10.0f);

            e.position = piyo::Vec3(-10.0f, -2.0f, -25.0f);
            f.position = piyo::Vec3(-10.0f, 2.0f, -25.0f);
            g.position = piyo::Vec3(10.0f, -2.0f, -25.0f);
            h.position = piyo::Vec3(10.0f, 2.0f, -25.0f);

            a.color = piyo::Color(255, 0, 0, 0);
            b.color = piyo::Color(255, 0, 0, 0);
            c.color = piyo::Color(255, 0, 0, 0);
            d.color = piyo::Color(255, 0, 0, 0);
            e.color = piyo::Color(255, 255, 0, 0);
            f.color = piyo::Color(255, 255, 0, 0);
            g.color = piyo::Color(255, 255, 0, 0);
            h.color = piyo::Color(255, 255, 0, 0);

            unsigned int aIndex = this->_mesh.AddVertex(a);
            unsigned int bIndex = this->_mesh.AddVertex(b);
            unsigned int cIndex = this->_mesh.AddVertex(c);
            unsigned int dIndex = this->_mesh.AddVertex(d);
            unsigned int eIndex = this->_mesh.AddVertex(e);
            unsigned int fIndex = this->_mesh.AddVertex(f);
            unsigned int gIndex = this->_mesh.AddVertex(g);
            unsigned int hIndex = this->_mesh.AddVertex(h);

            // Front
            this->_mesh.AddIndex(aIndex);
            this->_mesh.AddIndex(bIndex);
            this->_mesh.AddIndex(dIndex);
            this->_mesh.AddIndex(aIndex);
            this->_mesh.AddIndex(dIndex);
            this->_mesh.AddIndex(cIndex);

            // Top
            this->_mesh.AddIndex(bIndex);
            this->_mesh.AddIndex(fIndex);
            this->_mesh.AddIndex(hIndex);
            this->_mesh.AddIndex(bIndex);
            this->_mesh.AddIndex(hIndex);
            this->_mesh.AddIndex(dIndex);

            // Left
            this->_mesh.AddIndex(aIndex);
            this->_mesh.AddIndex(eIndex);
            this->_mesh.AddIndex(fIndex);
            this->_mesh.AddIndex(aIndex);
            this->_mesh.AddIndex(fIndex);
            this->_mesh.AddIndex(bIndex);

            // Right
            this->_mesh.AddIndex(cIndex);
            this->_mesh.AddIndex(hIndex);
            this->_mesh.AddIndex(gIndex);
            this->_mesh.AddIndex(cIndex);
            this->_mesh.AddIndex(dIndex);
            this->_mesh.AddIndex(hIndex);

            // Bottom
            this->_mesh.AddIndex(eIndex);
            this->_mesh.AddIndex(aIndex);
            this->_mesh.AddIndex(gIndex);
            this->_mesh.AddIndex(gIndex);
            this->_mesh.AddIndex(aIndex);
            this->_mesh.AddIndex(cIndex);

            // Back
            this->_mesh.AddIndex(eIndex);
            this->_mesh.AddIndex(fIndex);
            this->_mesh.AddIndex(hIndex);
            this->_mesh.AddIndex(eIndex);
            this->_mesh.AddIndex(hIndex);
            this->_mesh.AddIndex(gIndex);
        }
        virtual void OnDestroy() override {
            delete this->_shader;
        }
        virtual void OnUpdate() override {
        }
        virtual void OnDraw() override {
            piyo::Mat4x4 mvp = this->_projection * this->_view;
            this->_shader->UniformMatrix4fv("view", &mvp[0][0]);
            this->_shader->Render(this->_mesh);
        }

    private:
        piyo::GLShader *_shader;
        piyo::Mesh _mesh;

        piyo::Mat4x4 _projection;
        piyo::Mat4x4 _view;
};

int main() {
    piyo::Engine engine;

    piyo::Input input;
    engine.AddComponent(&input);

    piyo::Window window("Test Window", 1280, 720);
    window.SetInput(&input);
    engine.AddComponent(&window);

    TestScene scene;
    engine.SwitchScene(&scene);

    engine.Run();

    return 0;
}
