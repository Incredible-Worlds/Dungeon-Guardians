#pragma once
#include "MainMenu.h"

enum ItemIdList
{
	EmptySpace,
	CommonSword1,
	CommonSword2,
	CommonSword3,
	HealFlask,
	FinalSword,
};

class InventoryData
{
public:
	int item_id;
	int durability;

	InventoryData();

	int setDurability();

private:

};