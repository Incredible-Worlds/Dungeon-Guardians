#include "Inventory.h"

InventoryData::InventoryData()
{
	item_id = 0;
	durability = 20;
}

int InventoryData::setDurability()
{
	switch (item_id)
	{
		case CommonSword1:
		{
			durability = 20;
			break;
		}
		case CommonSword2:
		{
			durability = 50;
			break;
		}
		case CommonSword3:
		{
			durability = 100;
			break;
		}
		case FinalSword:
		{
			durability = 300;
			break;
		}
		case HealFlask:
		{
			durability = rand() % 3;
			break;
		}
		default:
		{
			item_id = 0;
			durability = 0;
			return 51;
		}
			
	}

	return 0;
}

//EASY4ENCE