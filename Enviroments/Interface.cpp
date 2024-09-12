//----------------Interface.cpp------------------//
//  Author: Excilious
//  Date: 06/07/24
//  Abstraction: User interface using 2d textured planes.
//
//----------------------------------------------//

#include "Interface.h"

float InterfaceVertices[ ] = {
    -1.0f, -1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, 1.0f, 0.0f,
     1.0f,  1.0f, 1.0f, 1.0f,
    -1.0f,  1.0f, 0.0f, 1.0f
};

unsigned int InterfaceIndices[ ] = {
    0, 1, 2,
    0, 2, 3
};


Interface::Interface()
{};

void Interface::GenerateTextures(std::string FileName)
{
    stbi_set_flip_vertically_on_load(true);
    glGenTextures(1,&Texture);
    glBindTexture(GL_TEXTURE_2D,Texture);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    
    int Width,Height,Channel;
    unsigned char *Data = stbi_load(FileName.c_str(),&Width,&Height,&Channel,0);
    if (Data)
    {
        if (Channel == 4){glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,Width,Height,0,GL_RGBA,GL_UNSIGNED_BYTE,Data);}
        else if (Channel == 3) {glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,Width,Height,0,GL_RGB,GL_UNSIGNED_BYTE,Data);}
        else if (Channel == 1) {glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,Width,Height,0,GL_RED,GL_UNSIGNED_BYTE,Data);}
    }
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(Data);
}

void Interface::GenerateText(const char* NewText,glm::vec4 NewTextColour,glm::vec2 NewTextPosition,float Scale)
{
    if (!gltInit())
    {glfwTerminate();}

    TextPosition = NewTextPosition;
    TextScale = Scale;
    TextContents = NewText;
    TextColour = NewTextColour;
    Text = gltCreateText();
    gltSetText(Text,NewText);
}

void Interface::RenderText()
{
    gltBeginDraw();
    gltColor(TextColour.x,TextColour.y,TextColour.z,TextColour.w);
    gltDrawText2D(Text,TextPosition.x,TextPosition.y,TextScale);
    gltEndDraw();
}

void Interface::DestroyText()
{
    gltDeleteText(Text);
    gltTerminate();
}

void Interface::GenerateInterface(std::string FileName,glm::vec2 Scale,glm::vec2 Position,int WindowWidth,int WindowHeight)
{
    glm::vec2 ScaleFactor = glm::vec2(0.75f,0.75f);
    Scale *= ScaleFactor;
    Shader2D.CreateNewShader("../../Shaders/InterfaceShader/Interface.vert","../../Shaders/InterfaceShader/Interface.frag");
    InputOffset = 1.0f;
    InputPosition = glm::vec3(Position,0.0f);
    InputScale = glm::vec3(Scale,1.0f);
    ScaleMatrix = glm::scale(ScaleMatrix,InputScale);

    glGenVertexArrays(1,&GLVertexArray);
    glGenBuffers(1,&GLVertexBuffer);
    glGenBuffers(1,&GLElementBuffer);
    glBindVertexArray(GLVertexArray);

    glBindBuffer(GL_ARRAY_BUFFER,GLVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(InterfaceVertices),InterfaceVertices,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,GLElementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(InterfaceIndices),InterfaceIndices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)(2*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    GenerateTextures(FileName);
};

void Interface::RenderInterface()
{
    Shader2D.ActivateShader();
    glBindTexture(GL_TEXTURE_2D,Texture);
    glUniform3f(glGetUniformLocation(Shader2D.Program,"position"),InputPosition.x,InputPosition.y,InputPosition.z);
    glUniform1f(glGetUniformLocation(Shader2D.Program,"ZOffset"),InputOffset);
    glUniformMatrix4fv(glGetUniformLocation(Shader2D.Program,"scale"),1,GL_FALSE,glm::value_ptr(ScaleMatrix));
    glBindVertexArray(GLVertexArray);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}

void Interface::DestroyInterface()
{
    Shader2D.DestroyShader();
    glDeleteVertexArrays(1,&GLVertexArray);
    glDeleteBuffers(1,&GLVertexBuffer);
    glDeleteBuffers(1,&GLElementBuffer);
}