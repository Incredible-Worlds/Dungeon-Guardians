// Kamys, Potrox and Bell404ll developers project
//
//          @ All rights reserved
//
// Not open source version, only for course work

#include <SDL.h>
#include <GameModule.h>
#include <iostream>

//
//  Developer func
//

// Show/Hide console window (~)
void HideShowConsole(bool& ConsoleStatus)
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
void FPSCounter(int& fps_count, int& fps_time)
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