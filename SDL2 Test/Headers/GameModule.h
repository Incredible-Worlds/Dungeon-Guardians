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
#include <vector>

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

    PositionData()
    {
        posx = 10;
        posy = 10;
    }
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

    EnemyData()
    {
        type = 0;
        health = 0;
        gold = 0;
        enemyStatus = true;
        position.posx = 0;
        position.posy = 0;
    }

    int GatherHealth(int type)
    {
        switch (type)
        {
        case ORGE:
            return 4;
        case GOBLIN:
            return 3;
        case SKELETON:
            return 2;
        case SLIME:
            return 1;
        default:
            return 0;
        }
    }

    int takeDamage(int str)
    {
        return health -= str;
    }

    int getStrength()
    {
        return maxHealth() / 3;
    }

    void generateNew()
    {
        type = randomEnemyType();
        health = GatherHealth(type);
        gold = rand() % 10;
    }

    int getHealth()
    {
        return health;
    }

    bool isDead()
    {
        return health <= 0;
    }

    int maxHealth()
    {
        return GatherHealth(type);
    }

    int gatherGold()
    {
        return gold;
    }

private:
    int randomEnemyType()
    {
        srand(time(NULL));

        return rand() % 4;
    }
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

    PlayerData()
    {
        status = true;
        health = 50;
        gold = 0;
        lv = 1;
        str = (int)(lv / 2 + 2);

        position.posx = 0;
        position.posy = 0;
    }

    // (Dead or alive, health points, gold, level, strength, pos on x and y)
    PlayerData(bool alive, 
                int current_health, 
                int current_gold, 
                int current_lv, 
                int current_str, 
                int x, 
                int y)
    {
        status = alive;
        health = current_health;
        gold = current_gold;
        lv = current_lv;
        str = current_str;
        position.posx = x;
        position.posy = y;
    }

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

    AreaData()
    {
        tileName = tileType::EMPTY;
        tileStatus = false;
        tileStatusTimer = 0;

        position.posx = 10;
        position.posy = 10;
    }

    AreaData(int Name_of_Tile, 
        bool Status_of_Tile,
        int Timer_of_Tile,
        int pos_on_x,
        int pos_on_y)
    {
        tileName = Name_of_Tile;
        tileStatus = Status_of_Tile;
        tileStatusTimer = Timer_of_Tile;

        position.posx = pos_on_x;
        position.posy = pos_on_y;
    }
};

#include "MapSaveLoad.h"
#include "AIver2.h"
#include "Inventory.h"


int DefineTileStatus(tileType type);

int HideShowConsole(bool& ConsoleStatus);

int CollisionCheck(AreaData* world, PositionData position, directionType direction);

int EnemyMovement(PositionData& position, AreaData* world);

//Easy4ENCE