#pragma once
#include "MainMenu.h"

enum ItemIdList
{
	STOCK_SWORD,
	MID_SWORD,
	EPIC_SWORD
};

class InventoryData
{
public:
	int item_id;
	int durability;


	InventoryData();
private:

};