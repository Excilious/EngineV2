//-----------------Character.h--------------------//
//  Author: Excilious
//  Date: 06/08/24
//  Abstraction: Header file for character system.
//
//----------------------------------------------//

#ifndef CHARACTER_HEADER
#define CHARACTER_HEADER

#include "Animation.h"
#include <map>

class HumanoidCharacter
{
    public:
        HumanoidCharacter();
        Animation NewAnimator;
        void CreateNewCharacter(const char* NewFile,glm::quat Rotation,glm::vec3 Scale,glm::vec3 Position);
        void RenderAllNewCharacters(Shader& NewShader,Camera& NewCamera);
    private:
        int CharacterIndex = 0;
        std::map<int,Model> CharacterModel = {};
};

#endif