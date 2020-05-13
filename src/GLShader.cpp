#include "GLShader.hpp"

#include "GL/glew.h"

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

        // Pointing the VAO to correct locations
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3), (void*)offsetof(Vertex3, position));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex3), (void*)offsetof(Vertex3, color));

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3), (void*)offsetof(Vertex3, uv));
    }

    GLShader::~GLShader() {
        // Deleting the GL program
        glDeleteProgram(this->_programID);
    }

    void GLShader::Use() {
        glUseProgram(this->_programID);
    }

    void GLShader::Unuse() {
        glUseProgram(0);
    }

    void GLShader::Render(const Mesh &mesh) {
        this->Use();

        // Binding the VBO
        glBindBuffer(GL_ARRAY_BUFFER, mesh._vboID);

        // Uploading vertex data
        glBufferData(GL_ARRAY_BUFFER, mesh._numVertices * sizeof(Vertex3), nullptr, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, mesh._numVertices * sizeof(Vertex3), mesh._vertices);

        // Unbinding the VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Binding the IBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh._iboID);

        // Uploading index data to the IBO
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh._numIndices * sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, mesh._numIndices * sizeof(unsigned int), mesh._indices);

        // Unbinding the IBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Binding vertex array
        glBindVertexArray(mesh._vaoID);

        // Drawing vertices
        glDrawElements(GL_TRIANGLES, mesh._numIndices, GL_UNSIGNED_INT, 0);

        // Unbinding the VAO
        glBindVertexArray(0);

        this->Unuse();
    }

    void GLShader::UniformMatrix4fv(const char *name, const float *value) {
        this->Use();
        glUniformMatrix4fv(glGetUniformLocation(this->_programID, name), 1, GL_FALSE, value);
    }
}
