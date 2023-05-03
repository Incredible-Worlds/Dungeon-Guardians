// Kamys, Potrox and Bell404ll developers project
//
//          @ All rights reserved
//
// Open source version, only for course work

#include <SDL.h>
#include "../Headers/GameModule.h"

#include <vector>
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

vector<EnemyData> enemys;

bool CnStatus = false;
bool FPSshowhide = false;

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

                case SDLK_ESCAPE:                        // exit
                {
                    return -1;
                }

                case SDLK_d:                               // Movment
                {
                    if (player.position.posx < worldsize - 84)
                    {
                        player.position.posx += CollisionCheck(world, player, RIGHT);
                    }
                    break;
                }
                case SDLK_s:
                {
                    if (player.position.posy < worldsize - 84)
                    {
                        player.position.posy += CollisionCheck(world, player, DOWN);
                    }
                    break;
                }
                case SDLK_w:
                {
                    if (player.position.posy > 42)
                    {
                        player.position.posy -= CollisionCheck(world, player, UP);
                    }
                    break;
                }
                case SDLK_a:                        
                {
                    if (player.position.posx > 42)
                    {
                        player.position.posx -= CollisionCheck(world, player, LEFT);
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

    return EXIT_SUCCESS;
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

    orge = SDL_LoadBMP("./Materials/Enemy/Orge.bmp");
    if (chest == NULL)
    {
        return LOADERROR;
    }

    goblin = SDL_LoadBMP("./Materials/Enemy/Goblin.bmp");
    if (chest == NULL)
    {
        return LOADERROR;
    }

    skeleton = SDL_LoadBMP("./Materials/Enemy/Skeleton.bmp");
    if (chest == NULL)
    {
        return LOADERROR;
    }

    slime = SDL_LoadBMP("./Materials/Enemy/Slime.bmp");
    if (chest == NULL)
    {
        return LOADERROR;
    }

    return 0;
    
}

int draw(PlayerData player, AreaData* world)
{
    SDL_Rect coord{};

    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));

    // Map render
    for (int i = 0; i < worldsize; i++)
    {
        coord.x = world[i].position.posx;
        coord.y = world[i].position.posy;
        if (world[i].tileStatus == true)
        {
            if (world[i].tileName == EMPTY)
            {
                SDL_BlitSurface(world_texture, NULL, surface, &coord);
            }

            if (world[i].tileName == CHEST && (world[i].position.posy > 32 && world[i].position.posx < worldsize - 42)
                && (world[i].position.posy > 32 && world[i].position.posx > 32)
                && (world[i].position.posy < worldsize - 42 && world[i].position.posx < worldsize - 42))
            {
                SDL_BlitSurface(world_texture, NULL, surface, &coord);
                SDL_BlitSurface(chest, NULL, surface, &coord);
            }
        }
    }

    for (unsigned int i = 0; i < enemys.size(); i++)
    {
        if (enemys[i].health > 0)
        {
            coord.x = enemys[i].position.posx;
            coord.y = enemys[i].position.posy;

            switch (enemys[i].type)
            {
                case SLIME:
                {
                    SDL_BlitSurface(world_texture, NULL, surface, &coord);
                    SDL_BlitSurface(slime, NULL, surface, &coord);
                    break;
                }
                case SKELETON:
                {
                    SDL_BlitSurface(world_texture, NULL, surface, &coord);
                    SDL_BlitSurface(skeleton, NULL, surface, &coord);
                    break;
                }
                case ORGE:
                {
                    SDL_BlitSurface(world_texture, NULL, surface, &coord);
                    SDL_BlitSurface(orge, NULL, surface, &coord);
                    break;
                }
                case GOBLIN:
                {
                    SDL_BlitSurface(world_texture, NULL, surface, &coord);
                    SDL_BlitSurface(goblin, NULL, surface, &coord);
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }

    coord.x = player.position.posx;
    coord.y = player.position.posy;

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

    int fps_time = time(NULL);
    bool PlayGame = true;
    int count = 32;

    for (int i = 1; i < worldsize; i++)
    {
        world[i].position.posx = world[i - 1].position.posx + 32;
        world[i].position.posy = world[i - 1].position.posy;
        world[i].tileName = EMPTY;
        world[i].tileStatus = true;

        if (i == count)
        {
            world[i].position.posx = 10;
            world[i].position.posy = world[i].position.posy + 32;
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
    }

    for (int i = 0; i < 1; i++)
    {
        EnemyData tempenemy;
        tempenemy.generateNew();
        tempenemy.position.posx = 32 * 4 + 10;
        tempenemy.position.posy = 32 * 6 + 10;

        enemys.push_back(tempenemy);
    }

    if (menu_main(window, surface) != 0)
    {
        PlayGame = false;
    }

    while (PlayGame)
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
                world[i].tileStatus = true;
            }

            if ((world[i].position.posy == player.position.posy) 
                && (world[i].position.posx == player.position.posx))
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

        for (unsigned int i = 0; i < enemys.size(); i++)
        {
            EnemyMovement(enemys[i].position.posx, enemys[i].position.posy, world);
        }

        draw(player, world);
        SDL_UpdateWindowSurface(window);
    }

    exit();

    return EXIT_SUCCESS;
}