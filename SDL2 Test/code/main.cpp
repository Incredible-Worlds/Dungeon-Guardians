#include <GameModule.h>
#include <vector>
// include WorldInit
// include Fight
// include MainMenu

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char* argv[])
{
    int size = 10;

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
    }
    


    

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("Hello SDL World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    // Check that the window was successfully created
    if (NULL == window)
    {
        // In the case that the window could not be made...
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

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

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}