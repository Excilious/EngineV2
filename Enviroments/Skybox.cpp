//------------------Skybox.cpp------------------//
//  Author: Excilious
//  Date: 12/06/24
//  Abstraction: Rendering the worlds skybox.
//
//----------------------------------------------//

#include "Skybox.h"

float SkyboxVertices[] = {
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f  -1.0f 
};

unsigned int SkyboxIndices[] = {
    1,2,6,
    6,5,1,
    0,4,7,
    7,3,0,
    4,5,6,
    6,7,4,
    0,3,2,
    2,1,0,
    0,1,5,
    5,4,0,
    3,7,6,
    6,2,3
};

Skybox::Skybox(int WindowWidth,int WindowHeight,float Near,float Far)
{
    stbi_set_flip_vertically_on_load(false);
    WINDOW_WIDTH = WindowWidth;
    WINDOW_HEIGHT = WindowHeight;
    NEAR_VIEW = Near;
    FAR_VIEW = Far;

    glGenVertexArrays(1,&SkyboxVertexArrayObject);
    glGenBuffers(1,&SkyboxVertexBufferObject);
    glGenBuffers(1,&SkyboxVertexElementObject);

    glBindVertexArray(SkyboxVertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER,SkyboxVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER,sizeof(SkyboxVertices),&SkyboxVertices,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,SkyboxVertexElementObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(SkyboxIndices),&SkyboxIndices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    glGenTextures(1,&CubemapTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP,CubemapTexture);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);


    for (unsigned int x = 0; x < 6; x++)
    {
        int Width,Height,Channels;
        unsigned char* Data = stbi_load(FaceCubemap[x].c_str(),&Width,&Height,&Channels,0);
        if (Data)
        {
            stbi_set_flip_vertically_on_load(false);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+x,0,GL_RGB,Height,Width,0,GL_RGB,GL_UNSIGNED_BYTE,Data);
            stbi_image_free(Data);
        }
        else 
        {
            std::cout << "failed to load textures" << FaceCubemap[x] << "\n";
            stbi_image_free(Data);
        }
    }
}

void Skybox::RenderSkybox(glm::vec3 Position,glm::vec3 Orientation,glm::vec3 UpPosition,Shader SkyboxShader)
{
    glDepthFunc(GL_LEQUAL);
    SkyboxShader.ActivateShader();
    glm::mat4 View = glm::mat4(1.0f);
    glm::mat4 Projection = glm::mat4(1.0f);
    
    View = glm::mat4(glm::mat3(glm::lookAt(Position,Position+Orientation,UpPosition)));
    Projection = glm::perspective(glm::radians(45.0f),(float)WINDOW_WIDTH/WINDOW_HEIGHT,NEAR_VIEW,FAR_VIEW);
    glUniformMatrix4fv(glGetUniformLocation(SkyboxShader.Program,"view"),1,GL_FALSE,glm::value_ptr(View));
    glUniformMatrix4fv(glGetUniformLocation(SkyboxShader.Program,"projection"),1,GL_FALSE,glm::value_ptr(Projection));

    glBindVertexArray(SkyboxVertexArrayObject);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP,CubemapTexture);
    glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}