#include "Setings.h"
#include <fstream>

int SetingsData::LoadFromFile(SetingsData& setings)
{
    std::ifstream setingsLoad("setings.data");

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
    std::ofstream setingsWrite("setings.data");

    if (setingsWrite.is_open())
    {
        setingsWrite.write((char*)&setings, sizeof(SetingsData));
    }

    setingsWrite.close();
    return EXIT_SUCCESS;
}
