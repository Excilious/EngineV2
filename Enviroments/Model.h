//-------------------Model.h--------------------//
//  Date: 06/04/24
//  Abstraction: Header file for the model script.
//
//----------------------------------------------//

#ifndef MODEL_HEADER
#define MODEL_HEADER

#include "jsonimport/json.h"
#include "Mesh.h"

#include <string>
#include <filesystem>
#include <map>
#include <vector>

using Json = nlohmann::json;

class Model
{
    public:
        Model(const char* NewFile,glm::quat Rotation,glm::vec3 Scale,glm::vec3 Position,unsigned int Instances = 1);
        void Draw(Shader& NewShader,Camera& NewCamera);
        void PreCacheModelData(std::string Directory);
        void GetCachedData(std::vector<std::string> NewModelContents,std::map<std::string,int> NewPrecachedModelIndex);
        Json JSON;
        Shader NewShader;
        glm::quat Rotation;
        glm::vec3 Scale;
        glm::vec3 Position;
        std::vector<glm::mat4> InstanceMatrix;
        std::vector<float> ConvertToVectorFloat(std::vector<Vertex> Vertices);
        
        glm::vec3 Maximum;
        glm::vec3 Minimum;

        std::vector<Vertex> Vertices;
        std::vector<GLuint> Indices;
        glm::mat4 TranslationPosition = glm::mat4(1.0f);
        glm::mat4 NewRotation = glm::mat4(1.0f);
        glm::mat4 NewScale = glm::mat4(1.0f);

        std::vector<std::string> ModelContents;
        std::map<std::string,int> PrecachedModelIndex;
    private:
        const char* NewFile;
        std::vector<unsigned char> NewData;
        unsigned int Instances;

        std::vector<Mesh> NewMeshes;
        std::vector<glm::vec3> TranslationsMeshes;
        std::vector<glm::quat> RotationMeshes;
        std::vector<glm::vec3> ScaleMeshes;
        std::vector<glm::mat4> MatricesMeshes;
        
        std::vector<std::string> LoadedTextureName;
        std::vector<Texture> LoadedTexture;

        void LoadMesh(unsigned int IndicesMesh);
        void TraverseNode(unsigned int NextNode, glm::mat4 Matrix = glm::mat4(1.0f));
        
        std::vector<unsigned char> GetData();
        std::vector<float> GetFloats(Json Accessor);
        std::vector<GLuint> GetIndices(Json Accessor);
        std::vector<Texture> GetTextures();

        std::vector<Vertex> AssembleVertices
        (
            std::vector<glm::vec3> Position,
            std::vector<glm::vec3> Normal,
            std::vector<glm::vec2> TextureUV
        );
        
        std::vector<glm::mat4> GenerateInstanceMatrix(glm::quat Rotation,glm::vec3 Scale,glm::vec3 Position);
        std::vector<glm::vec2> FloatsGroupVec2(std::vector<float> FloatVector);
        std::vector<glm::vec3> FloatsGroupVec3(std::vector<float> FloatVector);
        std::vector<glm::vec4> FloatsGroupVec4(std::vector<float> FloatVector);

};

#endif