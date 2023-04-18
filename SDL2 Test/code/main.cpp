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
SDL_Renderer* ren = NULL;

int init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        return 1;
    }

    window = SDL_CreateWindow("Hello SDL World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    // Check that the window was successfully created
    if (NULL == window)
    {
        std::cout << "Could not create window: " << SDL_GetError() << endl;
        return 2;
    }

    ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Check
    if (ren == NULL) {
        cout << "Can't create renderer: " << SDL_GetError() << endl;
        return 3;
    }

    SDL_UpdateWindowSurface(window);

    return 0;
}

int draw()
{
    if (SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF) == -1)
    {
        cout << "Could not create render: " << SDL_GetError() << endl;
        return 4;
    }

    SDL_Rect rect1 = { 10, 10, 50, 50 };

    for (int i = 32; i <= WIDTH - 10; i += 64)
    {
        for (int j = 32; j <= HEIGHT - 10; j += 64)
        {
            SDL_RenderDrawPoint(ren, i, j);
        }
    }
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

int SDL_main(int argc, char* argv[])
{
    init();

    ShowWindow(GetConsoleWindow(), SW_HIDE);    // Hide console window (enable on ~)

    AreaData* world = new AreaData[4096];

    SDL_Event windowEvent;

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

        draw();

        SDL_RenderPresent(ren);
    }

    exit();

    return EXIT_SUCCESS;
}