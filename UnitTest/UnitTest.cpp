#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include "../SDL2 Test/Headers/GameModule.h"
#include "../SDL2 Test/Headers/GameModule.cpp"
#include "../SDL2 Test/Headers/MapSaveLoad.h"
#include "../SDL2 Test/Headers/MapSaveLoad.cpp"
#include "../SDL2 Test/Headers/Setings.h"
#include "../SDL2 Test/Headers/Setings.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest_GameModule)
	{
	public:
		TEST_METHOD(PlayerPos)
		{
			PositionData p;
			Assert::IsTrue(p.posx == 10);
			Assert::IsTrue(p.posy == 10);
		}
		TEST_METHOD(Player_health_and_coord)
		{
			PlayerData p;
			Assert::IsTrue(p.health != 0);
			Assert::IsTrue((p.position.posx >= 0) && (p.position.posx <= 1024));
			Assert::IsTrue((p.position.posy >= 0) && (p.position.posy <= 1024));
		}
		TEST_METHOD(World_collision)
		{
			SetingsData a;
			PlayerData b;
			PositionData c;
			AreaData* world = new AreaData[worldsize];
			//--------------------------------------------------
			std::ifstream loadfile("../SDL2 Test/save/player.data");

			if (loadfile.is_open())
			{
				while (loadfile.read((char*)&b, sizeof(PlayerData)))
				{
				}
			}

			loadfile.close();
			//--------------------------------------------------
			std::ifstream loadfile1("../SDL2 Test/save/map.data");

			for (int i = 0; i < worldsize; i++)
			{
				loadfile1.read((char*)&world[i], sizeof(AreaData));
			}

			loadfile1.close();
			//--------------------------------------------------
			bool ConsoleStatus = false;
			Assert::IsTrue(HideShowConsole(ConsoleStatus) == 0);
			Assert::IsTrue(CollisionCheck(world, b.position, RIGHT) == (int)(a.width / 60));
			Assert::IsTrue(CollisionCheck(world, b.position, LEFT) == (int)(a.width / 60));
			Assert::IsTrue(CollisionCheck(world, b.position, UP) == (int)(a.width / 60));
			Assert::IsTrue(CollisionCheck(world, b.position, DOWN) == (int)(a.width / 60));
			Assert::IsTrue(EnemyMovement(c, world) == EXIT_SUCCESS);
		}
	};
}
