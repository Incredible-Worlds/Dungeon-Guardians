#pragma once
#include "GameModule.h"

class SetingsData
{
public:
	int width;
	int height;
	bool fullscreen;

	SetingsData();

	int LoadFromFile(SetingsData& setings);

	int WriteToFile(SetingsData& setings);
};