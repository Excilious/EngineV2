//-----------------Animation.cpp--------------------//
//  Author: Excilious
//  Date: 06/08/24
//  Abstraction: Keyframed animation system.
//
//----------------------------------------------//

#include "Animation.h"

Animation::Animation()
{}

bool Animation::CheckIfValueIsNull(Json NewValues)
{
    for (int x = 0; x < NewValues.size(); x++)
    {
        if (NewValues[x] == NULL)
        {
            return true;
        }
    }
    return false; 
}

void Animation::ReadAnimationFromModel(Model& NewModel)
{
    for (int x = 0; x < NewModel.JSON["skins"][0]["joints"].size(); x++)
    {JointMap.insert({x,NewModel.JSON["skins"][0]["joints"][x]});}

    std::cout << NewModel.JSON["nodes"][0] << "\n";

    for (std::map<int,int>::iterator MapIndex = JointMap.begin(); MapIndex != JointMap.end(); MapIndex++)
    {
        Json NewNode = NewModel.JSON["nodes"][MapIndex->second];
        NewJoint JointFromSkeleton;
        JointFromSkeleton.JointID = MapIndex->second;

        JointFromSkeleton.Scale = (CheckIfValueIsNull(NewNode["scale"]) ? glm::vec3(NewNode["scale"][0],NewNode["scale"][1],NewNode["scale"][2]) : glm::vec3(0.0f,0.0f,0.0f));
        JointFromSkeleton.Translation = (CheckIfValueIsNull(NewNode["translation"]) ? glm::vec3(NewNode["translation"][0],NewNode["translation"][1],NewNode["translation"][2]) : glm::vec3(0.0f,0.0f,0.0f));
        JointFromSkeleton.Rotation = (CheckIfValueIsNull(NewNode["rotation"]) ? glm::quat(NewNode["rotation"][0],NewNode["rotation"][1],NewNode["rotation"][2],NewNode["rotation"][3]) : glm::quat(0.0f,0.0f,0.0f,1.0f));
        JointFromSkeleton.NewJointName = (NewNode.find("name") != NewNode.end() ? NewNode["name"] : "");

        if (NewNode.find("children") != NewNode.end())
        {
            for (int x = 0; x < NewNode["children"].size(); x++)
            {JointFromSkeleton.Children.push_back(NewNode["children"][x]);}
        }
        SkeletonMap.insert({MapIndex->first,JointFromSkeleton});
    }  
}

