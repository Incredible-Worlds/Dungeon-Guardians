#include "AIver2.h"


int EnemyMovement_AI(AreaData* world, PositionData& mobPosition, PositionData playerPosition)
{
	if (mobPosition.posx == playerPosition.posx)
	{
		if (mobPosition.posy - playerPosition.posy > 0)
		{
			mobPosition.posy -= CollisionCheck(world, mobPosition, UP);
			return 0;
		}

		else if (mobPosition.posy - playerPosition.posy < 0)
		{
			mobPosition.posy += CollisionCheck(world, mobPosition, DOWN);
			return 0;
		}
	}
	else if (mobPosition.posy == playerPosition.posy)
	{
		if (mobPosition.posx - playerPosition.posx < 0)
		{
			mobPosition.posx += CollisionCheck(world, mobPosition, RIGHT);
			return 0;
		}

		else if (mobPosition.posx - playerPosition.posx > 0)
		{
			mobPosition.posx -= CollisionCheck(world, mobPosition, LEFT);
			return 0;
		}
	}

	EnemyMovement(mobPosition, world);

	return 0;
}
