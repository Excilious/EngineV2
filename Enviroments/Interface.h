//----------------Interface.h------------------//
//  Author: Excilious
//  Date: 06/07/24
//  Abstraction: Header script for interface planes.
//
//----------------------------------------------//

#ifndef INTERFACE_HEADER
#define INTERFACE_HEADER
#define GLT_IMPLEMENTATION

#include "../Dependancies/glad/glad.h"
#include "../Dependancies/GLFW/glfw3.h"
#include "../Dependancies/glm/glm.hpp"
#include "../Dependancies/gltext/gltext.h"
#include "../Dependancies/glm/gtc/matrix_transform.hpp"

#include "Camera.h"
#include "Skybox.h"
#include <vector>
#include <map>

struct Character 
{
    int TextureID;
    glm::vec2 Size;
    glm::vec2 Bearing;
    unsigned int Advance;
};

class Interface
{
    public:
        Interface();
        void GenerateInterface(std::string FileName,glm::vec2 Scale,glm::vec2 Position,int WindowWidth,int WindowHeight);
        void RenderInterface();
        void DestroyInterface();

        void GenerateText(const char* Text,glm::vec4 NewTextColour,glm::vec2 NewTextPosition,float Scale);
        void RenderText();
        void DestroyText();

        bool IsTweenPlaying = false;
        float AlphaTransparency = 1.0f;
        const char* TextContents;

        glm::vec2 TextPosition;
        glm::vec3 InputPosition;
        glm::vec3 InputScale;
        glm::mat4 ScaleMatrix = glm::mat4(1.0f);
    private:
        glm::vec4 TextColour;
        GLTtext *Text;

        void GenerateTextures(std::string FileName);
        unsigned int Texture;
        float TextScale;
        float InputOffset;

        Shader Shader2D;
        GLuint GLVertexBuffer;
        GLuint GLElementBuffer;
        GLuint GLVertexArray;

        std::map<GLchar,Character> CharacterGroup;
        std::vector<glm::mat4> CharacterTransforms;
        std::vector<int> LetterMap;
};

#endif