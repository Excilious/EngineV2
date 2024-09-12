//-----------------Physics.h--------------------//
//  Author: Excilious
//  Date: 06/08/24
//  Abstraction: Physics header for the physics engine.
//
//----------------------------------------------//

#ifndef PHYSICS_HEADER
#define PHYSICS_HEADER

#include <map>
#include <string>
#include <vector>
#include "Intertia.h"
#include "Collision.h"

#define PI 3.14159265358979323846

class Physics
{
    public:
        Collision CollisionEngine;
        Intertia IntertiaEngine;

        Physics();
        void BindWorldVertices(std::vector<float> Vertices,std::vector<unsigned int> Indices,glm::mat4 WorldMatrix);
        float CalculateKinesmatics(float Acceleration,float Time,float Position,float Velocity);
        glm::vec3 ApplyEntityGravity(glm::vec3 LastDisplacement,float Mass,float Velocity);
        glm::vec3 ApplyProjectileMotion(glm::vec3 LastDisplacement,float DeltaTime);

    private:
        float PhysicsThreshold = 0.05f;
        std::vector<float> NewWorldVertices;
        std::vector<unsigned int> NewWorldIndices;
        glm::mat4 NewWorldMatrix;

};

#endif