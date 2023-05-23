#pragma once
#include "GameModule.h"
#include <vector>

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
	bool is_active;

	InventoryData();

	int setDurability();

	int CheckChests(AreaData* world,
		PositionData position,
		std::vector<InventoryData>& inventory);

};