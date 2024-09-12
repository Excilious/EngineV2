//------------------Console.h------------------//
//  Author: Excilious
//  Date: 17/07/24
//  Abstraction: Header script for console script.
//
//----------------------------------------------//

#ifndef CONSOLE_HEADER
#define CONSOLE_HEADER

#include "World.h"
#include "../Dependancies/glad/glad.h"
#include "../Dependancies/GLFW/glfw3.h"
#include <stdio.h>				
#include <string.h>
#include <sys/stat.h>

class Console
{
    public:
        Console();
        void GenerateConsole(GLFWwindow* NewWindow,int WindowWidth,int WindowHeight);
        void RenderConsole(GLFWwindow* NewWindow);
        void ConsoleLogic(const char* ConsoleInput);
        void Destroy();
        void PushNotifcation(std::string InputText);
        struct stat sb;

        double ConsoleBackloadTime;
        int ConsoleInputDelay = 1000;
        bool WorldHasLoaded = false;
        std::string CurrentWorldLocation;
        Interface ConsoleBackgroundInterface; 
    private:
        Interface ConsoleEnterInterface;
        std::string NewConsoleLine;

        std::vector<char> ConsoleLine = {};
        std::map<int,Interface> TextContainer = {};

        glm::vec4 ConsoleNormalColour = glm::vec4(1.0f,1.0f,1.0f,1.0f);
        glm::vec2 TextPosition = glm::vec2(0.0f,0.0f);

        float Scale = 1.0f;
        int WindowHeight;
        static void CharacterCallback(GLFWwindow* NewWindow,unsigned int KeyCode);
};


#endif