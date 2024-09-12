//-------------------Model.cpp--------------------//
//  Date: 06/04/24
//  Abstraction: Model function to store multiple meshes 
//
//----------------------------------------------//

#include "Model.h"

Model::Model(const char* NewFile,glm::quat Rotation,glm::vec3 Scale,glm::vec3 Position,unsigned int Instances)
{
    Model::Rotation = Rotation;
    Model::Scale = Scale;
    Model::Position = Position;
    
    std::string NewText;
    if (ModelContents.size() == 0 || PrecachedModelIndex.find(NewFile) != PrecachedModelIndex.end())
    {NewText = GetShaderContents(NewFile);}
    else
    {NewText = ModelContents.data()[PrecachedModelIndex.find(NewFile)->second];}

    JSON = Json::parse(NewText);
    Model::NewFile = NewFile;
    Model::Instances = Instances;
    Model::InstanceMatrix = GenerateInstanceMatrix(Rotation,Scale,Position);
    NewData = GetData();
    TraverseNode(0);
}

std::vector<glm::mat4> Model::GenerateInstanceMatrix(glm::quat Rotation,glm::vec3 Scale,glm::vec3 Position)
{
    std::vector<glm::mat4> InstanceMatrix;

    TranslationPosition = glm::translate(TranslationPosition,Position);
    NewRotation = glm::mat4_cast(Rotation);
    NewScale = glm::scale(NewScale,Scale);

    InstanceMatrix.push_back(TranslationPosition*NewRotation*NewScale);
    return InstanceMatrix;
}

void Model::GetCachedData(std::vector<std::string> NewModelContents,std::map<std::string,int> NewPrecachedModelIndex)
{
    ModelContents = NewModelContents;
    PrecachedModelIndex = NewPrecachedModelIndex;
}

void Model::Draw(Shader& NewShader,Camera& NewCamera)
{
    for (unsigned int x = 0; x < NewMeshes.size(); x++)
    {NewMeshes[x].Mesh::Draw(NewShader,NewCamera,MatricesMeshes[x],Position,Rotation,Scale);}
}

void Model::TraverseNode(unsigned int NextNode, glm::mat4 Matrix)
{
    Json Node = JSON["nodes"][NextNode];

    glm::vec3 Translation = glm::vec3(0.0f,0.0f,0.0f);
    if (Node.find("translation") != Node.end())
    {
        float TranslationValue[3];
        for (unsigned int x = 0; x < Node["translation"].size(); x++)
        { TranslationValue[x] = (Node["translation"][x]);}

        Translation = glm::make_vec3(TranslationValue);
    } 
    
    glm::quat Rotation = glm::quat(1.0f,0.0f,0.0f,0.0f);
    if (Node.find("rotation") != Node.end())
    {
        float RotationValues[4] = {
            Node["rotation"][3],
            Node["rotation"][0],
            Node["rotation"][1],
            Node["rotation"][2],
        };
        Rotation = glm::make_quat(RotationValues);
    }

    glm::vec3 Scale = glm::vec3(1.0f,1.0f,1.0f);
    if (Node.find("scale") != Node.end())
    {
        float ScaledValues[3];
        for (unsigned int x = 0; x < Node["scale"].size(); x++)
        {ScaledValues[x] = (Node["scale"][x]);}

        Scale = glm::make_vec3(ScaledValues);
    }

    glm::mat4 MatrixNode = glm::mat4(1.0f);
    if (Node.find("matrix") != Node.end())
    {
        float MatrixValues[16];
        for (unsigned int x = 0; x < Node["matrix"].size(); x++)
        {MatrixValues[x] = (Node["matrix"][x]);}

        MatrixNode = glm::make_mat4(MatrixValues);
    }

    glm::mat4 NewTranslation = glm::mat4(1.0f);
    glm::mat4 NewRotation = glm::mat4(1.0f);
    glm::mat4 NewScale = glm::mat4(1.0f);

    NewTranslation = glm::translate(NewTranslation,Translation);
    NewRotation = glm::mat4_cast(Rotation);
    NewScale = glm::scale(NewScale,Scale);

    glm::mat4 MatrixNextNode = Matrix * MatrixNode * NewTranslation * NewRotation * NewScale;
    if (Node.find("mesh") != Node.end())
    {
        TranslationsMeshes.push_back(Translation);
        RotationMeshes.push_back(Rotation);
        ScaleMeshes.push_back(Scale);
        MatricesMeshes.push_back(MatrixNextNode);

        LoadMesh(Node["mesh"]);
    }

    if (Node.find("children") != Node.end())
    {
        for (unsigned int x = 0; x < Node["children"].size(); x++)
        {TraverseNode(Node["children"][x],MatrixNextNode);}
    }
}

