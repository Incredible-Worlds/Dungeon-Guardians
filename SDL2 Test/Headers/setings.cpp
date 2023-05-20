#include "Setings.h"
#include <fstream>

SetingsData::SetingsData()
{
    width = GetSystemMetrics(SM_CXSCREEN);
    height = GetSystemMetrics(SM_CYSCREEN);
    fullscreen = true;
    music = true;
}

int SetingsData::LoadFromFile(SetingsData& setings)
{
    std::ifstream setingsLoad("../SDL2 Test/save/setings.data");

    if (setingsLoad)
    {
        if (setingsLoad.is_open())
        {
            while (setingsLoad.read((char*)&setings, sizeof(SetingsData)))
            {
            }
        }
    }

    setingsLoad.close();
    return EXIT_SUCCESS;
}

int SetingsData::WriteToFile(SetingsData& setings)
{
    std::ofstream setingsWrite("./save/setings.data");

    if (setingsWrite.is_open())
    {
        setingsWrite.write((char*)&setings, sizeof(SetingsData));
    }

    setingsWrite.close();
    return EXIT_SUCCESS;
}

int SetingsData::ChangeMusicStatus(SetingsData& setings)
{
    if (setings.music == true)
    {
        setings.music = false;
    }
    else
    {
        setings.music = true;
    }

    return 0;
}
