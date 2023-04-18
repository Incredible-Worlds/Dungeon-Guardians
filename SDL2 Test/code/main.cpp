// Kamys, Potrox and Bell404ll developers project
//
//          @ All rights reserved
//
// Not open source version, only for course work

#include <SDL.h>
#include <GameModule.h>
#include <vector>
#include <Windows.h>
#include <iostream>

// include WorldInit
// include Fight
// include MainMenu

using namespace std;

const int WIDTH = 1024, HEIGHT = 768;
SDL_Window* window = NULL;
SDL_Surface* surface = NULL;
SDL_Surface* knight = NULL;

int init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        return 1;
    }

    window = SDL_CreateWindow("Hello SDL World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    // Check that the window was successfully created
    if (window == NULL)
    {
        std::cout << "Could not create window: " << SDL_GetError() << endl;
        return 2;
    }

    surface = SDL_GetWindowSurface(window);

    return 0;
}

int load()
{
    knight = SDL_LoadBMP("../SDL2 Test/Materials/Texture/knight.bmp");
    if (knight == NULL)
    {
        return 3;
    }
    return 0;
    
}

int draw(PlayerData player)
{
    //function for draw in SDL
    /*if (SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF) == -1)
    {
        cout << "Could not create render: " << SDL_GetError() << endl;
        return 4;
    }

    SDL_Rect rect1 = { 10, 10, 50, 50 };*/

    SDL_Rect coord;
    coord.x = player.posx;
    coord.y = player.posy;
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
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
    if (init() != 0)
    {
        return -1;
    }

    if (load() == 3)
    {
        return -1;
    }

    ShowWindow(GetConsoleWindow(), SW_HIDE);    // Hide console window (enable on ~)

    AreaData* world = new AreaData[4096];

    SDL_Event windowEvent;

    PlayerData player(1, 50, 0, 1, 1, 0, 1);


    bool CnStatus = false, FPSshowhide = false;
    int fps_count = 0, fps_time = time(NULL);

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

                }
                case 100:
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
                case 97:
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

        if (FPSshowhide)
        {
            FPSCounter(fps_count, fps_time);
        }

        draw(player);

        SDL_UpdateWindowSurface(window);
    }

    exit();

    return EXIT_SUCCESS;
}