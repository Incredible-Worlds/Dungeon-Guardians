#include "MapEditor.h"

struct textures
{
    SDL_Texture* empty = NULL;
    SDL_Texture* bound = NULL;
    SDL_Texture* chest = NULL;

} EditorTexture;

int GameEditorDraw(SDL_Renderer* ren, SetingsData editor_setings, AreaData* editor_world)
{
    SDL_Rect coord{};
    coord.w = coord.h = editor_setings.width / 60;

    for (int i = 0; i < worldsize; i++)
    {
        coord.x = editor_world[i].position.posx;
        coord.y = editor_world[i].position.posy;

        if (editor_world[i].tileName == EMPTY)
        {
            SDL_RenderCopy(ren, EditorTexture.empty, NULL, &coord);
        }

        if (editor_world[i].tileName == BOUND)
        {
            SDL_RenderCopy(ren, EditorTexture.empty, NULL, &coord);
            SDL_RenderCopy(ren, EditorTexture.bound, NULL, &coord);
        }

        if (editor_world[i].tileName == CHEST)
        {
            SDL_RenderCopy(ren, EditorTexture.empty, NULL, &coord);
            SDL_RenderCopy(ren, EditorTexture.chest, NULL, &coord);
        }
    }

    coord.w = coord.h = editor_setings.width / 30;
    coord.x = editor_setings.width - (int)(editor_setings.width / 4);
    coord.y = (int)(editor_setings.height / 5.4);
    SDL_RenderCopy(ren, EditorTexture.empty, NULL, &coord);

    coord.y += (int)(editor_setings.height / 16);
    SDL_RenderCopy(ren, EditorTexture.bound, NULL, &coord);

    coord.y += (int)(editor_setings.height / 16);
    SDL_RenderCopy(ren, EditorTexture.chest, NULL, &coord);

    SDL_RenderPresent(ren);
    SDL_RenderClear(ren);

    return EXIT_SUCCESS;
}

int GameEditorLoad(SDL_Renderer* ren)
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

    return EXIT_SUCCESS;
}

int GameEditor(SDL_Renderer* ren)
{
    SetingsData editor_setings;
    editor_setings.LoadFromFile(editor_setings);

    AreaData* editor_world = new AreaData[worldsize];

    GenerateNewMap(editor_world);

    PlayerData editor_player;

    if (GameEditorLoad(ren) != 0)
    {
        return LOADERROR;
    }

    while (true)
    {
        SDL_Event windowEvent;

        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT || windowEvent.key.keysym.sym == SDLK_ESCAPE)
            {
                return -1;
            }

            GameEditorDraw(ren, editor_setings, editor_world);
        }
    }

    return 0;
}