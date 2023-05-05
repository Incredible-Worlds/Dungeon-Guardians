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

using namespace std;

SDL_Window* window = NULL;
SDL_Surface* surface = NULL;

SDL_Renderer* ren = NULL;
SDL_Texture* knight = NULL;
SDL_Texture* world_texture = NULL;
SDL_Texture* bound = NULL;
SDL_Texture* chest = NULL;
SDL_Texture* orge = NULL;
SDL_Texture* goblin = NULL;
SDL_Texture* skeleton = NULL;
SDL_Texture* slime = NULL;

SDL_Texture* cat = NULL;

AreaData* world = new AreaData[worldsize];
SetingsData setings;
PlayerData player(1, 50, 0, 1, 1, 10 + (setings.width / 60), 10 + (setings.width / 60));

vector<EnemyData> enemys;

bool CnStatus = false;

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

                case SDLK_ESCAPE:                        // exit
                {
                    return -1;
                }
                case SDLK_d:                               // Movment
                {
                    player.position.posx += CollisionCheck(world, player.position, RIGHT);
                    break;
                }
                case SDLK_s:
                {
                    player.position.posy += CollisionCheck(world, player.position, DOWN);
                    break;
                }
                case SDLK_w:
                {
                    player.position.posy -= CollisionCheck(world, player.position, UP);
                    break;
                }
                case SDLK_a:
                {
                    player.position.posx -= CollisionCheck(world, player.position, LEFT);
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
        setings.width,
        setings.height,
        SDL_WINDOW_ALLOW_HIGHDPI);

    // Check that the window was successfully created
    if (window == NULL)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 2;
    }

    ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL) {
        cout << "Can't create renderer: " << SDL_GetError() << endl;
        return 3;
    }
    SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);

    surface = SDL_GetWindowSurface(window);

    return 0;
}

int load()
{
    SDL_Surface* temp_surface = SDL_LoadBMP("./Materials/Texture/knight.bmp");
    knight = SDL_CreateTextureFromSurface(ren, temp_surface);
    if (knight == NULL)
    {
        return LOADERROR;
    }

    temp_surface = SDL_LoadBMP("./Materials/Texture/123.bmp");
    world_texture = SDL_CreateTextureFromSurface(ren, temp_surface);
    if (world_texture == NULL)
    {
        return LOADERROR;
    }

    temp_surface = SDL_LoadBMP("./Materials/Texture/border.bmp");
    bound = SDL_CreateTextureFromSurface(ren, temp_surface);
    if (bound == NULL)
    {
        return LOADERROR;
    }

    temp_surface = SDL_LoadBMP("./Materials/Texture/chest.bmp");
    chest = SDL_CreateTextureFromSurface(ren, temp_surface);
    if (chest == NULL)
    {
        return LOADERROR;
    }

    temp_surface = SDL_LoadBMP("./Materials/Enemy/Orge.bmp");
    orge = SDL_CreateTextureFromSurface(ren, temp_surface);
    if (orge == NULL)
    {
        return LOADERROR;
    }

    temp_surface = SDL_LoadBMP("./Materials/Enemy/Goblin.bmp");
    goblin = SDL_CreateTextureFromSurface(ren, temp_surface);
    if (goblin == NULL)
    {
        return LOADERROR;
    }

    temp_surface = SDL_LoadBMP("./Materials/Enemy/Skeleton.bmp");
    skeleton = SDL_CreateTextureFromSurface(ren, temp_surface);
    if (skeleton == NULL)
    {
        return LOADERROR;
    }

    temp_surface = SDL_LoadBMP("./Materials/Enemy/Slime.bmp");
    slime = SDL_CreateTextureFromSurface(ren, temp_surface);
    if (slime == NULL)
    {
        return LOADERROR;
    }

    temp_surface = SDL_LoadBMP("./Materials/Texture/cat.bmp");
    cat = SDL_CreateTextureFromSurface(ren, temp_surface);
    if (cat == NULL)
    {
        return LOADERROR;
    }

    temp_surface = NULL;

    return 0;

}

