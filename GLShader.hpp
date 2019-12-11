#pragma once

#include <string>

#include "Type/Vertex.hpp"

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

            void Render();

            unsigned int AddVertex(const Vertex3 &vertex);
            void AddIndex(unsigned int index);

        private:
            unsigned int _programID;
            unsigned int _vaoID, _vboID, _iboID;

            Vertex3 *_vertices;
            unsigned int *_indices;

            unsigned int _numVertices, _numIndices;
    };
}
