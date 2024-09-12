//------------------Console.cpp------------------//
//  Author: Excilious
//  Date: 17/07/24
//  Abstraction: Console script for game script.
//
//----------------------------------------------//

#include "Console.h"
#include "../Client/SoundScape.h"

bool IsConsoleActive = false;

Console::Console()
{}

void Console::CharacterCallback(GLFWwindow* NewWindow,unsigned int KeyCode)
{
    Console *ConsoleHandler = reinterpret_cast<Console *>(glfwGetWindowUserPointer(NewWindow));
    if (IsConsoleActive)
    {
        char NewCode = KeyCode;
        ConsoleHandler->NewConsoleLine += NewCode;
    }
}

void Console::GenerateConsole(GLFWwindow* NewWindow,int WindowWidth,int WindowHeight)
{
    ConsoleBackgroundInterface.GenerateInterface("../../Textures/BackgroundRender.jpg",glm::vec2(3.0f,3.0f),glm::vec2(0.0f,0.0f),WindowWidth,WindowHeight);
    Console::WindowHeight = WindowHeight;
    IsConsoleActive = true;
    glfwSetWindowUserPointer(NewWindow,reinterpret_cast<void *>(this));
    glfwSetCharCallback(NewWindow,CharacterCallback);
}

void Console::PushNotifcation(std::string InputText)
{
    Interface NewTextContainer;
    NewTextContainer.GenerateText(InputText.c_str(),ConsoleNormalColour,TextPosition,Scale);
    TextContainer[TextPosition.y] = NewTextContainer;
    TextPosition.y += 20;
    if (TextContainer.size() >= int(WindowHeight/20))
    {
        for (std::map<int,Interface>::iterator TextLabel = TextContainer.begin(); TextLabel != TextContainer.end(); TextLabel++)
        {
            TextLabel->second.TextPosition.y -= 20;
            if (TextLabel->first < 0)
            {TextLabel->second.DestroyText();}
        }
    }
}

void Console::ConsoleLogic(const char* ConsoleInput)
{
    std::string StringConsoleInput = ConsoleInput;
    if (StringConsoleInput.substr(0,1) != "/")
    {PushNotifcation("Syntax Error: Invalid Command Given.");}
    else
    {
        if (StringConsoleInput.substr(1,6) == "World ")
        {
            std::string WorldIndexName = StringConsoleInput.substr(7,StringConsoleInput.length()-1);
            CurrentWorldLocation = "../../Client/";
            CurrentWorldLocation.append(WorldIndexName.c_str());

            std::cout << CurrentWorldLocation << "\n";
            if (stat(CurrentWorldLocation.c_str(),&sb) == 0 && !(sb.st_mode & S_IFDIR))
            {PushNotifcation("Loading World..."); WorldHasLoaded = true;}
            else
            {PushNotifcation("World Error: Cannot Find World.");}
        }
        else
        {PushNotifcation("Syntax Error: Invalid Command Given.");}
    }
}

void Console::RenderConsole(GLFWwindow* NewWindow)
{
    for (std::map<int,Interface>::iterator TextLabel = TextContainer.begin(); TextLabel != TextContainer.end(); TextLabel++)
    {TextLabel->second.RenderText();}

    ConsoleEnterInterface.GenerateText(NewConsoleLine.c_str(),ConsoleNormalColour,TextPosition,Scale);
    ConsoleEnterInterface.RenderText();
    ConsoleBackgroundInterface.RenderInterface();
    if (glfwGetKey(NewWindow,GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        if (NewConsoleLine.size() != 0)
        {
            PushNotifcation(NewConsoleLine);
            ConsoleLogic(NewConsoleLine.c_str());
            NewConsoleLine = "";
        }
    }
    else if (glfwGetKey(NewWindow,GLFW_KEY_BACKSPACE) == GLFW_PRESS)
    {
        double CurrentBackloadTime = glfwGetTime()*1000;
        if (CurrentBackloadTime-ConsoleBackloadTime > ConsoleInputDelay)
        {NewConsoleLine.erase(NewConsoleLine.size()-1);}
    }
}

void Console::Destroy()
{
    IsConsoleActive = false;
    ConsoleBackgroundInterface.DestroyInterface();
    for (std::map<int,Interface>::iterator TextLabel = TextContainer.begin(); TextLabel != TextContainer.end(); TextLabel++)
    {TextLabel->second.DestroyText();}
}