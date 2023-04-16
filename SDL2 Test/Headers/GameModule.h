#pragma once
#include <SDL.h>
#include <iostream>
#include <list>    
#include <iterator>
using namespace std;

// Нумерация объектов
enum characterType { PLAYER, OGRE, GOBLIN, SLIME, SKELETON };
enum tileType { BOUND, EMPTY, ENEMY, EXIT, CHEST };

// Описание структуры игрока
struct Player
{
    bool status;
    int health;
    int gold;
    int lv;
    int str; // (int)(lv / 2 + 2);
};

int AreaSize(int size) { return size; }

// Описание структуры карты
struct Area
{
    int tileName;
    bool tileStatus;

    Area()
    {
        tileName = -1;
        tileStatus = false;
    }

    Area(int Name_of_Tile, bool Status_of_Tile)
    {
        tileName = Name_of_Tile;
        tileStatus = Status_of_Tile;

    }
};

// Проверка полей поступающих данных
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

//Easy4ENCE

//class Player
//{
//public:
//    Player()
//    {
//        bool alive = true;
//        int health;
//        int gold;
//        int lv = 1;
//        int str = (int)(lv / 2 + 2);
//    }
//};


// Задание случайного типа противника
int randomEnemyType()
{
    return rand() % 4 + 1;
}

// Описание класса противников
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