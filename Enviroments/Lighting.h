//----------------Lighting.h------------------//
//  Author: Excilious
//  Date: 12/06/24
//  Abstraction: Header script for lighting.
//
//----------------------------------------------//

#ifndef LIGHTING_HEADER
#define LIGHTING_HEADER

#include "../CoreDefine.h"

class Lighting
{
    public:
        glm::vec3 LightPosition;
        glm::vec3 LightScale;
        glm::vec4 LightColour;

        Lighting();
        void CreateLightBlock(glm::vec3 Scale, glm::vec3 Position, glm::vec4 Colour);
        void RenderLightBlockWorld(Camera& NewCamera);
        void RenderLightBlockModel(Model& NewModel,Shader& NewModelShader,Camera& NewCamera);
    private:
        Shader NewLightShader;

        GLuint LightVertexArray;
        GLuint LightElementBuffer;
        GLuint LightVertexBuffer;
};

#endif