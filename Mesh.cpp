#include "Object/Mesh.hpp"

#include <GL/glew.h>
#include <cstdio>

namespace piyo {
    Mesh::Mesh() {
        // Generating VAO, VBO, and IBO
        if (this->_vaoID == 0)
            glGenVertexArrays(1, &this->_vaoID);
        if (this->_vboID == 0)
            glGenBuffers(1, &this->_vboID);
        if (this->_iboID == 0)
            glGenBuffers(1, &this->_iboID);

        // Binding the VAO and VBO, and IBO
        glBindVertexArray(this->_vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, this->_vboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_iboID);

        // Initializing arrays
        this->_vertices = new Vertex3[0];
        this->_indices = new unsigned int[0];
        this->_numVertices = 0;
        this->_numIndices = 0;
    }

    Mesh::~Mesh() {
        // Deleting arrays
        delete[] this->_vertices;
        delete[] this->_indices;

        // Deleting VAO, VBO, and IBO
        if (this->_vaoID)
            glDeleteVertexArrays(1, &this->_vaoID);
        if (this->_vboID)
            glDeleteBuffers(1, &this->_vboID);
        if (this->_iboID)
            glDeleteBuffers(1, &this->_iboID);
    }

    unsigned int Mesh::AddVertex(const Vertex3 &vertex) {
        this->_numVertices++;

        Vertex3 *newVertexArray = new Vertex3[this->_numVertices];
        for (int i = 0; i < (int)(this->_numVertices - 1); i++)
            newVertexArray[i] = this->_vertices[i];
        newVertexArray[this->_numVertices - 1] = vertex;

        delete[] this->_vertices;
        this->_vertices = newVertexArray;

        return this->_numVertices - 1;
    }

    void Mesh::AddIndex(unsigned int index) {
        this->_numIndices++;

        unsigned int *newIndexArray = new unsigned int[this->_numIndices];
        for (int i = 0; i < (int)(this->_numIndices - 1); i++)
            newIndexArray[i] = this->_indices[i];
        newIndexArray[this->_numIndices - 1] = index;

        delete[] this->_indices;
        this->_indices = newIndexArray;
    }
}