std::vector<float> Model::ConvertToVectorFloat(std::vector<Vertex> Vertices)
{
    std::vector<float> NewVertices = {};
    for (int VertexIndex = 0; VertexIndex < Vertices.size(); VertexIndex++)
    {
        NewVertices.push_back(Vertices.data()[VertexIndex].Position.x);
        NewVertices.push_back(Vertices.data()[VertexIndex].Position.y);
        NewVertices.push_back(Vertices.data()[VertexIndex].Position.z);
    }
    return NewVertices;
}

void Model::LoadMesh(unsigned int IndicesMesh)
{
    unsigned int PositionAccessorIndices = JSON["meshes"][IndicesMesh]["primitives"][0]["attributes"]["POSITION"];
    unsigned int NormalAccessorIndices = JSON["meshes"][IndicesMesh]["primitives"][0]["attributes"]["NORMAL"];
    unsigned int TextureAccessorIndices = JSON["meshes"][IndicesMesh]["primitives"][0]["attributes"]["TEXCOORD_0"];
    unsigned int IndicesAccessorIndices = JSON["meshes"][IndicesMesh]["primitives"][0]["indices"];

    std::vector<float> PositionVector = GetFloats(JSON["accessors"][PositionAccessorIndices]);
    std::vector<glm::vec3> Positions = FloatsGroupVec3(PositionVector);
    std::vector<float> NormalVector = GetFloats(JSON["accessors"][NormalAccessorIndices]);
    std::vector<glm::vec3> Normals = FloatsGroupVec3(NormalVector);
    std::vector<float> TextureVector = GetFloats(JSON["accessors"][TextureAccessorIndices]);
    std::vector<glm::vec2> TextureUV = FloatsGroupVec2(TextureVector);

    Vertices = AssembleVertices(Positions,Normals,TextureUV);
    Indices = GetIndices(JSON["accessors"][IndicesAccessorIndices]);
    std::vector<Texture> Textures = GetTextures();

    NewMeshes.push_back(Mesh(Vertices,Indices,Textures,Instances,InstanceMatrix));
}

std::vector<unsigned char> Model::GetData()
{
    std::string ByteText;
    std::string BufferURI = JSON["buffers"][0]["uri"];

    std::string FileString = std::string(NewFile);
    std::string FileDirectory = FileString.substr(0,FileString.find_last_of('/')+1);
    ByteText = GetShaderContents((FileDirectory+BufferURI).c_str());
    
    std::vector<unsigned char> NewData(ByteText.begin(),ByteText.end());
    return NewData;
}

std::vector<float> Model::GetFloats(Json Accessor)
{
    std::vector<float> FloatVector;

    unsigned int BufferViewIndex = Accessor.value("bufferView",1);
    unsigned int Count = Accessor["count"];
    unsigned int AccessorByteOffset = Accessor.value("byteOffset",0);

    std::string Type = Accessor["type"];
    Json BufferView = JSON["bufferViews"][BufferViewIndex];
    unsigned int ByteOffset = BufferView["byteOffset"];

    unsigned int NumberPerVertices;
    if (Type == "SCALAR") NumberPerVertices = 1;
    else if (Type == "VEC2") NumberPerVertices = 2;
    else if (Type == "VEC3") NumberPerVertices = 3;
    else if (Type == "VEC4") NumberPerVertices = 4;
    else throw std::invalid_argument("VEC3,VEC2,VEC1 OR SCALAR doesnt exist in Type");

    unsigned int StartOfData = ByteOffset + AccessorByteOffset;
    unsigned int LengthOfData = Count * 4 * NumberPerVertices;
    for (unsigned int x = StartOfData; x < StartOfData + LengthOfData; x)
    {
        unsigned char Bytes[] = {NewData[x++],NewData[x++],NewData[x++],NewData[x++]};
        float Value;
        std::memcpy(&Value,Bytes,sizeof(float));
        FloatVector.push_back(Value);
    }
    return FloatVector;
}

