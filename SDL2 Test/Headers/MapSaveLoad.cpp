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
	std::ifstream loadfile("../SDL2 Test/save/map.data");

	for (int i = 0; i < worldsize; i++)
	{
		loadfile.read((char*)&world[i], sizeof(AreaData));
	}

	loadfile.close();

	return EXIT_SUCCESS;
}

int Saveload::WriteToCharacterFile(PlayerData player)
{
	std::ofstream writefile("./save/player.data");

	if(writefile.is_open())
	{
		writefile.write((char*)&player, sizeof(PlayerData));
	}

	writefile.close();

	return EXIT_SUCCESS;
}

int Saveload::LoadFromCharacterFile(PlayerData& player)
{
	std::ifstream loadfile("../SDL2 Test/save/player.data");

	if (loadfile.is_open())
	{
		while (loadfile.read((char*)&player, sizeof(PlayerData)))
		{ }
	}

	loadfile.close();

	return EXIT_SUCCESS;
}

int Saveload::WriteAll(AreaData* world, PlayerData player)
{
	WriteToMapFile(world);
	WriteToCharacterFile(player);

	return EXIT_SUCCESS;
}

int Saveload::LoadAll(AreaData* world, PlayerData& player)
{
	LoadFromMapFile(world);
	LoadFromCharacterFile(player);

	return EXIT_SUCCESS;
}

//EASY4ENCE