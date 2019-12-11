#pragma once

#include "../Type/Vertex.hpp"

namespace piyo {
    class GLShader;

    class Mesh {
        friend GLShader;

        public:
            Mesh();
            ~Mesh();

            unsigned int AddVertex(const Vertex3 &vertex);
            void AddIndex(unsigned int index);

        private:
            unsigned int _vaoID, _vboID, _iboID;
            unsigned int _numVertices, _numIndices;

            Vertex3 *_vertices;
            unsigned int *_indices;
    };
}
