#include "Inventory.h"

InventoryData::InventoryData()
{
	item_id = 0;
	durability = 0;
	is_active = false;
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

int InventoryData::CheckChests(AreaData* world,
	PositionData position,
	std::vector<InventoryData>& inventory)
{
    InventoryData temp;
    temp.item_id = HealFlask;
    temp.setDurability();

    for (int i = 0; i < worldsize; i++)
    {
        if ((world[i].position.posx == position.posx
            && world[i].position.posy == position.posy)
            && world[i].tileName == CHEST)
        {
            inventory.push_back(temp);
            world[i].tileName = EMPTY;
            break;
        }
    }

    return 0;
}

//EASY4ENCE