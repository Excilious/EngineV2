#include "Collision.h"

Collision::Collision()
{}

glm::vec3 Collision::GetVertexPosition(std::vector<float> Vertices,size_t Index)
{
    size_t IndexBase = Index*8;
    return glm::vec3(Vertices[IndexBase],Vertices[IndexBase+1],Vertices[IndexBase+2]); 
}

glm::vec3 Collision::MatrixPosition(glm::vec3 Position,glm::mat4 Matrix)
{
    glm::vec4 TransformedMatrix = Matrix*glm::vec4(Position,1.0f);
    return glm::vec3(TransformedMatrix);
}

bool Collision::IsPointNearPlane(glm::vec3 Point,glm::vec3 PlanePoint,glm::vec3 PlaneNormal,float Threshold)
{
    float Distance = glm::dot(PlaneNormal,Point-PlanePoint);
    return glm::abs(Distance) < Threshold;
}

bool Collision::GenerateCollision(glm::vec3 Position,std::vector<float> Vertices,std::vector<unsigned int> Indices,glm::mat4 ModelMatrix,float Threshold)
{
    for (int Index = 0; Index < Indices.size(); Index += 3)
    {
        glm::vec3 Vertex0 = glm::vec3(ModelMatrix*glm::vec4(GetVertexPosition(Vertices,Indices[Index]),1.0f));
        glm::vec3 Vertex1 = glm::vec3(ModelMatrix*glm::vec4(GetVertexPosition(Vertices,Indices[Index+1]),1.0f));
        glm::vec3 Vertex2 = glm::vec3(ModelMatrix*glm::vec4(GetVertexPosition(Vertices,Indices[Index+2]),1.0f));

        glm::vec3 Edge1 = Vertex1-Vertex0;
        glm::vec3 Edge2 = Vertex2-Vertex0;
        glm::vec3 Normal = glm::normalize(glm::cross(Edge1,Edge2));

        if (IsPointNearPlane(Position,Vertex0,Normal,Threshold))
        {
            if (IsVectorInTriangle(Position,Vertex0,Vertex1,Vertex2))
            {return true;}
        }
    }
    return false;
}

bool Collision::IsVectorInTriangle(glm::vec3 Point,glm::vec3 Vertex0,glm::vec3 Vertex1,glm::vec3 Vertex2)
{
    glm::vec3 Vertex0Point = Point-Vertex0;
    glm::vec3 Vertex1Point = Point-Vertex1;
    glm::vec3 Vertex2Point = Point-Vertex2;

    glm::vec3 Normal0 = glm::cross(Vertex1-Vertex0,Vertex0Point);
    glm::vec3 Normal1 = glm::cross(Vertex2-Vertex1,Vertex1Point);
    glm::vec3 Normal2 = glm::cross(Vertex0-Vertex2,Vertex2Point);
    if (glm::dot(Normal0,Normal1) >= 0 && glm::dot(Normal0,Normal2) >= 0)
    {return true;}
    return false;
}

BoundingBox Collision::GenerateBoundingBox(std::vector<float> Vertices,std::vector<unsigned int> Indices,glm::mat4 ModelMatrix)
{
    BoundingBox NewBoundBox;
    std::vector<glm::vec3> VertexCollection;
    for (int IndicesIndex = 0; IndicesIndex < Indices.size(); IndicesIndex++)
    {
        glm::vec3 NewVertex = glm::vec3(Vertices.data()[Indices.data()[IndicesIndex]],Vertices.data()[Indices.data()[IndicesIndex+1]],Vertices.data()[Indices.data()[IndicesIndex+2]]);
        NewVertex = MatrixPosition(NewVertex,ModelMatrix);
        VertexCollection.push_back(NewVertex);
    }
    glm::vec3 CurrentMinimum = VertexCollection.data()[0];
    glm::vec3 CurrentMaximum = VertexCollection.data()[0];
    for (int VertexIndex = 0; VertexIndex < VertexCollection.size(); VertexIndex++)
    {
        NewBoundBox.Minimum.x = std::min(CurrentMinimum.x,VertexCollection.data()[VertexIndex].x);
        NewBoundBox.Minimum.y = std::min(CurrentMinimum.y,VertexCollection.data()[VertexIndex].y);
        NewBoundBox.Minimum.z = std::min(CurrentMinimum.z,VertexCollection.data()[VertexIndex].z);

        NewBoundBox.Maximum.x = std::max(CurrentMaximum.x,VertexCollection.data()[VertexIndex].x);
        NewBoundBox.Maximum.y = std::max(CurrentMaximum.y,VertexCollection.data()[VertexIndex].y);
        NewBoundBox.Maximum.z = std::max(CurrentMaximum.z,VertexCollection.data()[VertexIndex].z);
    }
    return NewBoundBox;
}