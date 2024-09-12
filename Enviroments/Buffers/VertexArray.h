//-----------------VertexArray.h-----------------//
//  Author: Excilious
//  Date: 05/04/24
//  Abstraction: Header file for the vertexarray script.
//
//----------------------------------------------//

#ifndef VERTEX_ARRAY_HEADER
#define VERTEX_ARRAY_HEADER

#include "../Dependancies/glad/glad.h"
#include "VertexBuffer.h"
#include <vector>

class VertexArrayObject
{
    public:
        GLuint VertexArray;
        VertexArrayObject();
        void Bind();
        void Unbind();
        void Delete();
        void LinkAttribute(VertexBufferObject& VertexBuffer,GLuint Layout,GLuint Components,GLenum Type,GLsizeiptr Stride,void* Offset);
};

#endif