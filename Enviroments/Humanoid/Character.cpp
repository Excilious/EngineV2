//-----------------Character.cpp--------------------//
//  Author: Excilious
//  Date: 06/08/24
//  Abstraction: Physical world body character.
//
//----------------------------------------------//

#include "Character.h"

HumanoidCharacter::HumanoidCharacter()
{}

void HumanoidCharacter::CreateNewCharacter(const char* NewFile,glm::quat Rotation,glm::vec3 Scale,glm::vec3 Position)
{
    Model NewModel(NewFile,Rotation,Scale,Position,1);
    CharacterModel.insert({CharacterIndex,NewModel});
    CharacterIndex++;

    NewAnimator.ReadAnimationFromModel(NewModel);
}

void HumanoidCharacter::RenderAllNewCharacters(Shader& NewShader,Camera& NewCamera)
{
    for (std::map<int,Model>::iterator NewCharacterIndex = CharacterModel.begin(); NewCharacterIndex != CharacterModel.end(); NewCharacterIndex++)
    {NewCharacterIndex->second.Draw(NewShader,NewCamera);}
}