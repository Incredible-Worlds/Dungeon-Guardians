// Kamys, Potrox and Bell404ll developers project
//
//          @ All rights reserved
//
// Not open source version, only for course work


#include <SDL.h>
#include <GameModule.h>
#include <iostream>


inline int AreaSize(int size) { return size; }

// Check for type of Area Tile
inline int DefineTileStatus(tileType type)
{
    switch (type)
    {
    case BOUND:
        return 0;
    case ENEMY:
        return 2;
    case EXIT:
        return 3;
    case CHEST:
        return 4;
    default:
        return 1;
    }
}

//
//  Developer func
//

// Show/Hide console window (~)
inline void HideShowConsole(bool& ConsoleStatus)
{
    if (ConsoleStatus == false)
    {
        ConsoleStatus = true;
    }
    else
    {
        ConsoleStatus = false;
    }

    ShowWindow(GetConsoleWindow(), ConsoleStatus);
}

// Show/Hide FPS
inline void FPSCounter(int& fps_count, int& fps_time)
{
    fps_count++;

    if ((time(NULL) - fps_time) != 0)
    {
        system("CLS");
        std::cout << std::endl << "Fps is: " << fps_count << std::endl;
        fps_time = time(NULL);
        fps_count = 0;
    }
}