//--------------------Main.h--------------------//
//  Author: Excilious
//  Date: 02/04/24
//  Abstraction: Main header files for precompiled values.
//
//----------------------------------------------//

#ifndef ENGINE_HEADER
#define ENGINE_HEADER
#define IMGUI_DEFINE_MATH_OPERATORS

#include <iostream>
#include <map>
#include <string>
#include "Dependancies/glad/glad.h"
#include "Dependancies/GLFW/glfw3.h"

#include "Enviroments/Console.h"
#include "Client/Player.h"

class Main
{
    public:
        std::map<std::string,std::string> TextureMap;
        Main();

    private:
        int STATE = GAME_STATE_MENU;
        int WindowWidth = 1920;
        int WindowHeight = 1080;
        float NearView = 0.1f;
        float FarView = 100.0f;
        float FieldOfView = 60.0f;
        
        float WaterHeight = 120.0f;
        float GridLength = 120.0f;
        double XPosition;
        double YPosition;
        unsigned int Counter = 0;
        unsigned int Samples = 8;

        const int VERSION_MAJOR = 3;
        const int VERSION_MINOR = 3;

        bool ConsoleActivated = false;
        int DebounceConsole = 10000;
        double CurrentTime = 0.0; 
        double LastTime = 0.0;
        int DeltaTime = 0;

        Console NewConsole;
        void Render(GLFWwindow* NewWindow);
        void Release(GLFWwindow* NewWindow);
        void UpdateWorld(World& NewWorld,Player& NewPlayer,std::string WorldFile);
};

#endif