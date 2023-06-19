#pragma once
#include "Graphics.h"


int main_graphics::init(mainw::basedwindow &MainWindow)
{
    SetingsData settings;
    settings.LoadFromFile(settings);
    if (SDL_Init(SDL_INIT_EVERYTHING || SDL_INIT_AUDIO) != 0)
    {
        return 1;
    }

    MainWindow.window = SDL_CreateWindow("Dungeon Guardian",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        settings.width,
        settings.height,
        SDL_WINDOW_ALLOW_HIGHDPI);

    // Check that the window was successfully created
    if (MainWindow.window == NULL)
    {
        return 2;
    }

    MainWindow.ren = SDL_CreateRenderer(MainWindow.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (MainWindow.ren == NULL) {
        return 3;
    }
    SDL_SetRenderDrawColor(MainWindow.ren, 0xFF, 0xFF, 0xFF, 0xFF);

    MainWindow.surface = SDL_GetWindowSurface(MainWindow.window);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    return 0;
}

int main_graphics::load(mainw::basedwindow& MainWindow, maintextures& WorldTexture)
{
    SDL_Surface* temp_surface = SDL_LoadBMP("./Materials/Texture/knight.bmp");
    WorldTexture.knight = SDL_CreateTextureFromSurface(MainWindow.ren, temp_surface);
    if (WorldTexture.knight == NULL)
    {
        return LOADERROR;
    }

    temp_surface = SDL_LoadBMP("./Materials/Texture/stonefloor.bmp");
    WorldTexture.world_texture = SDL_CreateTextureFromSurface(MainWindow.ren, temp_surface);
    if (WorldTexture.world_texture == NULL)
    {
        return LOADERROR;
    }

    temp_surface = SDL_LoadBMP("./Materials/Texture/border.bmp");
    WorldTexture.bound = SDL_CreateTextureFromSurface(MainWindow.ren, temp_surface);
    if (WorldTexture.bound == NULL)
    {
        return LOADERROR;
    }

    temp_surface = SDL_LoadBMP("./Materials/Texture/chest.bmp");
    WorldTexture.chest = SDL_CreateTextureFromSurface(MainWindow.ren, temp_surface);
    if (WorldTexture.chest == NULL)
    {
        return LOADERROR;
    }

    temp_surface = SDL_LoadBMP("./Materials/Enemy/Orge.bmp");
    WorldTexture.orge = SDL_CreateTextureFromSurface(MainWindow.ren, temp_surface);
    if (WorldTexture.orge == NULL)
    {
        return LOADERROR;
    }

    temp_surface = SDL_LoadBMP("./Materials/Enemy/Goblin.bmp");
    WorldTexture.goblin = SDL_CreateTextureFromSurface(MainWindow.ren, temp_surface);
    if (WorldTexture.goblin == NULL)
    {
        return LOADERROR;
    }

    temp_surface = SDL_LoadBMP("./Materials/Enemy/Skeleton.bmp");
    WorldTexture.skeleton = SDL_CreateTextureFromSurface(MainWindow.ren, temp_surface);
    if (WorldTexture.skeleton == NULL)
    {
        return LOADERROR;
    }

    temp_surface = SDL_LoadBMP("./Materials/Enemy/Slime.bmp");
    WorldTexture.slime = SDL_CreateTextureFromSurface(MainWindow.ren, temp_surface);
    if (WorldTexture.slime == NULL)
    {
        return LOADERROR;
    }

    temp_surface = SDL_LoadBMP("./Materials/GUI/Background.bmp");
    WorldTexture.cat = SDL_CreateTextureFromSurface(MainWindow.ren, temp_surface);
    if (WorldTexture.cat == NULL)
    {
        return LOADERROR;
    }

    temp_surface = SDL_LoadBMP("./Materials/GUI/InventoryBorder.bmp");
    WorldTexture.inventoryBorder = SDL_CreateTextureFromSurface(MainWindow.ren, temp_surface);
    if (WorldTexture.inventoryBorder == NULL)
    {
        return LOADERROR;
    }

    temp_surface = SDL_LoadBMP("./Materials/GUI/InventoryBorder_active.bmp");
    WorldTexture.inventoryBorder_active = SDL_CreateTextureFromSurface(MainWindow.ren, temp_surface);
    if (WorldTexture.inventoryBorder_active == NULL)
    {
        return LOADERROR;
    }

    temp_surface = SDL_LoadBMP("./Materials/GUI/CommonSword1.bmp");
    WorldTexture.commonSword1 = SDL_CreateTextureFromSurface(MainWindow.ren, temp_surface);
    if (WorldTexture.commonSword1 == NULL)
    {
        return LOADERROR;
    }

    temp_surface = NULL;

    return 0;
}

int main_graphics::draw(mainw::basedwindow& MainWindow, maintextures& WorldTexture, PlayerData player, AreaData* world, std::vector<InventoryData> inventory, std::vector<EnemyData> enemys)
{
    SetingsData setings;
    setings.LoadFromFile(setings);

    SDL_Rect coord{};
    coord.w = setings.width;
    coord.h = setings.height;
    SDL_RenderCopy(MainWindow.ren, WorldTexture.cat, NULL, &coord);

    coord.w = coord.h = setings.width / 60;

    // Rendering world
    for (int i = 0; i < worldsize; i++)
    {
        coord.x = world[i].position.posx;
        coord.y = world[i].position.posy;
        if (world[i].tileStatus == true)
        {
            if (world[i].tileName == EMPTY)
            {
                SDL_RenderCopy(MainWindow.ren, WorldTexture.world_texture, NULL, &coord);
            }

            if (world[i].tileName == BOUND)
            {
                SDL_RenderCopy(MainWindow.ren, WorldTexture.world_texture, NULL, &coord);
                SDL_RenderCopy(MainWindow.ren, WorldTexture.bound, NULL, &coord);
            }

            if (world[i].tileName == CHEST)
            {
                SDL_RenderCopy(MainWindow.ren, WorldTexture.world_texture, NULL, &coord);
                SDL_RenderCopy(MainWindow.ren, WorldTexture.chest, NULL, &coord);
            }
        }
    }

    // Rendering Enemys
    for (int i = 0; i < (int)enemys.size(); i++)
    {
        if (enemys[i].health > 0 && enemys[i].enemyStatus == true)
        {
            coord.x = enemys[i].position.posx;
            coord.y = enemys[i].position.posy;

            switch (enemys[i].type)
            {
            case SLIME:
            {
                SDL_RenderCopy(MainWindow.ren, WorldTexture.slime, NULL, &coord);
                break;
            }
            case ORGE:
            {
                SDL_RenderCopy(MainWindow.ren, WorldTexture.orge, NULL, &coord);
                break;
            }
            case SKELETON:
            {
                SDL_RenderCopy(MainWindow.ren, WorldTexture.skeleton, NULL, &coord);
                break;
            }
            case GOBLIN:
            {
                SDL_RenderCopy(MainWindow.ren, WorldTexture.goblin, NULL, &coord);
                break;
            }
            default:
            {
                break;
            }
            }
        }
    }

    SDL_Rect SetPeace{};
    // Rendering GUI
    for (int i = 0; i < (int)inventory.size(); i++)
    {
        SetPeace.w = SetPeace.h = 44;
        switch (inventory[i].item_id)
        {
        case CommonSword1:
        {
            coord.x = (int)(setings.width / 1.67) + (i * (int)(setings.width / 20)) + 15;
            coord.y = setings.height - (int)setings.height / 8.4375 + 15;
            coord.w = coord.h = (int)setings.width / 29;
            SDL_RenderCopy(MainWindow.ren, WorldTexture.commonSword1, &SetPeace, &coord);
            break;
        }
        case HealFlask:
        {
            coord.x = (int)(setings.width / 1.67) + (i * (int)(setings.width / 20)) + 15;
            coord.y = setings.height - (int)setings.height / 8.4375 + 15;
            coord.w = coord.h = (int)setings.width / 29;
            SDL_RenderCopy(MainWindow.ren, WorldTexture.slime, &SetPeace, &coord);
            break;
        }
        }

        SetPeace.w = SetPeace.h = 64;

        coord.x = (int)(setings.width / 1.67) + (i * (int)(setings.width / 20));
        coord.y = setings.height - (int)setings.height / 8.4375;
        coord.w = coord.h = (int)setings.width / 20;

        SDL_RenderCopy(MainWindow.ren, WorldTexture.inventoryBorder, &SetPeace, &coord);

        if (inventory[i].is_active == true)
        {
            SDL_RenderCopy(MainWindow.ren, WorldTexture.inventoryBorder_active, &SetPeace, &coord);
        }
    }

    coord.w = coord.h = setings.width / 60;

    coord.x = player.position.posx;
    coord.y = player.position.posy;
    SDL_RenderCopy(MainWindow.ren, WorldTexture.knight, NULL, &coord);
    SDL_RenderPresent(MainWindow.ren);
    SDL_RenderClear(MainWindow.ren);

    return 0;
}

int main_graphics::exit(mainw::basedwindow &MainWindow, maintextures &WorldTexture)
{
    SDL_DestroyWindow(MainWindow.window);
    MainWindow.window = NULL;

    WorldTexture.knight = NULL;
    WorldTexture.world_texture = NULL;
    WorldTexture.bound = NULL;
    WorldTexture.chest = NULL;
    WorldTexture.orge = NULL;
    WorldTexture.goblin = NULL;
    WorldTexture.skeleton = NULL;
    WorldTexture.slime = NULL;
    WorldTexture.cat = NULL;

    SDL_DestroyRenderer(MainWindow.ren);
    MainWindow.ren = NULL;
    SDL_Quit();
    return 0;
}