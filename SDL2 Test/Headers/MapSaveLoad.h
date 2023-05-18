#pragma once

#include "GameModule.h"
#include <fstream>

class Saveload
{
public:

	int WriteAll(AreaData* world, PlayerData player);

	int LoadAll(AreaData* world, PlayerData& player);

private:
	int WriteToMapFile(AreaData* world);

	int LoadFromMapFile(AreaData* world);

	int WriteToCharacterFile(PlayerData player);

	int LoadFromCharacterFile(PlayerData& player);
};

