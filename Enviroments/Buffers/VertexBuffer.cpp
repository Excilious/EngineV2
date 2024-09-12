//----------------VertexBuffer.cpp-----------------//
//  Author: Excilious
//  Date: 05/04/24
//  Abstraction: Normal script for vertex buffer.
//
//----------------------------------------------//

#include "VertexBuffer.h"

VertexBufferObject::VertexBufferObject(std::vector<Vertex>& Vertices)
{
    glGenBuffers(1,&VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,Vertices.size()*sizeof(Vertex),Vertices.data(),GL_STATIC_DRAW);
}

VertexBufferObject::VertexBufferObject(std::vector<float>& Vertices)
{
    glGenBuffers(1,&VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,Vertices.size()*sizeof(float),Vertices.data(),GL_STATIC_DRAW);
}

VertexBufferObject::VertexBufferObject(std::vector<glm::mat4>& Matrix4x4s)
{
    glGenBuffers(1,&VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,Matrix4x4s.size()*sizeof(Vertex),Matrix4x4s.data(),GL_STATIC_DRAW);

}

void VertexBufferObject::Bind()
{glBindBuffer(GL_ARRAY_BUFFER,VertexBuffer);}

void VertexBufferObject::Unbind()
{glBindBuffer(GL_ARRAY_BUFFER,0);}

void VertexBufferObject::Delete()
{glDeleteBuffers(1,&VertexBuffer);}