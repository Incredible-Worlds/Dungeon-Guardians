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