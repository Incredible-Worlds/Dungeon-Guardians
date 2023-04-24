// Kamys, Potrox and Bell404ll developers project
//
//          @ All rights reserved
//
// Not open source version, only for course work

#define LOADERROR 3

#include <SDL.h>
#include "../Headers/GameModule.h"
#include <iostream>


const int WIDTH = 1920, HEIGHT = 1080;
const int worldsize = 1024;

SDL_Window* window = NULL;
SDL_Surface* surface = NULL;

SDL_Surface* knight = NULL;
SDL_Surface* world_texture = NULL;
SDL_Surface* chest = NULL;
SDL_Surface* orge = NULL;
SDL_Surface* goblin = NULL;
SDL_Surface* skeleton = NULL;
SDL_Surface* slime = NULL;

int init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Could not init SDL: " << SDL_GetError() << std :: endl;
        return 1;
    }


    window = SDL_CreateWindow("Dungeon Guardian", 
                                SDL_WINDOWPOS_UNDEFINED, 
                                SDL_WINDOWPOS_UNDEFINED, 
                                WIDTH, 
                                HEIGHT, 
                                SDL_WINDOW_ALLOW_HIGHDPI);

    // Check that the window was successfully created
    if (window == NULL)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std :: endl;
        return 2;
    }

    surface = SDL_GetWindowSurface(window);

    return 0;
}

int load()
{
    knight = SDL_LoadBMP("./Materials/Texture/knight.bmp");
    if (knight == NULL)
    {
        return LOADERROR;
    }

    world_texture = SDL_LoadBMP("./Materials/Texture/Stonefloor.bmp");
    if (world_texture == NULL)
    {
        return LOADERROR;
    }

    chest = SDL_LoadBMP("./Materials/Texture/Goblin.bmp");
    if (chest == NULL)
    {
        return LOADERROR;
    }

    orge = SDL_LoadBMP("./Materials/Texture/123.bmp");
    if (chest == NULL)
    {
        return LOADERROR;
    }

    goblin = SDL_LoadBMP("./Materials/Texture/Goblin.bmp");
    if (chest == NULL)
    {
        return LOADERROR;
    }

    skeleton = SDL_LoadBMP("./Materials/Texture/123.bmp");
    if (chest == NULL)
    {
        return LOADERROR;
    }

    slime = SDL_LoadBMP("./Materials/Texture/Slime.bmp");
    if (chest == NULL)
    {
        return LOADERROR;
    }

    return 0;
    
}

int draw(PlayerData player, AreaData* world)
{
    //function for draw in SDL
    /*if (SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF) == -1)
    {
        cout << "Could not create render: " << SDL_GetError() << endl;
        return 4;
    }

    SDL_Rect rect1 = { 10, 10, 50, 50 };*/

    SDL_Rect coord{};

    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 40, 40, 40));

    for (int i = 0; i < worldsize; i++)
    {
        coord.x = world[i].posx;
        coord.y = world[i].posy;
        if (world[i].tileStatus == true)
        {
            if (world[i].tileName == tileType::EMPTY)
            {
                SDL_BlitSurface(world_texture, NULL, surface, &coord);
            }
            if (world[i].tileName == tileType::CHEST)
            {
                SDL_BlitSurface(world_texture, NULL, surface, &coord);
                SDL_BlitSurface(chest, NULL, surface, &coord);
            }

            // fix bound texture
            if (world[i].tileName == tileType::BOUND)
            {
                SDL_BlitSurface(slime, NULL, surface, &coord);
            }
            if (world[i].enemyStatus ==true)
            {
                if (world[i].enemy_type.type == characterType::OGRE)
                {
                    SDL_BlitSurface(world_texture, NULL, surface, &coord);
                    SDL_BlitSurface(orge, NULL, surface, &coord);
                }
                if (world[i].enemy_type.type == characterType::GOBLIN)
                {
                    SDL_BlitSurface(world_texture, NULL, surface, &coord);
                    SDL_BlitSurface(goblin, NULL, surface, &coord);
                }
                if (world[i].enemy_type.type == characterType::SKELETON)
                {
                    SDL_BlitSurface(world_texture, NULL, surface, &coord);
                    SDL_BlitSurface(skeleton, NULL, surface, &coord);
                }
                if (world[i].enemy_type.type == characterType::SLIME)
                {
                    SDL_BlitSurface(world_texture, NULL, surface, &coord);
                    SDL_BlitSurface(slime, NULL, surface, &coord);
                }
            }
        }
    }

    coord.x = player.posx;
    coord.y = player.posy;

    SDL_BlitSurface(knight, NULL, surface, &coord);

    return 0;
}

