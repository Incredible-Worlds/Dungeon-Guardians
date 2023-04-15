#pragma once
#include <iostream>
#include <list>    
#include <iterator>
using namespace std;

enum characterType { PLAYER, OGRE, GOBLIN, SLIME, SKELETON };
enum tileType { BOUND, EMPTY, ENEMY, EXIT, CHEST };

//Easy4ENCE

class Player
{
public:
    Player()
    {
        bool alive = true;
        int health;
        int gold;
        int lv = 1;
        int str = (int)(lv / 2 + 2);
    }
};

int randomEnemyType()
{
    return rand() % 4 + 1;
}


class Enemy
{
public:
    Enemy()
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

    void takeDamage(int str)
    {
        health -= str;
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
};

class Area
{
public:
    Area()
    {
        list<int> tile_status{};
    }

    int DefineTileStatus(int type)
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
};