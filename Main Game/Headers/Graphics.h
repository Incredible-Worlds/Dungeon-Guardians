#pragma once
#include <GameModule.h>
#include <SDL.h>

namespace main_window
{
    struct basedwindow
    {
        SDL_Window* window = NULL;
        SDL_Surface* surface = NULL;
        SDL_Renderer* ren = NULL;
    };
}
namespace mainw = main_window;

namespace main_graphics
{
    struct maintextures
    {
        SDL_Texture* knight = NULL;
        SDL_Texture* world_texture = NULL;
        SDL_Texture* bound = NULL;
        SDL_Texture* chest = NULL;
        SDL_Texture* orge = NULL;
        SDL_Texture* goblin = NULL;
        SDL_Texture* skeleton = NULL;
        SDL_Texture* slime = NULL;

        SDL_Texture* inventoryBorder = NULL;
        SDL_Texture* inventoryBorder_active = NULL;
        SDL_Texture* commonSword1 = NULL;

        SDL_Texture* cat = NULL;
    };

    int init(mainw::basedwindow& MainWindow);

    int load(mainw::basedwindow& MainWindow, maintextures& WorldTexture);

    int draw(mainw::basedwindow& MainWindow,
        maintextures& WorldTexture,
        PlayerData player,
        AreaData* world,
        std::vector<InventoryData> inventory,
        std::vector<EnemyData> enemys);

    int exit(mainw::basedwindow& MainWindow, maintextures& WorldTexture);
}
namespace maing = main_graphics;