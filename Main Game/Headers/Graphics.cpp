#pragma once
#include "Graphics.h"


int exit(basedwindow MainWindow, maintextures WorldTexture)
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