int draw(PlayerData player, AreaData* world)
{
    SDL_Rect coord{};
    coord.w = setings.width;
    coord.h = setings.height;
    SDL_RenderCopy(ren, cat, NULL, &coord);


    coord.w = setings.width / 60;
    coord.h = setings.width / 60;

    for (int i = 0; i < worldsize; i++)
    {
        coord.x = world[i].position.posx;
        coord.y = world[i].position.posy;
        if (world[i].tileStatus == true)
        {
            if (world[i].tileName == EMPTY)
            {
                SDL_RenderCopy(ren, world_texture, NULL, &coord);
            }
           
            if (world[i].tileName == BOUND)
            {
                SDL_RenderCopy(ren, world_texture, NULL, &coord);
                SDL_RenderCopy(ren, bound, NULL, &coord);
            }

            if (world[i].tileName == CHEST)
            {
                SDL_RenderCopy(ren, world_texture, NULL, &coord);
                SDL_RenderCopy(ren, chest, NULL, &coord);
            }
        }
    }

    for (unsigned int i = 0; i < enemys.size(); i++)
    {
        if (enemys[i].health > 0 && enemys[i].enemyStatus == true)
        {
            coord.x = enemys[i].position.posx;
            coord.y = enemys[i].position.posy;

            switch (enemys[i].type)
            {
                case SLIME:
                {
                    SDL_RenderCopy(ren, slime, NULL, &coord);
                    break;
                }
                case ORGE:
                {
                    SDL_RenderCopy(ren, orge, NULL, &coord);
                    break;
                }
                case SKELETON:
                {
                    SDL_RenderCopy(ren, skeleton, NULL, &coord);
                    break;
                }
                case GOBLIN:
                {
                    SDL_RenderCopy(ren, goblin, NULL, &coord);
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
    SDL_RenderCopy(ren, knight, NULL, &coord);
    SDL_RenderPresent(ren);
    SDL_RenderClear(ren);

    //SDL_BlitScaled(knight, NULL, surface, &coord);

    return 0;
}

int exit()
{
    SDL_DestroyWindow(window);
    window = NULL;

    SDL_DestroyRenderer(ren);
    ren = NULL;
    SDL_Quit();
    return 0;
}

int SDL_main(int argc, char** argv)
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);    // Hide console window (enable on ~)

    int error_code;
    int last_time = time(NULL);
    bool PlayGame = true;
    int count = 32;

    // Error check
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

    // Creating worldmap
    for (int i = 1; i < worldsize; i++)
    {
        world[i].position.posx = world[i - 1].position.posx + (setings.width / 60);
        world[i].position.posy = world[i - 1].position.posy;
        world[i].tileStatus = false;

        if (i == count)
        {
            world[i].position.posx = 10;
            world[i].position.posy = world[i].position.posy + (setings.width / 60);
            count += 32;
        }

        if (world[i].position.posx == 10
            || world[i].position.posy == 10
            || world[i].position.posx == (setings.width / 60) * 31 + 10
            || world[i].position.posy == (setings.width / 60) * 31 + 10)
        {
            world[i].tileName = BOUND;
        }
        else
        {
            world[i].tileName = EMPTY;
        }
    }

    // Generate chestes
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

    // Adding enemys
    for (int i = 0; i < 1; i++)
    {
        EnemyData tempenemy;
        tempenemy.generateNew();
        tempenemy.position.posx = 10 + setings.width / 60;
        tempenemy.position.posy = 10 + setings.width / 60;

        enemys.push_back(tempenemy);
    }

    world[163].tileName = BOUND;
    world[196].tileName = BOUND;
    world[194].tileName = BOUND;

    if (menu_main(window, surface, ren) != 0)
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
            if (time(NULL) - world[i].tileStatusTimer > 15)
            {
                world[i].tileStatus = false;
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
            for (int j = 0; j < worldsize; j++)
            {
                if (world[j].tileStatus == true
                    && world[j].position.posx == enemys[i].position.posx
                    && world[j].position.posy == enemys[i].position.posy)
                {
                    enemys[i].enemyStatus = true;
                    break;
                }
                else
                {
                    enemys[i].enemyStatus = false;
                }
            }
        }

        if (last_time != time(NULL))
        {
            for (unsigned int i = 0; i < enemys.size(); i++)
            {
                EnemyMovement(enemys[i].position, world);
            }
            last_time = time(NULL);
        }

        draw(player, world);
    }

    exit();

    return EXIT_SUCCESS;
}