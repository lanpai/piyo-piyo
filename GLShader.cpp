#include "GLShader.hpp"

#include <GL/glew.h>

namespace piyo {
    unsigned int CompileShader(unsigned int type, const std::string &source) {
        // Compiling 
        unsigned int id = glCreateShader(type);
        const char *src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        // Compiling shader and error checking
        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (!result)
        {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            std::printf(
                "Failed to compile shader!\n%s",
                message
            );
            glDeleteShader(id);
            return 0;
        }

        return id;
    }

    GLShader::GLShader(const GLProgramSource &source) {
        // Initializing the OpenGL program
        this->_programID = glCreateProgram();

        // Compiling shaders
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, source.VertexSource);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, source.FragmentSource);

        // Linking programs
        glAttachShader(this->_programID, vs);
        glAttachShader(this->_programID, fs);
        glLinkProgram(this->_programID);
        glValidateProgram(this->_programID);

        // Garbage collection
        glDeleteShader(vs);
        glDeleteShader(fs);

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

        // Pointing the VAO to correct locations
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3), (void*)offsetof(Vertex3, position));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex3), (void*)offsetof(Vertex3, color));

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3), (void*)offsetof(Vertex3, uv));

        // Initializing arrays
        this->_vertices = new Vertex3[0];
        this->_indices = new unsigned int[0];
    }

    GLShader::~GLShader() {
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

        // Deleting the GL program
        glDeleteProgram(this->_programID);
    }

    void GLShader::Use() {
        glUseProgram(this->_programID);
    }

    void GLShader::Unuse() {
        glUseProgram(0);
    }

    void GLShader::Render() {
        this->Use();

        // Binding the VBO
        glBindBuffer(GL_ARRAY_BUFFER, this->_vboID);

        // Uploading vertex data
        glBufferData(GL_ARRAY_BUFFER, this->_numVertices * sizeof(Vertex3), nullptr, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, this->_numVertices * sizeof(Vertex3), this->_vertices);

        // Unbinding the VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Binding the IBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_iboID);

        // Uploading index data to the IBO
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_numIndices * sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, this->_numIndices * sizeof(unsigned int), this->_indices);

        // Unbinding the IBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Binding vertex array
        glBindVertexArray(this->_vaoID);

        // Drawing vertices
        glDrawElements(GL_TRIANGLES, this->_numIndices, GL_UNSIGNED_INT, 0);

        // Unbinding the VAO
        glBindVertexArray(0);

        this->Unuse();

        // Clear the vertex and index arrays
        delete[] this->_vertices;
        delete[] this->_indices;
        this->_vertices = new Vertex3[0];
        this->_indices = new unsigned int[0];
        this->_numVertices = 0;
        this->_numIndices = 0;
    }

    unsigned int GLShader::AddVertex(const Vertex3 &vertex) {
        this->_numVertices++;

        Vertex3 *newVertexArray = new Vertex3[this->_numVertices];
        for (int i = 0; i < (int)(this->_numVertices - 1); i++)
            newVertexArray[i] = this->_vertices[i];
        newVertexArray[this->_numVertices - 1] = vertex;

        delete[] this->_vertices;
        this->_vertices = newVertexArray;

        return this->_numVertices - 1;
    }

    void GLShader::AddIndex(unsigned int index) {
        this->_numIndices++;

        unsigned int *newIndexArray = new unsigned int[this->_numIndices];
        for (int i = 0; i < (int)(this->_numIndices - 1); i++)
            newIndexArray[i] = this->_indices[i];
        newIndexArray[this->_numIndices - 1] = index;

        delete[] this->_indices;
        this->_indices = newIndexArray;
    }
}
