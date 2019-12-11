#pragma once

#include <string>

#include "Type/Vertex.hpp"
#include "Object/Mesh.hpp"

namespace piyo {
    struct GLProgramSource {
        std::string VertexSource = "";
        std::string FragmentSource = "";
    };

    class GLShader {
        public:
            GLShader(const GLProgramSource &source);
            ~GLShader();

            void Use();
            void Unuse();

            void Render(const Mesh &mesh);

        private:
            unsigned int _programID;
    };
}
