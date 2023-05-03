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


SDL_Renderer* ren = NULL;
SDL_Texture* knight = NULL;
SDL_Texture* world_texture = NULL;
SDL_Texture* border = NULL;
SDL_Texture* chest = NULL;
SDL_Texture* orge = NULL;
SDL_Texture* goblin = NULL;
SDL_Texture* skeleton = NULL;
SDL_Texture* slime = NULL;


AreaData* world = new AreaData[worldsize];
PlayerData player(1, 50, 0, 1, 1, 42, 42);

vector<EnemyData> enemys;

bool CnStatus = false;
bool FPSshowhide = false;

int WIDTH = GetSystemMetrics(SM_CXSCREEN);
int HEIGHT = GetSystemMetrics(SM_CYSCREEN);


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
                        player.position.posx += CollisionCheck(world, player.position, RIGHT);
                    }
                    break;
                }
                case SDLK_s:
                {
                    if (player.position.posy < worldsize - 84)
                    {
                        player.position.posy += CollisionCheck(world, player.position, DOWN);
                    }
                    break;
                }
                case SDLK_w:
                {
                if (player.position.posy > 42)
                    {
                        player.position.posy -= CollisionCheck(world, player.position, UP);
                    }
                    break;
                }
                case SDLK_a:
                {
                    if (player.position.posx > 42)
                    {
                        player.position.posx -= CollisionCheck(world, player.position, LEFT);
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
    SDL_Surface* knight_temp = SDL_LoadBMP("./Materials/Texture/knight.bmp");
    knight = SDL_CreateTextureFromSurface(ren, knight_temp);
    if (knight == NULL)
    {
        return LOADERROR;
    }

    SDL_Surface* world_texture_temp = SDL_LoadBMP("./Materials/Texture/123.bmp");
    world_texture = SDL_CreateTextureFromSurface(ren, world_texture_temp);
    if (world_texture == NULL)
    {
        return LOADERROR;
    }


    SDL_Surface* border_tempf = SDL_LoadBMP("./Materials/Texture/border.bmp");
    border = SDL_CreateTextureFromSurface(ren, border_tempf);
    if (border == NULL)
    {
        return LOADERROR;
    }

    SDL_Surface* chest_temp = SDL_LoadBMP("./Materials/Texture/chest.bmp");
    chest = SDL_CreateTextureFromSurface(ren, chest_temp);
    if (chest == NULL)
    {
        return LOADERROR;
    }


    SDL_Surface* orge_temp = SDL_LoadBMP("./Materials/Texture/123.bmp");
    orge = SDL_CreateTextureFromSurface(ren, orge_temp);
    if (orge == NULL)
    {
        return LOADERROR;
    }

    SDL_Surface* goblin_temp = SDL_LoadBMP("./Materials/Texture/123.bmp");
    goblin = SDL_CreateTextureFromSurface(ren, goblin_temp);
    if (goblin == NULL)
    {
        return LOADERROR;
    }

    SDL_Surface* skeleton_temp = SDL_LoadBMP("./Materials/Texture/123.bmp");
    skeleton = SDL_CreateTextureFromSurface(ren, skeleton_temp);
    if (skeleton == NULL)
    {
        return LOADERROR;
    }

    SDL_Surface* slime_temp = SDL_LoadBMP("./Materials/Texture/123.bmp");
    slime = SDL_CreateTextureFromSurface(ren, slime_temp);
    if (slime == NULL)
    {
        return LOADERROR;
    }

    return 0;

}

int draw(PlayerData player, AreaData* world)
{
    SDL_Rect coord{};
    coord.w = WIDTH / 60;
    coord.h = HEIGHT / 33.75;

    for (int i = 0; i < worldsize; i++)
    {
        coord.x = world[i].posx;
        coord.y = world[i].posy;
        if (world[i].tileStatus == true)
        {
            if (world[i].tileName == EMPTY)
            {
                SDL_RenderCopy(ren, world_texture, NULL, &coord);
            }
            if ((coord.x + 42 | coord.y + 42) > worldsize or (coord.x - 42 | coord.y - 42) < 0)
            {
                SDL_RenderCopy(ren, border, NULL, &coord);
            }
            if (world[i].tileName == CHEST && (coord.x + 42 | coord.y + 42) < worldsize and (coord.x - 42 | coord.y - 42) > 0)
            {
                SDL_RenderCopy(ren, world_texture, NULL, &coord);
                SDL_RenderCopy(ren, chest, NULL, &coord);
            }
            if (world[i].tileName == ENEMY && (coord.x + 42 | coord.y + 42) < worldsize and (coord.x - 42 | coord.y - 42) > 0)
            {
                if (world[i].tileName == OGRE)
                {
                    SDL_RenderCopy(ren, world_texture, NULL, &coord);
                    SDL_RenderCopy(ren, orge, NULL, &coord);
                }
                if (world[i].tileName == GOBLIN)
                {
                    SDL_RenderCopy(ren, world_texture, NULL, &coord);
                    SDL_RenderCopy(ren, goblin, NULL, &coord);
                }
                if (world[i].tileName == SKELETON)
                {
                    SDL_RenderCopy(ren, world_texture, NULL, &coord);
                    SDL_RenderCopy(ren, skeleton, NULL, &coord);
                }
                if (world[i].tileName == SLIME)
                {
                    SDL_RenderCopy(ren, world_texture, NULL, &coord);
                    SDL_RenderCopy(ren, slime, NULL, &coord);
                }
            }
        }
    }

    coord.x = player.posx;
    coord.y = player.posy;
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

    int last_time = time(NULL);
    bool PlayGame = true;
    int count = 32;

    // Creating worldmap
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
        tempenemy.position.posx = 32 * 4 + 10;
        tempenemy.position.posy = 32 * 6 + 10;

        enemys.push_back(tempenemy);
    }

    world[163].tileName = BOUND;
    world[196].tileName = BOUND;
    world[194].tileName = BOUND;

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

        if (last_time != time(NULL))
        {
            for (unsigned int i = 0; i < enemys.size(); i++)
            {
                EnemyMovement(enemys[i].position, world);
            }
            last_time = time(NULL);
        }

        draw(player, world);

        //SDL_UpdateWindowSurface(window);
    }

    exit();

    return EXIT_SUCCESS;
}