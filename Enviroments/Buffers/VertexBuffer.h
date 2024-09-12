//-----------------VertexBuffer.h-----------------//
//  Author: Excilious
//  Date: 05/04/24
//  Abstraction: Header file for the vertexbuffer script.
//
//----------------------------------------------//

#ifndef VERTEX_BUFFER_HEADER
#define VERTEX_BUFFER_HEADER

#include "../Dependancies/glad/glad.h"
#include "../Dependancies/glm/glm.hpp"
#include <vector>

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 Colour;
    glm::vec2 TextureUV;
};

class VertexBufferObject
{
    public:
        GLuint VertexBuffer;
        VertexBufferObject(std::vector<Vertex>& Vertices);
        VertexBufferObject(std::vector<glm::mat4>& Matrix4x4s);
        VertexBufferObject(std::vector<float>& Vertices);
        void Bind();
        void Unbind();
        void Delete();
};

#endif
