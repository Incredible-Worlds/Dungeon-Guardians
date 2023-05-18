#pragma once

#include "GameModule.h"
#include <fstream>

class Saveload
{
public:

	int WriteToMapFile(AreaData* world);

	int LoadFromMapFile(AreaData* world);
	
	int WriteToCharacterFile();

	int LoadFromCharacterFile();

};

