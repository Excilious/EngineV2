//-----------------Physics.cpp--------------------//
//  Author: Excilious
//  Date: 06/08/24
//  Abstraction: Main physics system for the physics engine.
//
//----------------------------------------------//

#include "Physics.h"

Physics::Physics()
{};

void Physics::BindWorldVertices(std::vector<float> Vertices,std::vector<unsigned int> Indices,glm::mat4 WorldMatrix)
{
    NewWorldVertices = Vertices;
    NewWorldIndices = Indices;  
    NewWorldMatrix = WorldMatrix;
}

float Physics::CalculateKinesmatics(float Acceleration,float Time,float Position,float Velocity)
{return (0.5f*Acceleration*Time*Time+Position);}

glm::vec3 Physics::ApplyProjectileMotion(glm::vec3 LastDisplacement,float DeltaTime)
{
    float NewPositionX = CalculateKinesmatics(0.0f,0.0f,LastDisplacement.x,DeltaTime/1000);
    float NewPositionY = CalculateKinesmatics(-9.81f,0.0f,LastDisplacement.y,DeltaTime/1000);

    return LastDisplacement;
}

glm::vec3 Physics::ApplyEntityGravity(glm::vec3 LastDisplacement,float Mass,float Velocity)
{
    glm::vec3 NewDisplacement = glm::vec3(0.0f,-9.81f*Mass,0.0f);
    if (CollisionEngine.GenerateCollision(LastDisplacement,NewWorldVertices,NewWorldIndices,NewWorldMatrix,PhysicsThreshold))
    {
        std::cout << "Entity collided!" << "\n";
        glm::vec3 PositionDisplacement = LastDisplacement-NewDisplacement;
        float FinalVelocity = Velocity*Velocity+2*(-9.81*Mass)*PositionDisplacement.y;
        NewDisplacement += glm::vec3(0.0f,-FinalVelocity,0.0f);
    }
    return NewDisplacement;
}