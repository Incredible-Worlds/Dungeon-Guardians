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

bool CnStatus = false;

int AllGameEvents(PlayerData& player, AreaData* world, vector<InventoryData>& inventory)
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

int SDL_main(int argc, char** argv)
{
    Saveload loadAll;

    mainw::basedwindow MainWindow;
    maing::maintextures WorldTexture;

    Mix_Music* mainmusic = NULL;
    AreaData* world = new AreaData[worldsize];
    SetingsData setings;

    PlayerData player;
    vector<EnemyData> enemys;

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

    vector<InventoryData> inventory;
    InventoryData temp;
    temp.item_id = CommonSword1;
    temp.is_active = true;
    temp.setDurability();
    inventory.push_back(temp);

    /// Error check
    if ((error_code = maing::init(MainWindow)) != 0)
    {
        std::cout << "Could not init: " << SDL_GetError() << endl;
        ShowWindow(GetConsoleWindow(), SW_SHOW);
        return error_code;
    }

    if ((error_code = maing::load(MainWindow, WorldTexture)) != 0)
    {
        std::cout << "Could not load files: " << SDL_GetError() << endl;
        ShowWindow(GetConsoleWindow(), SW_SHOW);
        return error_code;
    }

    mainmusic = Mix_LoadMUS("./Materials/OST/8 bit.wav");
    if (mainmusic == NULL)
    {
        return LOADERROR;
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

    if (menu_main(MainWindow.window, MainWindow.surface, MainWindow.ren, mainmusic) != 0)
    {
        PlayGame = false;
    }
       
    loadAll.LoadAll(world, player);

    /// Please be patient I have atei... autism; I LOVE TRPO
    for (;PlayGame;)
    {
        if (AllGameEvents(player, world, inventory) != EXIT_SUCCESS)
        {
            break;
        }

        CheckWorld(world, player.position);

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

        maing::draw(MainWindow, WorldTexture, player, world, inventory, enemys);
    }

    loadAll.WriteAll(world, player);
    maing::exit(MainWindow, WorldTexture);

    return EXIT_SUCCESS;
}