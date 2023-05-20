// Kamys, Potrox and Bell404ll developers project
//
//          @ All rights reserved
//
// Not open source version, only for course work

#include "Setings.h"
#include "GameModule.h"
#include <iostream>

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
int HideShowConsole(bool& ConsoleStatus)
{
    if (ConsoleStatus == false)
    {
        ConsoleStatus = true;
    }
    else
    {
        ConsoleStatus = false;
    }

    ShowWindow(GetConsoleWindow(), ConsoleStatus);
    return 0;
}

int CollisionCheck(AreaData* world, PositionData position, directionType direction)
{
    SetingsData setings;
    setings.LoadFromFile(setings);

    switch (direction)
    {
        case RIGHT:
        {
            for (int i = 0; i < worldsize; i++)
            {
                if (world[i].position.posx == position.posx + (int)(setings.width / 60)
                    && world[i].position.posy == position.posy
                    && world[i].tileName != BOUND)
                {
                    return (int)(setings.width / 60);
                }
            }
            break;
        }
            
        case LEFT:
        {
            for (int i = 0; i < worldsize; i++)
            {
                if (world[i].position.posx == position.posx - setings.width / 60
                    && world[i].position.posy == position.posy
                    && world[i].tileName != BOUND)
                {
                    return (int)(setings.width / 60);
                }
            }
            break;
        }
            
        case UP:
        {
            for (int i = 0; i < worldsize; i++)
            {
                if (world[i].position.posx == position.posx
                    && world[i].position.posy == position.posy - setings.width / 60
                    && world[i].tileName != BOUND)
                {
                    return (int)(setings.width / 60);
                }
            }
            break;
        }
            
        case DOWN:
        {
            for (int i = 0; i < worldsize; i++)
            {
                if (world[i].position.posx == position.posx
                    && world[i].position.posy == position.posy + setings.width / 60
                    && world[i].tileName != BOUND)
                {
                    return (int)(setings.width / 60);
                }
            }
            break;
        }
            
        default:
        {
            break;
        }
    }

    return 0;
}

int EnemyMovement(PositionData& position, AreaData* world)
{
    srand(time(NULL));
    
    switch (rand() % 4)
    {
        case 0:
        {
            position.posx += CollisionCheck(world, position, RIGHT);
            break;
        }
        case 1:
        {
            position.posx -= CollisionCheck(world, position, LEFT);
            break;
        }
        case 2:
        {
            position.posy -= CollisionCheck(world, position, UP);
            break;
        }
        case 3:
        {
            position.posy += CollisionCheck(world, position, DOWN);
            break;
        }
        default:
        {
            break;
        }
    }

    return EXIT_SUCCESS;
}

PlayerData::PlayerData()
{
    status = true;
    health = 50;
    gold = 0;
    lv = 1;
    str = (int)(lv / 2 + 2);

    position.posx = 0;
    position.posy = 0;
}

PlayerData::PlayerData(bool alive,
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

int PlayerData::setPos(int x, int y)
{
    position.posx = x;
    position.posy = y;

    return EXIT_SUCCESS;
}

PositionData::PositionData()
{
    posx = 10;
    posy = 10;
}

EnemyData::EnemyData()
{
    type = 0;
    health = 0;
    gold = 0;
    enemyStatus = true;
    position.posx = 0;
    position.posy = 0;
}

int EnemyData::GatherHealth(int type)
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

int EnemyData::takeDamage(int str)
{
    return health -= str;
}

int EnemyData::getStrength()
{
    return maxHealth() / 3;
}

void EnemyData::generateNew()
{
    type = randomEnemyType();
    health = GatherHealth(type);
    gold = rand() % 10;
}

int EnemyData::getHealth()
{
    return health;
}

bool EnemyData::isDead()
{
    return health <= 0;
}

int EnemyData::maxHealth()
{
    return GatherHealth(type);
}

int EnemyData::gatherGold()
{
    return gold;
}

int EnemyData::randomEnemyType()
{
    srand(time(NULL));

    return rand() % 4;
}

AreaData::AreaData()
{
    tileName = tileType::EMPTY;
    tileStatus = false;
    tileStatusTimer = 0;

    position.posx = 10;
    position.posy = 10;
}

AreaData::AreaData(int Name_of_Tile,
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
