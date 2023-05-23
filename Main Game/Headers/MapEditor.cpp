#include "MapEditor.h"

struct textures
{
    SDL_Texture* empty = NULL;
    SDL_Texture* bound = NULL;
    SDL_Texture* chest = NULL;

} EditorTexture;

SDL_Texture* ExitButtonEditor = NULL;

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


    coord.w = editor_setings.width / 7.5;
    coord.h = editor_setings.height / 8.43;
    coord.x = (int)(editor_setings.width / 1.2) - (editor_setings.width / 15);
    coord.y = editor_setings.height - (editor_setings.width / 15) - (editor_setings.width / 96);
    SDL_RenderCopy(ren, ExitButtonEditor, NULL, &coord);

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

    temp_surface = SDL_LoadBMP("./Materials/GUI/ExitButton.bmp");
    ExitButtonEditor = SDL_CreateTextureFromSurface(ren, temp_surface);
    if (ExitButtonEditor == NULL)
    {
        return LOADERROR;
    }

    return EXIT_SUCCESS;
}

int GameEditor(SDL_Renderer* ren)
{
    SetingsData editor_setings;
    editor_setings.LoadFromFile(editor_setings);
    Saveload saveloadall;


    AreaData* editor_world = new AreaData[worldsize];
    PlayerData editor_player;
    tileType basedItem = BOUND;

    saveloadall.LoadAll(editor_world, editor_player);
    GenerateNewMap(editor_world);

    int mousex = 0, mousey = 0;

    if (GameEditorLoad(ren) != 0)
    {
        return LOADERROR;
    }

    while (true)
    {
        SDL_Event windowEvent;

        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT)
            {
                break;
            }

            if (windowEvent.type == SDL_MOUSEBUTTONDOWN)
            {
                mousex = (int)((windowEvent.button.x - 10) / 32) * 32 + 10;
                mousey = (int)((windowEvent.button.y - 10) / 32) * 32 + 10;

                if (windowEvent.button.x > editor_setings.width - (int)(editor_setings.width / 4)
                    && windowEvent.button.x <= editor_setings.width - (int)(editor_setings.width / 4) + editor_setings.width / 30)
                {
                    if (windowEvent.button.y > (int)(editor_setings.height / 5.4)
                        && windowEvent.button.y <= (int)(editor_setings.height / 5.4) + editor_setings.width / 30)
                    {
                        basedItem = EMPTY;
                    }
                    if (windowEvent.button.y > (int)(editor_setings.height / 5.4) + editor_setings.width / 30
                        && windowEvent.button.y <= (int)(editor_setings.height / 5.4) + 2 * (editor_setings.width / 30))
                    {
                        basedItem = BOUND;
                    }
                    if (windowEvent.button.y > (int)(editor_setings.height / 5.4) + 2 * (editor_setings.width / 30)
                        && windowEvent.button.y <= (int)(editor_setings.height / 5.4) + 3 * (editor_setings.width / 30))
                    {
                        basedItem = CHEST;
                    }
                }

                for (int i = 0; i < worldsize; i++)
                {
                    if (editor_world[i].position.posx == mousex
                        && editor_world[i].position.posy == mousey)
                    {
                        editor_world[i].tileName = basedItem;
                        break;
                    }
                }

                if (windowEvent.button.x > (int)(editor_setings.width / 1.2) - (editor_setings.width / 15)
                    && windowEvent.button.x < (int)(editor_setings.width / 1.2) + (editor_setings.width / 15)
                    && windowEvent.button.y > editor_setings.height - (editor_setings.width / 15) - (editor_setings.width / 96)
                    && windowEvent.button.y < editor_setings.height - (editor_setings.width / 96))
                {
                    break;
                }
            }

            GameEditorDraw(ren, editor_setings, editor_world);
        }
    }

    editor_player.position.posx = 10 + 32;
    editor_player.position.posy = 10 + 32;
    saveloadall.WriteAll(editor_world, editor_player);

    return 0;
}
