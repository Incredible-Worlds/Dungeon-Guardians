#pragma once
#include "GameModule.h"

class SetingsData
{
public:
	int width;
	int height;
	bool fullscreen;
	bool music;

	SetingsData();

	int LoadFromFile(SetingsData& setings);

	int WriteToFile(SetingsData& setings);

	int ChangeMusicStatus(SetingsData& setings);
};