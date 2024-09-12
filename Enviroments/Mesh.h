//--------------------Mesh.h--------------------//
//  Author: Excilious
//  Date: 05/04/24
//  Abstraction: Creation of new meshes with vertices.
//
//----------------------------------------------//

#ifndef MESH_HEADER
#define MESH_HEADER

#include <string>
#include "Buffers/VertexArray.h"
#include "Buffers/ElementBuffer.h"
#include "Terrain/Terrain.h"
#include "../Dependancies/glm/gtx/string_cast.hpp"

class Mesh
{
    public:
        std::vector <Vertex> Vertices;
        std::vector <GLuint> Indices;
        std::vector <Texture> Textures;

        VertexArrayObject VertexArray;
        unsigned int Instances;

        Mesh(
            std::vector<Vertex>& Vertices,
            std::vector<GLuint>& Indices,
            std::vector<Texture>& Textures,
            unsigned int Instances = 1,
            std::vector<glm::mat4> InstanceMatrix = {}
        );
        void Draw(Shader& ShaderInstance,Camera& CameraInstance,glm::mat4 Matrix = glm::mat4(1.0f),glm::vec3 Translation = glm::vec3(0.0f,0.0f,0.0f),glm::quat Rotation = glm::quat(1.0f,0.0f,0.0f,0.0f),glm::vec3 Scale = glm::vec3(1.0f,1.0f,1.0f));
};

#endif