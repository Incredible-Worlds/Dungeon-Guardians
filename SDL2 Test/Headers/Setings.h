#pragma once
#include "GameModule.h"

class SetingsData
{
public:
	int width;
	int height;
	bool fullscreen;

	SetingsData()
	{
		width = GetSystemMetrics(SM_CXSCREEN);
		height = GetSystemMetrics(SM_CYSCREEN);
		fullscreen = true;
	}

};