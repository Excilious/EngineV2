//-----------------ElementBuffer.h----------------//
//  Author: Excilious
//  Date: 05/04/24
//  Abstraction: Header file for the element buffer object.
//
//----------------------------------------------//

#ifndef ELEMENT_BUFFER_HEADER
#define ELEMENT_BUFFER_HEADER

#include "../Dependancies/glad/glad.h"
#include "../Dependancies/GLFW/glfw3.h"
#include "../Dependancies/glm/glm.hpp"
#include <vector>

class ElementBufferObject
{
    public:
        GLuint ElementBuffer;
        ElementBufferObject(std::vector<GLuint>& Indices);
        void Bind();
        void Unbind();
        void Delete();
};


#endif