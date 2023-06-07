#pragma once
#include <GameModule.h>
#include <SDL.h>

struct basedwindow
{
    SDL_Window* window = NULL;
    SDL_Surface* surface = NULL;
    SDL_Renderer* ren = NULL;
};

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

int exit(basedwindow MainWindow, maintextures WorldTexture);