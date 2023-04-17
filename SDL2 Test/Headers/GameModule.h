// Kamys, Potrox and Bell404ll developers project
//
//          @ All rights reserved
//
// Not open source version, only for course work

#pragma once 
#pragma warning(disable:4244)   // loss while time_t to int
#include <iterator>
#include <Windows.h>
#include <iostream>

// ENUM of objects
enum characterType 
{ 
    PLAYER, 
    OGRE, 
    GOBLIN, 
    SLIME, 
    SKELETON 
};

enum tileType 
{ 
    BOUND, 
    EMPTY, 
    ENEMY, 
    EXIT, 
    CHEST 
};

// Description of the Enemy class
class EnemyData
{
public:
    EnemyData()
    {
        type = randomEnemyType();
        health = GatherHealth(type);
        gold = rand() % 20;
    }

    int GatherHealth(int type)
    {
        switch (type)
        {
        case OGRE:
            return 40;
        case GOBLIN:
            return 30;
        case SKELETON:
            return 20;
        case SLIME:
            return 10;
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
    int health;
    int type;
    int gold;

    int randomEnemyType()
    {
        return rand() % 4 + 1;
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
    int posx;
    int posy;

    PlayerData()
    {
        status = true;
        health = 50;
        gold = 0;
        lv = 1;
        str = (int)(lv / 2 + 2);
        posx = -1;
        posy = -1;
    }

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
        posx = x;
        posy = y;
    }
};

// Descriptiosn of Area class
class AreaData
{
public:
    int tileName;
    bool tileStatus;

    AreaData()
    {
        tileName = -1;
        tileStatus = false;
    }

    AreaData(int Name_of_Tile, bool Status_of_Tile)
    {
        tileName = Name_of_Tile;
        tileStatus = Status_of_Tile;

    }
};

int AreaSize(int size) { return size; }

// Check for type of Area Tile
int DefineTileStatus(tileType type)
{
    switch (type)
    {
    case BOUND:
        return 0;
    case ENEMY:
        return 2;
    case EXIT:
        return 3;
    case CHEST:
        return 4;
    default:
        return 1;
    }
}



//
//  Developer func
//



// Show/Hide console window (~)
void HideShowConsole(bool& ConsoleStatus)
{
    if (ConsoleStatus == false)
    {
        ConsoleStatus = true;
    }
    else if (ConsoleStatus = true)
    {
        ConsoleStatus = false;
    }

    ShowWindow(GetConsoleWindow(), ConsoleStatus);
}
//Easy4ENCE