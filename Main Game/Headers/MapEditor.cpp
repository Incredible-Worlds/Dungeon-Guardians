#include "MapEditor.h"

struct textures
{
    SDL_Texture* empty = NULL;
    SDL_Texture* bound = NULL;
    SDL_Texture* chest = NULL;

} EditorTexture;

int GameEfitorLoad(SDL_Renderer* ren)
{
    SDL_Surface* temp_surface = SDL_LoadBMP("./Materials/Texture/stonefloor.bmp");
    EditorTexture.empty = SDL_CreateTextureFromSurface(ren, temp_surface);
    if (EditorTexture.empty == NULL)
    {
        return LOADERROR;
    }

    temp_surface = SDL_LoadBMP("./Materials/Texture/border.bmp");
    EditorTexture.bound = SDL_CreateTextureFromSurface(ren, temp_surface);
    if (EditorTexture.bound == NULL)
    {
        return LOADERROR;
    }

    temp_surface = SDL_LoadBMP("./Materials/Texture/chest.bmp");
    EditorTexture.chest = SDL_CreateTextureFromSurface(ren, temp_surface);
    if (EditorTexture.chest == NULL)
    {
        return LOADERROR;
    }

    return 0;
}

int GameEditor(SDL_Renderer* ren)
{
    SetingsData editor_setings;
    editor_setings.LoadFromFile(editor_setings);

    AreaData* editor_word = new AreaData[worldsize];
    PlayerData editor_player;

    while (true)
    {

    }

    return 0;
}
