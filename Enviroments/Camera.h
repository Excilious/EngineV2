//------------------Camera.h------------------//
//  Author: Excilious
//  Date: 02/04/24
//  Abstraction: Header file for the camera player view.
//
//----------------------------------------------//

#ifndef CAMERA_HEADER
#define CAMERA_HEADER
#define GLM_ENABLE_EXPERIMENTAL

#include "../Dependancies/glad/glad.h"
#include "../Dependancies/GLFW/glfw3.h"
#include "../Dependancies/glm/glm.hpp"
#include "../Dependancies/glm/gtc/matrix_transform.hpp"
#include "../Dependancies/glm/gtc/type_ptr.hpp"
#include "../Dependancies/glm/gtx/rotate_vector.hpp"
#include "../Dependancies/glm/gtx/vector_angle.hpp"
#include "Shader.h"

class Camera
{
    public:
        int Width;
        int Height;
        glm::vec3 Position = glm::vec3(0.0f,1.0f,0.0f);
        glm::vec3 UpPosition = glm::vec3(0.0f,1.0f,0.0f);
        glm::vec3 Orientation = glm::vec3(0.0f,0.0f,-1.0f);
        glm::mat4 CameraMatrix = glm::mat4(1.0f);

        glm::mat4 ViewMatrix = glm::mat4(1.0f);
        glm::mat4 ProjectionMatrix = glm::mat4(1.0f);

        Camera(int WINDOW_WIDTH,int WINDOW_HEIGHT,glm::vec3 Position);
        void UpdateMatrix(float FieldOfView,float NearPlane,float FarPlane);
        void SetMatrix(Shader& ShaderInstance,const char* Uniform);
        void MoveCamera(GLFWwindow* InputWindow);
        void UpdateCameraPosition(GLFWwindow* InputWindow,double XPosition,double YPosition);
    private:
        float LastX = 0;
        float LastY = 0;
        float RotateX = 0;
        float RotateY = 0;
        float XOffset = 0;
        float YOffset = 0;
        bool FirstMouse = true;

        float Sensitivity = 0.1f;
        bool MouseCursorLocked = false;
};

#endif