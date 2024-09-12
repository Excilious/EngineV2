//---------------ElementBuffer.cpp----------------//
//  Author: Excilious
//  Date: 05/04/24
//  Abstraction: Main script for element buffer.
//
//----------------------------------------------//

#include "ElementBuffer.h"

ElementBufferObject::ElementBufferObject(std::vector<GLuint>& Indices)
{
    glGenBuffers(1,&ElementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ElementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,Indices.size()*sizeof(GLuint),Indices.data(),GL_STATIC_DRAW);
}

void ElementBufferObject::Bind()
{glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ElementBuffer);}

void ElementBufferObject::Unbind()
{glBindBuffer(GL_ARRAY_BUFFER,0);}

void ElementBufferObject::Delete()
{glDeleteBuffers(1,&ElementBuffer);}

