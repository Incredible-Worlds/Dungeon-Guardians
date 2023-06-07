// Kamys, Potrox and Bell404ll developers project
//
//          @ All rights reserved
//
// Open source version, only for course work

#include <SDL.h>
#include <SDL_mixer.h>

#include <GameModule.h>
#include <Graphics.h>

#include <vector>
#include <iostream>

using namespace std;

basedwindow MainWindow;
maintextures WorldTexture;


Mix_Music* mainmusic = NULL;


AreaData* world = new AreaData[worldsize];
SetingsData setings;

PlayerData player;

vector<EnemyData> enemys;

bool CnStatus = false;

int AllGameEvents(vector<InventoryData>& inventory)
{
    SDL_Event windowEvent;

    if (SDL_PollEvent(&windowEvent))
    {
        if (windowEvent.type == SDL_QUIT)
        {
            return -1;
        }
        if (windowEvent.type == SDL_KEYDOWN)
        {
            cout << "Pressed key is: " << windowEvent.key.keysym.sym << endl;
            switch (windowEvent.key.keysym.sym)
            {
                case 96:                        // Show or hide console
                {
                    HideShowConsole(CnStatus);
                    break;
                }

                case SDLK_ESCAPE:                        // exit
                {
                    return -1;
                }
                case SDLK_d:                               // Movment
                {
                    player.position.posx += CollisionCheck(world, player.position, RIGHT);
                    break;
                }
                case SDLK_s:
                {
                    player.position.posy += CollisionCheck(world, player.position, DOWN);
                    break;
                }
                case SDLK_w:
                {
                    player.position.posy -= CollisionCheck(world, player.position, UP);
                    break;
                }
                case SDLK_a:
                {
                    player.position.posx -= CollisionCheck(world, player.position, LEFT);
                    break;
                }
                case 32:
                {
                    inventory[0].CheckChests(world, player.position, inventory);
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }

    return EXIT_SUCCESS;
}

int init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING || SDL_INIT_AUDIO) != 0)
    {
        std::cout << "Could not init SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    MainWindow.window = SDL_CreateWindow("Dungeon Guardian",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        setings.width,
        setings.height,
        SDL_WINDOW_ALLOW_HIGHDPI);

    // Check that the window was successfully created
    if (MainWindow.window == NULL)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 2;
    }

    MainWindow.ren = SDL_CreateRenderer(MainWindow.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (MainWindow.ren == NULL) {
        cout << "Can't create renderer: " << SDL_GetError() << endl;
        return 3;
    }
    SDL_SetRenderDrawColor(MainWindow.ren, 0xFF, 0xFF, 0xFF, 0xFF);

    MainWindow.surface = SDL_GetWindowSurface(MainWindow.window);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    return 0;
}

int load()  
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

    mainmusic = Mix_LoadMUS("./Materials/OST/8 bit.wav");
    if (mainmusic == NULL)
    {
        return LOADERROR;
    }

    return 0;

}

int draw(PlayerData player, AreaData* world, vector<InventoryData> inventory)
{
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

int SDL_main(int argc, char** argv)
{
    //setings.width = 1920;
    //setings.height = 1080;
    //setings.WriteToFile(setings);               // Write to setings.data
    setings.LoadFromFile(setings);              // Load from setings.data

    player.setPos(10 + (setings.width / 60) * 4, 
                  10 + (setings.width / 60) * 4);

    ShowWindow(GetConsoleWindow(), SW_HIDE);    /// Hide console window (enable on ~)

    int error_code;
    int last_time = time(NULL);
    bool PlayGame = true;

    Saveload loadAll;

    vector<InventoryData> inventory;
    InventoryData temp;
    temp.item_id = CommonSword1;
    temp.is_active = true;
    temp.setDurability();
    inventory.push_back(temp);

    /// Error check
    if ((error_code = init()) != 0)
    {
        std::cout << "Could not init: " << SDL_GetError() << endl;
        ShowWindow(GetConsoleWindow(), SW_SHOW);
        return error_code;
    }

    if ((error_code = load()) != 0)
    {
        std::cout << "Could not load files: " << SDL_GetError() << endl;
        ShowWindow(GetConsoleWindow(), SW_SHOW);
        return error_code;
    }

    /// Adding enemys
    for (int i = 0; i < 1; i++)
    {
        EnemyData tempenemy;
        tempenemy.generateNew();
        tempenemy.position.posx = 10 + setings.width / 60;
        tempenemy.position.posy = 10 * (setings.width / 60) + 10;
        enemys.push_back(tempenemy);
    }

    //EnemyData* enemys_arr = new EnemyData[enemys.size()];
    //for (int i = 0; i < (int)enemys.size(); i++)
    //{
    //    enemys_arr[i] = enemys[i];
    //}

    if (menu_main(MainWindow.window, MainWindow.surface, MainWindow.ren, mainmusic) != 0)
    {
        PlayGame = false;
    }
       
    loadAll.LoadAll(world, player);

    /// Please be patient I have atei... autism; I LOVE TRPO
    for (;PlayGame;)
    {
        if (AllGameEvents(inventory) != EXIT_SUCCESS)
        {
            break;
        }

        CheackWorld(world, player.position);

        for (int i = 0; i < (int)enemys.size(); i++)
        {
            for (int j = 0; j < worldsize; j++)
            {
                if (world[j].tileStatus == true
                    && world[j].position.posx == enemys[i].position.posx
                    && world[j].position.posy == enemys[i].position.posy)
                {
                    enemys[i].enemyStatus = true;
                    break;
                }
                else
                {
                    enemys[i].enemyStatus = false;
                }
            }
        }

        if (last_time != time(NULL))
        {
            for (int i = 0; i < (int)enemys.size(); i++)
            {
                EnemyMovement_AI(world, enemys[i].position, player.position);
            }
            last_time = time(NULL);
        }

        draw(player, world, inventory);
    }

    loadAll.WriteAll(world, player);
    exit(MainWindow, WorldTexture);

    return EXIT_SUCCESS;
}