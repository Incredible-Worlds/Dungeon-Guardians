#include "GameModule.h"

int ChestCheck(AreaData* world,
    PositionData position,
    std::vector<InventoryData> inventory)
{

    InventoryData temp;
    temp.item_id = HealFlask;

    for (int i = 0; i < worldsize; i++)
    {
        if ((world[i].position.posx == position.posx
            && world[i].position.posy == position.posy)
            && world[i].tileName == CHEST)
        {
            inventory.push_back(temp);
            world[i].tileName = EMPTY;
        }
    }
    return 0;
}
