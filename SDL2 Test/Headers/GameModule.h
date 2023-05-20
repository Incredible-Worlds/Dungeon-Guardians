    // Kamys, Potrox and Bell404ll developers project
//
//          @ All rights reserved
//
// Open source version, only for course work

#pragma once 

#pragma warning(disable:4244)   // loss while time_t to int
#include "../../SDL2-2.0.9/include/SDL.h"
#include <iterator>
#include <ctime>
#include <Windows.h>

#include "Setings.h"
#include "MainMenu.h"

#define LOADERROR 3

// include Fight

// Consts
const int worldsize = 1024;

// ENUMs of objects
enum characterType 
{ 
    ORGE, 
    GOBLIN, 
    SLIME, 
    SKELETON 
};

enum tileType 
{ 
    BOUND, 
    EMPTY, 
    ENEMY,
    CHEST,
    EXIT
};

enum directionType
{
    RIGHT,
    LEFT,
    UP,
    DOWN
};

// Description of the position on x and y
class PositionData
{
public:
    int posx;
    int posy;

    PositionData();
};

// Description of the Enemy class
class EnemyData
{
public:
    int health;
    int type;
    int gold;
    bool enemyStatus;
    PositionData position;

    EnemyData();

    int GatherHealth(int type);

    int takeDamage(int str);

    int getStrength();

    void generateNew();

    int getHealth();

    bool isDead();

    int maxHealth();

    int gatherGold();

private:
    int randomEnemyType();
};

// Description of the Player class
class PlayerData
{
public:
    bool status;
    int health;
    int gold;
    int lv;
    int str;

    PositionData position;

    PlayerData();

    // (Dead or alive, health points, gold, level, strength, pos on x and y)
    PlayerData(bool alive,
        int current_health,
        int current_gold,
        int current_lv,
        int current_str,
        int x,
        int y);

    int setPos(int x, int y);
};

// Descriptiosn of Area class
class AreaData
{
public:
    int tileName;
    bool tileStatus;
    int tileStatusTimer;

    PositionData position;

    AreaData();

    AreaData(int Name_of_Tile,
        bool Status_of_Tile,
        int Timer_of_Tile,
        int pos_on_x,
        int pos_on_y);
};

#include "MapSaveLoad.h"
#include "AIver2.h"
#include "Inventory.h"


int DefineTileStatus(tileType type);

int HideShowConsole(bool& ConsoleStatus);

int CollisionCheck(AreaData* world, PositionData position, directionType direction);

int EnemyMovement(PositionData& position, AreaData* world);

//Easy4ENCE