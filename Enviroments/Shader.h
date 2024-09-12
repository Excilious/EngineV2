//-------------------Shader.h--------------------//
//  Author: Excilious
//  Date: 02/04/24
//  Abstraction: Shader header file for precompiled values.
//
//----------------------------------------------//

#ifndef SHADER_HEADER_FILE
#define SHADER_HEADER_FILE

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

#include "../Dependancies/glad/glad.h"
#include "../Dependancies/GLFW/glfw3.h"

std::string GetShaderContents(const char* ShaderName);

class Shader
{
    public:
        GLuint Program;
        Shader();
        void CreateNewShader(const char* VertexShaderFile,const char* FragmentShaderFile);
        void ActivateShader();
        void DestroyShader();
};

#endif