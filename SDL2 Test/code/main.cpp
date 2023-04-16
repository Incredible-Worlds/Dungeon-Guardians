#include <GameModule.h>
#include <vector>
// include WorldInit
// include Fight
// include MainMenu

const int WIDTH = 800, HEIGHT = 600;
SDL_Window* window = NULL;
SDL_Surface* surface = NULL;
SDL_Renderer* ren = NULL;


int init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        return 1;
    }

    window = SDL_CreateWindow("Hello SDL World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    // Check that the window was successfully created
    if (NULL == window)
    {
        // In the case that the window could not be made...
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (ren == NULL) {
        cout << "Can't create renderer: " << SDL_GetError() << endl;
    }

    SDL_UpdateWindowSurface(window);

    return 0;
}

int draw()
{
    SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);

    SDL_Rect rect1 = { 10, 10, 50, 50 };

    for (int i = 10; i <= 800 - 10; i += 4)
    {
        for (int j = 10; j <= 600 - 10; j += 4)
        {
            SDL_RenderDrawPoint(ren, i, j);
        }
    }
    return 0;
}

void check_for_close()
{
    SDL_Event windowEvent;

    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
            {
                break;
            }
        }
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
   /* int size = 10;

    AreaSize(size);

    tileType a{ tileType::EMPTY };
    bool b = true;

    Area world[10][10];

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            world[i][j] = Area(a, b);
            cout << world[i][j].tileStatus << " ";
        }
        cout << endl;
    }*/

    init();

    draw();

    SDL_RenderPresent(ren);

    check_for_close();
    
    exit();

    return EXIT_SUCCESS;
}