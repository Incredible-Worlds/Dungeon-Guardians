// Kamys, Potrox and Bell404ll developers project
//
//          @ All rights reserved
//
// Not open source version, only for course work

#include "MapSaveLoad.h"
#include <iostream>
#include <fstream>
#include <vector>

int Saveload::WriteToMapFile(AreaData* world)
{
	std::ofstream writefile("./save/map.data");

	for (int i = 0; i < worldsize; i++)
	{
		writefile.write((char*)&world[i], sizeof(AreaData));
	}

	writefile.close();

	return EXIT_SUCCESS;
}

int Saveload::LoadFromMapFile(AreaData* world)
{
	std::ifstream loadfile("./save/map.data");

	for (int i = 0; i < worldsize; i++)
	{
		loadfile.read((char*)&world[i], sizeof(AreaData));
	}

	loadfile.close();

	return EXIT_SUCCESS;
}

int Saveload::WriteToCharacterFile()
{
	std::ofstream loaded_characterfile("./save/character.data");

	

	return EXIT_SUCCESS;
}

int Saveload::LoadFromCharacterFile()
{
	std::ifstream saved_characterfile("./save/character.data");

	return 0;
}

 

//EASY4ENCE