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

// Show/Hide FPS
void FPSCounter(int& fps_count, int& fps_time)
{
    fps_count++;

    if ((time(NULL) - fps_time) != 0)
    {
        system("CLS");
        std::cout << std::endl << "Fps is: " << fps_count << std::endl;
        fps_time = time(NULL);
        fps_count = 0;
    }
}

int CollisionCheck(AreaData* world, PlayerData player, directionType direction)
{
    switch (direction)
    {
        case RIGHT:
        {
            for (int i = 0; i < worldsize; i++)
            {
                if (world[i].posx == player.posx + 32
                    && world[i].posy == player.posy
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
                if (world[i].posx == player.posx - 32
                    && world[i].posy == player.posy
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
                if (world[i].posx == player.posx
                    && world[i].posy == player.posy - 32
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
                if (world[i].posx == player.posx
                    && world[i].posy == player.posy + 32
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

int EnemyMovement(AreaData* world, int current_pos)
{
    srand(time(NULL));

    if (rand() % 100 > 90)
    {
        world[current_pos + 1].enemyStatus = true;
        world[current_pos + 1].enemy_type = world[current_pos].enemy_type;

        world[current_pos].enemyStatus = false;
    }
    if (rand() % 100 < 10)
    {
        world[current_pos - 1].enemyStatus = true;
        world[current_pos - 1].enemy_type = world[current_pos].enemy_type;

        world[current_pos].enemyStatus = false;
    }

    return 0;
}
