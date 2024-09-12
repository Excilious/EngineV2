#include "Enviroments/Humanoid/Character.h"
#include "Enviroments/World.h"
#include "Physics/Physics.h"

#ifndef DEBUG
#define DEBUG
#endif

#ifdef DEBUG
    #include <typeinfo>
#endif

#define LIGHT_ENTITY_ID glm::vec4(1.0f,0.0f,0.0f,0.0f)
#define PLAYER_ENTITY_ID glm::vec4(2.0f,0.0f,0.0f,0.0f)
#define GAME_STATE_MENU     0x00000001
#define GAME_STATE_PLAY     0x00000002
#define GAME_STATE_END      0x00000003
#define GAME_STATE_DIED     0x00000004


#define MAX_INTERFACE 256
#define MAX_PLAYER_HEALTH 100;
