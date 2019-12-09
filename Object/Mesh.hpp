#pragma once

#include "../Type/Vertex.hpp"

namespace piyo {
    struct Mesh {
        Mesh()
            : vertices(new Vertex3[0]), indices(new unsigned int[0]) {}
        ~Mesh() {
            delete[] this->vertices;
            delete[] this->indices;
        }

        Vertex3 *vertices;
        unsigned int *indices;
    };
}
