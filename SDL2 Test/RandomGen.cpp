// Kamys, Potrox and Bell404ll developers project
//
//          @ All rights reserved
//
// Not open source version, only for course work

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int random_presets_main()
{
	ifstream file;

	int SizeOf = 32; //негра

	vector <char> world(SizeOf);

	//Value that will define preset
	srand(time(NULL));
	int preset = rand() % 5;


	//Chosing world preset process
	switch (preset)
	{
		case 1:
		{
			file.open("2.txt");
			file.read(world.data(), SizeOf);
		}

		case 2:
		{
			file.open("3.txt");
			file.read(world.data(), SizeOf);
		}

		case 3:
		{
			file.open("4.txt");
			file.read(world.data(), SizeOf);
		}

		case 4:
		{
			file.open("5.txt");
			file.read(world.data(), SizeOf);
		}

		default:
		{
			file.open("1.txt");
			file.read(world.data(), SizeOf);
		}
	}

	return 0;
}

//EASY4ENCE