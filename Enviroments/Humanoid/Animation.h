//-----------------Animation.h--------------------//
//  Author: Excilious
//  Date: 06/08/24
//  Abstraction: Header files for animation system.
//
//----------------------------------------------//

#ifndef ANIMATION_HEADER
#define ANIMATION_HEADER

#include "../Model.h"
#include <map>
#include <vector>
#include <string>  

struct NewJoint
{
    int JointID;
    glm::vec3 Scale;
    glm::quat Rotation;
    glm::vec3 Translation;
    std::vector<int> Children = {};
    std::string NewJointName;
};

class Animation
{
    public:
        Animation();
        void ReadAnimationFromModel(Model& NewModel);
        bool CheckIfValueIsNull(Json NewValues);

    private:
        std::map<int,int> JointMap = {};
        std::map<int,NewJoint> SkeletonMap = {};
};

#endif