int exit()
{
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
    return 0;
}

int SDL_main(int argc, char* argv[])
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);    // Hide console window (enable on ~)

    int error_code;
    if ((error_code = init()) != 0)
    {
        std::cout << "Could not init window: " << SDL_GetError() << std :: endl;
        ShowWindow(GetConsoleWindow(), SW_SHOW);
        return error_code;
    }

    if ((error_code = load()) != 0)
    {
        std::cout << "Could not load files: " << SDL_GetError() << std :: endl;
        ShowWindow(GetConsoleWindow(), SW_SHOW);
        return error_code;
    }

    AreaData* world = new AreaData[worldsize];
    PlayerData player(1, 50, 0, 1, 1, 10, 10);

    EnemyData randenemy;

    SDL_Event windowEvent;
    bool CnStatus = false, FPSshowhide = false;
    int fps_count = 0, fps_time = time(NULL);

    // Two different versions of the fill world function
    for (int i = 1, count = 32; i < worldsize; i++)
    {
        world[i].posx = world[i - 1].posx + 32;
        world[i].posy = world[i - 1].posy;
        world[i].tileName = tileType::EMPTY;
        world[i].tileStatus = false;

        if (i == count)
        {
            world[i].posx = 10;
            world[i].posy = world[i].posy + 32;
            count += 32;
        }
    }

    world[rand() % 500].tileName = tileType::CHEST;
    world[rand() % 620 - 120].tileName = tileType::CHEST;

    EnemyData enemy_rand_1;
    enemy_rand_1.generateNew();

    world[rand() % 300 + 200].enemy_type = enemy_rand_1;
    world[rand() % 300 + 200].enemyStatus = true;
    
    world[56].tileName = tileType::BOUND;

    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT)
            {
                break;
            }
            if (windowEvent.type == SDL_KEYDOWN)
            {
                std :: cout << "Pressed key is: " << windowEvent.key.keysym.sym << std :: endl;

                if (windowEvent.key.keysym.sym == 27)
                {
                    break;
                }

                switch (windowEvent.key.keysym.sym)
                {
                    case 96:                        // Show or hide console
                    {
                        HideShowConsole(CnStatus);
                        break;
                    }
                    case 9:                         // Show or hide FPS
                    {
                        if (!FPSshowhide)
                        {
                            FPSshowhide = true;
                        }
                        else
                        {
                            FPSshowhide = false;
                            system("CLS");
                        }
                        break;
                    }
                    case 100:                       // Movment
                    {
                        player.posx += 32;

                        break;
                    }
                    case 115:
                    {
                        player.posy += 32;

                        break;
                    }
                    case 119:
                    {
                        player.posy -= 32;

                        break;
                    }
                    case 97:                        // Endof Movmet
                    {
                        player.posx -= 32;

                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
        }

        // Check all status of world
        for (int i = 0; i < worldsize; i++)
        {
            if (time(NULL) - world[i].tileStatusTimer > 15)
            {
                world[i].tileStatus = false;
            }

            if ((world[i].posy == player.posy)
                && (world[i].posx == player.posx))
            {
                for (int j = i - 1; j < i + 2; j++)
                {
                    world[j].tileStatus = true;

                    world[j].tileStatusTimer = time(NULL);
                }
                world[i - (int)sqrt(worldsize)].tileStatus = true;
                world[i - (int)sqrt(worldsize)].tileStatusTimer = time(NULL);

                world[i + (int)sqrt(worldsize)].tileStatus = true;
                world[i + (int)sqrt(worldsize)].tileStatusTimer = time(NULL);
            }

            if ((world[i].tileName == tileType::BOUND)
                && ((world[i].posy == player.posy)
                    && (world[i].posx == player.posx)))
            {

            }
        }


        if (FPSshowhide)
        {
            FPSCounter(fps_count, fps_time);
        }

        draw(player, world);

        SDL_UpdateWindowSurface(window);
    }

    exit();

    return EXIT_SUCCESS;
}