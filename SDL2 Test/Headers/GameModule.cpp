// Kamys, Potrox and Bell404ll developers project
//
//          @ All rights reserved
//
// Not open source version, only for course work

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
void HideShowConsole(bool& ConsoleStatus)
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
}


int CollisionCheck(AreaData* world, PlayerData player, directionType direction)
{
    switch (direction)
    {
        case RIGHT:
        {
            for (int i = 0; i < worldsize; i++)
            {
                if (world[i].position.posx == player.position.posx + 32
                    && world[i].position.posy == player.position.posy
                    && world[i].tileName != BOUND)
                {
                    return 32;
                }
            }
            break;
        }
            
        case LEFT:
        {
            for (int i = 0; i < worldsize; i++)
            {
                if (world[i].position.posx == player.position.posx - 32
                    && world[i].position.posy == player.position.posy
                    && world[i].tileName != BOUND)
                {
                    return 32;
                }
            }
            break;
        }
            
        case UP:
        {
            for (int i = 0; i < worldsize; i++)
            {
                if (world[i].position.posx == player.position.posx
                    && world[i].position.posy == player.position.posy - 32
                    && world[i].tileName != BOUND)
                {
                    return 32;
                }
            }
            break;
        }
            
        case DOWN:
        {
            for (int i = 0; i < worldsize; i++)
            {
                if (world[i].position.posx == player.position.posx
                    && world[i].position.posy == player.position.posy + 32
                    && world[i].tileName != BOUND)
                {
                    return 32;
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



// VIP create func to init W and H of screen
int CurrentWhandHs(SDL_DisplayMode& DispMode, int& Width, int& Height)
{
    SDL_GetDesktopDisplayMode(0, &DispMode);

    return EXIT_SUCCESS;
}

int EnemyMovement(int& posx, int& posy, AreaData* world)
{


    return EXIT_SUCCESS;
}


