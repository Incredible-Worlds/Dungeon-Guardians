#include "MapInteract.h"

int GenerateNewMap(AreaData* world)
{
    SetingsData setings;
    setings.LoadFromFile(setings);

    world[0].position.posx = 1;
    world[0].position.posy = 1;

    /// Creating worldmap
    for (int i = 1; i < worldsize; i++)
    {
        world[i].position.posx = world[i - 1].position.posx + 1;
        world[i].position.posy = world[i - 1].position.posy;
        world[i].tileStatus = true;

        if (i % 32 == 0)
        {
            world[i].position.posx = 1;
            world[i].position.posy = world[i].position.posy + 1;
        }

        if (world[i].position.posx == 1
            || world[i].position.posy == 1
            || world[i].position.posx == 31
            || world[i].position.posy == 31)
        {
            world[i].tileName = BOUND;
        }
        else
        {
            world[i].tileName = EMPTY;
        }
    }

    world[0].tileName = BOUND;

    /// Generate chests
    srand(time(NULL));
    for (int i = 1; i < worldsize; i++)
    {
        int countchest = rand() % 100;
        int countchest1 = rand() % 100;
        int countmob = rand() % 100;
        if (countchest == 33 and (countchest1 == 9
            or countchest1 == 19
            or countchest1 == 29
            or countchest1 == 39
            or countchest1 == 49
            or countchest1 == 59
            or countchest1 == 69
            or countchest1 == 79
            or countchest1 == 89
            or countchest1 == 99))
        {
            world[i].tileName = CHEST;
        }
    }

    return EXIT_SUCCESS;
}

int CheckWorld(AreaData* world, PositionData position)
{
    position.SetTilePos();
    for (int i = 0; i < worldsize; i++)
    {
        if (time(NULL) - world[i].tileStatusTimer > 25)
        {
            world[i].tileStatus = true;
        }

        if ((world[i].position.posy == position.GetTilePosy())
            && (world[i].position.posx == position.GetTilePosx()))
        {
            for (int j = i - 1; j < i + 2; j++)
            {
                world[j].tileStatus = true;

                world[j].tileStatusTimer = time(NULL);
            }

            world[i - (int)sqrt(worldsize)].tileStatus = true;
            world[i - (int)sqrt(worldsize)].tileStatusTimer = time(NULL);

            world[i + (int)sqrt(worldsize)].tileStatus = true;
            world[i + (int)sqrt(worldsize)].tileStatusTimer = time(NULL);
        }
    }

    return EXIT_SUCCESS;
}