std::vector<GLuint> Model::GetIndices(Json Accessor)
{
    std::vector<GLuint> Indices;

    unsigned int BufferViewIndices = Accessor.value("bufferView",0);
    unsigned int Count = Accessor["count"];
    unsigned int AccessorByteOffset = Accessor.value("byteOffset",0);
    unsigned int ComponentType = Accessor["componentType"];

    Json BufferView = JSON["bufferViews"][BufferViewIndices];
    unsigned int ByteOffet = BufferView["byteOffset"];
    unsigned int StartOfData = ByteOffet + AccessorByteOffset;
    
    if (ComponentType == 5125)
    {
        for (unsigned int x = StartOfData; x < ByteOffet + AccessorByteOffset + Count * 4;x)
        {
            unsigned char Bytes[] = {NewData[x++],NewData[x++],NewData[x++],NewData[x++]};
            unsigned int Value;
            std::memcpy(&Value,Bytes,sizeof(unsigned int));
            Indices.push_back((GLuint)Value);
        }
    }
    else if (ComponentType == 5123)
    {
        for (unsigned int x = StartOfData; x < ByteOffet + AccessorByteOffset + Count * 2; x)
        {
          unsigned char Bytes[] = {NewData[x++],NewData[x++]};
          unsigned short Value;
          std::memcpy(&Value,Bytes,sizeof(unsigned short));
          Indices.push_back((GLuint)Value);

        }
    }
    else if (ComponentType == 5122)
    {
        for (unsigned int x = StartOfData; x < ByteOffet + AccessorByteOffset + Count * 2; x)
        {
            unsigned char Bytes[] = {NewData[x++],NewData[x++]};
            short Value;
            std::memcpy(&Value,Bytes,sizeof(short));
            Indices.push_back((GLuint)Value);
        }
    }
    return Indices;
}

std::vector<Texture> Model::GetTextures()
{
    std::vector<Texture> Textures;
    std::string FileString = std::string(NewFile);
    std::string FileDirectory = FileString.substr(0,FileString.find_last_of('/')+1);

    for (unsigned int x = 0; x < JSON["images"].size(); x++)
    {
        std::string TexturePath = JSON["images"][x]["uri"];
        bool Skip = false;
        for (unsigned int y = 0; y < LoadedTextureName.size(); y++)
        {
            if (LoadedTextureName[y] == TexturePath)
            {
                Textures.push_back(LoadedTexture[y]);
                Skip = true;
                break;
            }
        }

        if (!Skip)
        {
            if (TexturePath.find("baseColor") != std::string::npos)
            {
                Texture Diffuse = Texture((FileDirectory+TexturePath).c_str(),"diffuse",LoadedTexture.size());
                Textures.push_back(Diffuse);
                LoadedTexture.push_back(Diffuse);
            }
            else if (TexturePath.find("metallicRoughness") != std::string::npos)
            {
                Texture Specular = Texture((FileDirectory+TexturePath).c_str(),"specular",LoadedTexture.size());
                Textures.push_back(Specular);
                LoadedTexture.push_back(Specular);
            }
            LoadedTextureName.push_back(TexturePath);
        }
    }
    return Textures;
}

std::vector<Vertex> Model::AssembleVertices(std::vector<glm::vec3> Position, std::vector<glm::vec3> Normal, std::vector<glm::vec2> TextureUV)
{
    std::vector<Vertex> Vertices;
    for (int x = 0; x < Position.size(); x++)
    {
       Vertices.push_back
       (Vertex{Position[x],Normal[x],glm::vec3(1.0f,1.0f,1.0f),TextureUV[x]});
    }
    return Vertices;
}

std::vector<glm::vec2> Model::FloatsGroupVec2(std::vector<float> FloatVector)
{
    std::vector<glm::vec2> Vectors;
    for (int x = 0; x < FloatVector.size(); x)
    {Vectors.push_back(glm::vec2(FloatVector[x++],FloatVector[x++]));}

    return Vectors;
}

std::vector<glm::vec3> Model::FloatsGroupVec3(std::vector<float> FloatVector)
{
    std::vector<glm::vec3> Vectors;
    for (int x = 0; x < FloatVector.size(); x)
    {Vectors.push_back(glm::vec3(FloatVector[x++],FloatVector[x++],FloatVector[x++]));}

    return Vectors;
}

std::vector<glm::vec4> Model::FloatsGroupVec4(std::vector<float> FloatVector)
{
    std::vector<glm::vec4> Vectors;
    for (int x = 0; x < FloatVector.size(); x)
    {Vectors.push_back(glm::vec4(FloatVector[x++],FloatVector[x++],FloatVector[x++],FloatVector[x++]));}

    return Vectors;
}