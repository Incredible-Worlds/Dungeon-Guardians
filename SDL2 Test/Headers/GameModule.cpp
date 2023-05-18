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
                if (world[i].position.posx == position.posx + setings.width / 60
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

int PlayerData::setPos(int x, int y)
{
    position.posx = x;
    position.posy = y;

    return EXIT_SUCCESS;
}
