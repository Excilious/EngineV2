//-----------------VertexArray.cpp---------------//
//  Author: Excilious
//  Date: 05/04/24
//  Abstraction: Generates a new vertex array.
//
//----------------------------------------------//

#include "VertexArray.h"

VertexArrayObject::VertexArrayObject()
{glGenVertexArrays(1,&VertexArray);}

void VertexArrayObject::Bind()
{glBindVertexArray(VertexArray);}

void VertexArrayObject::Unbind()
{glBindVertexArray(0);}

void VertexArrayObject::Delete()
{glDeleteVertexArrays(1,&VertexArray);}

void VertexArrayObject::LinkAttribute(VertexBufferObject& VertexBuffer,GLuint Layout,GLuint Components,GLenum Type,GLsizeiptr Stride,void* Offset)
{
    VertexBuffer.Bind();
    glVertexAttribPointer(Layout,Components,Type,GL_FALSE,Stride,Offset);
    glEnableVertexAttribArray(Layout);
    VertexBuffer.Unbind();
}