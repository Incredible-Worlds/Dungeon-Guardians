#pragma once

#include "GameModule.h"
#include <fstream>

class Saveload
{
public:

	int WriteToMapFile();

	int LoadFromMapFile();
	
	Saveload();
};

