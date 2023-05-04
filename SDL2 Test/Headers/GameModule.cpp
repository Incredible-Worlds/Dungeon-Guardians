// Kamys, Potrox and Bell404ll developers project
//
//          @ All rights reserved
//
// Not open source version, only for course work

#include "GameModule.h"
#include <iostream>

int WH = GetSystemMetrics(SM_CXSCREEN);
int HT = GetSystemMetrics(SM_CYSCREEN);

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


int CollisionCheck(AreaData* world, PositionData position, directionType direction)
{
    switch (direction)
    {
        case RIGHT:
        {
            for (int i = 0; i < worldsize; i++)
            {
                if (world[i].position.posx == position.posx + WH / 60
                    && world[i].position.posy == position.posy
                    && world[i].tileName != BOUND)
                {
                    return WH / 60;
                }
            }
            break;
        }
            
        case LEFT:
        {
            for (int i = 0; i < worldsize; i++)
            {
                if (world[i].position.posx == position.posx - WH / 60
                    && world[i].position.posy == position.posy
                    && world[i].tileName != BOUND)
                {
                    return WH / 60;
                }
            }
            break;
        }
            
        case UP:
        {
            for (int i = 0; i < worldsize; i++)
            {
                if (world[i].position.posx == position.posx
                    && world[i].position.posy == position.posy - WH / 60
                    && world[i].tileName != BOUND)
                {
                    return WH / 60;
                }
            }
            break;
        }
            
        case DOWN:
        {
            for (int i = 0; i < worldsize; i++)
            {
                if (world[i].position.posx == position.posx
                    && world[i].position.posy == position.posy + WH / 60
                    && world[i].tileName != BOUND)
                {
                    return WH / 60;
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


