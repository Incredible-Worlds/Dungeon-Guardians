// Kamys, Potrox and Bell404ll developers project
//
//          @ All rights reserved
//
// Not open source version, only for course work

#include <SDL.h>
#include "../Headers/GameModule.h"

#include <iostream>

// include WorldInit
// include Fight
// include MainMenu

using namespace std;

SDL_Window* window = NULL;
SDL_Surface* surface = NULL;

SDL_Surface* knight = NULL;
SDL_Surface* world_texture = NULL;
SDL_Surface* border = NULL;
SDL_Surface* chest = NULL;
SDL_Surface* orge = NULL;
SDL_Surface* goblin = NULL;
SDL_Surface* skeleton = NULL;
SDL_Surface* slime = NULL;

AreaData* world = new AreaData[worldsize];
PlayerData player(1, 50, 0, 1, 1, 10 + 32, 10 + 32);

bool CnStatus = false;
bool FPSshowhide = false;

SDL_DisplayMode DM;
int WIDTH = 1920;
int HEIGHT = 1080;

int AllGameEvents()
{
    SDL_Event windowEvent;

    if (SDL_PollEvent(&windowEvent))
    {
        if (windowEvent.type == SDL_QUIT)
        {
            return -1;
        }
        if (windowEvent.type == SDL_KEYDOWN)
        {
            cout << "Pressed key is: " << windowEvent.key.keysym.sym << endl;
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
                    if (player.posx < worldsize - 84)
                    {
                        player.posx += 32;
                    }
                    break;
                }
                case 115:
                {
                    if (player.posy < worldsize - 84)
                    {
                        player.posy += 32;
                    }
                    break;
                }
                case 119:
                {
                    if (player.posy > 42)
                    {
                        player.posy -= 32;
                    }
                    break;
                }
                case 97:                        // Endof Movmet
                {
                    if (player.posx > 42)
                    {
                        player.posx -= 32;
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }

    return SUCSESS_EXIT;
}

int init()
{

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Could not init SDL: " << SDL_GetError() << std::endl;
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

    world_texture = SDL_LoadBMP("./Materials/Texture/123.bmp");
    if (world_texture == NULL)
    {
        return LOADERROR;
    }

    border = SDL_LoadBMP("./Materials/Texture/border.bmp");
    if (border == NULL)
    {
        return LOADERROR;
    }

    chest = SDL_LoadBMP("./Materials/Texture/chest.bmp");
    if (chest == NULL)
    {
        return LOADERROR;
    }

    orge = SDL_LoadBMP("./Materials/Texture/123.bmp");
    if (chest == NULL)
    {
        return LOADERROR;
    }

    goblin = SDL_LoadBMP("./Materials/Texture/123.bmp");
    if (chest == NULL)
    {
        return LOADERROR;
    }

    skeleton = SDL_LoadBMP("./Materials/Texture/123.bmp");
    if (chest == NULL)
    {
        return LOADERROR;
    }

    slime = SDL_LoadBMP("./Materials/Texture/123.bmp");
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
    
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));


    for (int i = 0; i < worldsize; i++)
    {
        coord.x = world[i].posx;
        coord.y = world[i].posy;
        if (world[i].tileStatus == true)
        {
            if (world[i].tileName == EMPTY && (world[i].posy > 32 && world[i].posx < worldsize - 42) 
                                           && (world[i].posy > 32 && world[i].posx > 32) 
                                           && (world[i].posy < worldsize - 42 && world[i].posx < worldsize - 42))
            {
                SDL_BlitSurface(world_texture, NULL, surface, &coord);
            }
            else
            {
                SDL_BlitSurface(border, NULL, surface, &coord);;
            }
            if (world[i].tileName == CHEST && (world[i].posy > 32 && world[i].posx < worldsize - 42)
                && (world[i].posy > 32 && world[i].posx > 32)
                && (world[i].posy < worldsize - 42 && world[i].posx < worldsize - 42))
            {
                SDL_BlitSurface(world_texture, NULL, surface, &coord);
                SDL_BlitSurface(chest, NULL, surface, &coord);
            }
            if (world[i].tileName == ENEMY && (world[i].posy > 32 && world[i].posx < worldsize - 42)
                && (world[i].posy > 32 && world[i].posx > 32)
                && (world[i].posy < worldsize - 42 && world[i].posx < worldsize - 42))
            {
                if (world[i].tileName == OGRE)
                {
                    SDL_BlitSurface(world_texture, NULL, surface, &coord);
                    SDL_BlitSurface(orge, NULL, surface, &coord);
                }
                if (world[i].tileName == GOBLIN)
                {
                    SDL_BlitSurface(world_texture, NULL, surface, &coord);
                    SDL_BlitSurface(goblin, NULL, surface, &coord);
                }
                if (world[i].tileName == SKELETON)
                {
                    SDL_BlitSurface(world_texture, NULL, surface, &coord);
                    SDL_BlitSurface(skeleton, NULL, surface, &coord);
                }
                if (world[i].tileName == SLIME)
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

int SDL_main(int argc, char** argv)
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);    // Hide console window (enable on ~)

    int error_code;
    if ((error_code = init()) != 0)
    {
        std::cout << "Could not init window: " << SDL_GetError() << endl;
        ShowWindow(GetConsoleWindow(), SW_SHOW);
        return error_code;
    }

    if ((error_code = load()) != 0)
    {
        std::cout << "Could not load files: " << SDL_GetError() << endl;
        ShowWindow(GetConsoleWindow(), SW_SHOW);
        return error_code;
    }

    int fps_count = 0, fps_time = time(NULL);

    int count = 32;

    // Two different versions of the fill world function
    for (int i = 1; i < worldsize; i++)
    {
        world[i].posx = world[i - 1].posx + 32;
        world[i].posy = world[i - 1].posy;
        world[i].tileName = EMPTY;
        world[i].tileStatus = false;

        if (i == count)
        {
            world[i].posx = 10;
            world[i].posy = world[i].posy + 32;
            count += 32;
        }
    }

    srand(time(NULL));
    for (int i = 1; i < worldsize; i++)
    {
        int countchest = rand() % 100;
        int countchest1 = rand() % 100;
        int countmob = rand() % 100;
        if (countchest == 33 and (countchest1 == 9
                                or countchest1 == 19 
                                or countchest1 == 29
                                or countchest1 == 39
                                or countchest1 == 49
                                or countchest1 == 59
                                or countchest1 == 69
                                or countchest1 == 79
                                or countchest1 == 89
                                or countchest1 == 99))
        {
            world[i].tileName = CHEST;
        }
        if (countmob == 50)
        {
            world[i].tileName = ENEMY;
            int counttype = rand() % 4 + 1;
            if (counttype == 1)
            {
                world[i].tileName = SLIME;
            }
            if (counttype == 2)
            {
                world[i].tileName = SKELETON;
            }
            if (counttype == 3)
            {
                world[i].tileName = GOBLIN;
            }
            if (counttype == 4)
            {
                world[i].tileName = OGRE;
            }
        }
    }

    menu_main(window, surface);

    while (true)
    {
        if (AllGameEvents() != EXIT_SUCCESS)
        {
            break;
        }

        // Check all status of world
        for (int i = 0; i < worldsize; i++)
        {
            if (time(NULL) - world[i].tileStatusTimer > 5)
            {
                world[i].tileStatus = false;
            }

            if ((world[i].posy == player.posy) && (world[i].posx == player.posx))
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