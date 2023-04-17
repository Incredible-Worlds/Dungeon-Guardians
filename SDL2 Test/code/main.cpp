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
const int WIDTH = 1000, HEIGHT = 800;
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

    for (int i = 10; i <= WIDTH - 10; i += 4)
    {
        for (int j = 10; j <= HEIGHT - 10; j += 4)
        {
            SDL_RenderDrawPoint(ren, i, j);
        }
    }
    return 0;
}

void check_for_close()
{
    SDL_Event windowEvent;

    int fps_time, fps_count = 0;

    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
            {
                break;
            }
            if (windowEvent.type == SDL_KEYDOWN)
            {
                cout << "Pressed key is: " << windowEvent.key.keysym.sym << endl;
            }
        }
        fps_time = time(NULL);
        fps_count++;

        draw();

        SDL_RenderPresent(ren);

        if ((time(NULL) - fps_time) != 0)
        {
            system("CLS");
            cout << endl << "Fps is: " << fps_count << endl;
            fps_time = time(NULL);
            fps_count = 0;
        }
        //Sleep(10);
    }
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

int main(int argc, char* argv[])
{
    tileType a{ tileType::EMPTY };
     bool b = true;

     AreaData world[10][10];

     for (int i = 0; i < 10; i++)
     {
         for (int j = 0; j < 10; j++)
         {
             world[i][j] = AreaData(a, b);
             cout << world[i][j].tileStatus << " ";
         }
         cout << endl;
     }

    init();

    check_for_close();

    exit();

    return EXIT_SUCCESS;
}