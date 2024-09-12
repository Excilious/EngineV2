//-----------------Collision.h------------------//
//  Author: Excilious
//  Date: 23/06/24
//  Abstraction: Header for collision script.
//
//----------------------------------------------//

#ifndef COLLISION_HEADER
#define COLLISION_HEADER
#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <vector>
#include <map>
#include "../Dependancies/glad/glad.h"
#include "../Dependancies/GLFW/glfw3.h"
#include "../Dependancies/glm/glm.hpp"
#include "../Dependancies/glm/gtc/matrix_transform.hpp"
#include "../Dependancies/glm/gtc/type_ptr.hpp"
#include "../Dependancies/glm/gtx/string_cast.hpp"

#define EPSILON 0.0000001f

enum InstanceState
{
    STATE_REBOUND,
    STATE_ACCELERATION,
    STATE_DECELERATION,
    STATE_STATIONARY,
    STATE_JUMPING,
    STATE_FALLING,
    STATE_DEAD
};

enum InstanceShape
{
    SHAPE_PRISM,
    SHAPE_CYLINDER,
    SHAPE_QUAD,
    SHAPE_SPHERE
};

struct BoundingBox
{
    glm::vec3 Minimum;
    glm::vec3 Maximum;
};

struct EntityBody
{
    float Mass;
    float Volume;
    float Density;
    InstanceState EntityBodyState;
    InstanceShape EntityBodyShape;
    glm::vec3 EntityCurrentPosition;
    glm::vec3 EntityCurrentScale;
};

struct Triangle
{
    glm::vec3 Vertex0;
    glm::vec3 Vertex1;
    glm::vec3 Vertex2;
};

class Collision
{
    public:
        Collision();

        bool GenerateCollision(glm::vec3 Position,std::vector<float> Vertices,std::vector<unsigned int> Indices,glm::mat4 ModelMatrix,float Threshold);
        bool IsVectorInTriangle(glm::vec3 Point,glm::vec3 Vertex0,glm::vec3 Vertex1,glm::vec3 Vertex2);
        bool IsPointNearPlane(glm::vec3 Point,glm::vec3 PlanePoint,glm::vec3 PlaneNormal,float Threshold);

        BoundingBox GenerateBoundingBox(std::vector<float> Vertices,std::vector<unsigned int> Indices,glm::mat4 ModelMatrix);
    private:
        glm::vec3 GetVertexPosition(std::vector<float> Vertices,size_t Index);
        glm::vec3 MatrixPosition(glm::vec3 Position,glm::mat4 Matrix);
};

#endif