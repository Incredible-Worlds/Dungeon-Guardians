// Kamys, Potrox and Bell404ll developers project
//
//          @ All rights reserved
//
// Not open source version, only for course work

#include "RandomGen.h"
#include <iostream>
#include <fstream>
#include <vector>

int Saveload::WriteToMapFile()
{
	std::ofstream loadfile("./save/map.data");

	return EXIT_SUCCESS;
}

int Saveload::LoadFromMapFile()
{
	std::ifstream savefile("./save/map.data");

	return EXIT_SUCCESS;
}

//EASY4ENCE