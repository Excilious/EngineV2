//--------------------Main.cpp------------------//
//  Author: Excilious
//  Date: 02/04/24
//  Abstraction: Main file to run the engine.
//
//----------------------------------------------//

#define STB_IMAGE_IMPLEMENTATION
#include "Main.h"
#include <math.h>

Main::Main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,VERSION_MINOR);
    glfwWindowHint(GLFW_SAMPLES,Samples);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* NewWindow;
    //glfwGetPrimaryMonitor()
    NewWindow = glfwCreateWindow(WindowWidth,WindowHeight,"Realms",glfwGetPrimaryMonitor(),NULL);
    glfwMakeContextCurrent(NewWindow);
    gladLoadGL();
    glViewport(0,0,WindowWidth,WindowHeight);

    if (NewWindow == NULL)
    {glfwTerminate();}   
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {glfwTerminate();}

    Main::Render(NewWindow);
 
    glfwDestroyWindow(NewWindow);
    glfwTerminate();
}

void Main::Release(GLFWwindow* NewWindow)
{
    if (glfwGetKey(NewWindow,GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwTerminate();
        exit(0);
    }
}

void Main::UpdateWorld(World& NewWorld,Player& NewPlayer,std::string WorldFile)
{
    NewWorld.StartWorld(WorldFile);
    NewWorld.GenerateEntityMap();
    NewWorld.GenerateLightMap();
    NewWorld.GenerateAllAssets(WindowWidth,WindowHeight);
    NewPlayer.GenerateCharacter(NewWorld.Vertices,NewWorld.Indices,NewWorld.InstanceMatrix);
    NewPlayer.Generate(WindowWidth,WindowHeight,NewWorld.InterfaceWorldMap,STATE);
}

void Main::Render(GLFWwindow* NewWindow)
{
    glm::vec3 Position = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 Scale = glm::vec3(1.0f,1.0f,1.0f);
    glm::quat Rotation = glm::quat(0.0f,0.0f,0.0f,1.0f);

    Shader ShaderProgram;
    Shader SkyboxShader;
    Player NewPlayer;
    World NewWorld;
    Water NewWater;
    Camera NewCamera(WindowWidth,WindowHeight,glm::vec3(0.0f,0.0f,0.0f));
    Skybox NewSkybox(WindowWidth,WindowHeight,NearView,FarView);
    Model NewModel("../../Meshes/Player.gltf",Rotation,Scale,Position,1);

    glEnable(GL_DEPTH_TEST);
    glfwSwapInterval(1);
    glFrontFace(GL_CCW);

    TextureMap["sand"] = "../../Textures/Enviroments/sand.jpg";
    TextureMap["grass"] = "../../Textures/Enviroments/grass.jpg";
    TextureMap["rock"] = "../../Textures/Enviroments/rdiffuse.jpg";
    TextureMap["snow"] = "../../Textures/Enviroments/snow2.jpg";
    TextureMap["grass1"] = "../../Textures/Enviroments/rnormal.jpg";
    TextureMap["rockNormal"] = "../../Textures/Enviroments/terrainTexture.jpg";

    glUniform1i(glGetUniformLocation(SkyboxShader.Program,"skybox"),0);
    ShaderProgram.CreateNewShader("../../Shaders/Instance.vert","../../Shaders/Instance.frag");
    SkyboxShader.CreateNewShader("../../Shaders/Skybox.vert","../../Shaders/Skybox.frag");
    NewWater.GenerateWater(glm::vec2(0.0f,0.0f),WaterHeight,GridLength,NewCamera);
    ShaderProgram.ActivateShader();
    SkyboxShader.ActivateShader();
    NewConsole.GenerateConsole(NewWindow,WindowWidth,WindowHeight);
    NewConsole.PushNotifcation("Running On Resolution: "+std::to_string(WindowWidth)+"x"+std::to_string(WindowHeight));
    NewConsole.PushNotifcation("Press 'ESC' to exit program.");
    NewCamera.Position = glm::vec3(0.05f,0.0f,0.0f);

    NewPlayer.GenerateWeapons("../../Meshes/Ranger.gltf",Rotation,Position,Scale);

    while (!glfwWindowShouldClose(NewWindow))
    {
        CurrentTime = glfwGetTime();
        DeltaTime = CurrentTime-LastTime;
        LastTime = CurrentTime;
        glfwPollEvents();
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (STATE == GAME_STATE_MENU)
        {
            NewConsole.RenderConsole(NewWindow);
            if (NewConsole.WorldHasLoaded)
            {UpdateWorld(NewWorld,NewPlayer,NewConsole.CurrentWorldLocation); STATE = GAME_STATE_PLAY;}
        }
        else if (STATE == GAME_STATE_PLAY) 
        {
            NewPlayer.RenderFaces();
            NewPlayer.RenderWeapons(ShaderProgram,NewCamera);
            NewPlayer.Input(NewWindow,NewCamera,NewWorld,DeltaTime);
            NewCamera.UpdateMatrix(FieldOfView,NearView,FarView);
            NewCamera.UpdateCameraPosition(NewWindow,XPosition,YPosition);
            NewSkybox.RenderSkybox(NewCamera.Position,NewCamera.Orientation,NewCamera.UpPosition,SkyboxShader);
            NewWorld.RenderWorld(NewCamera);
            NewWorld.RenderAllEntities(ShaderProgram,NewCamera);
            NewWorld.RenderAllInterfaces();
            NewWater.Draw(NewCamera);
            NewModel.Draw(ShaderProgram,NewCamera);
            
            if (NewPlayer.HasPlayerDied)
            {STATE = GAME_STATE_DIED;}
        }
        else if (STATE == GAME_STATE_DIED)
        {
            if (glfwGetKey(NewWindow,GLFW_KEY_ENTER) == GLFW_PRESS)
            {
                STATE = GAME_STATE_PLAY;
                NewPlayer.FacesIndex = 1;
                NewPlayer.UpdateFaces();
                NewPlayer.HasPlayerDied = false;
                NewPlayer.NewPlayer.Health = MAX_PLAYER_HEALTH
                NewCamera.Position = glm::vec3(0.0f,0.0f,0.0f);
            }
        }
        Release(NewWindow);
        glfwGetCursorPos(NewWindow,&XPosition,&YPosition);
        glfwSwapBuffers(NewWindow);
    }

    NewWorld.Destroy();
    NewConsole.Destroy();
    SkyboxShader.DestroyShader();
    ShaderProgram.DestroyShader();
    glfwTerminate();
}