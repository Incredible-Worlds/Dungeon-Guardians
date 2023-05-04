// Kamys, Potrox and Bell404ll developers project
//
//          @ All rights reserved
//
// Not open source version, only for course work

#include <iostream>
#include <fstream>
using namespace std;

int random_main()
{
	ifstream file;

	//Value that will define preset
	int preset = rand() % 5;


	//Chosing world preset process
	switch (preset)
	{
	case 1:
		file.open("...\Presets\2.txt");
	case 2:
		file.open("...\Presets\3.txt");
	case 3:
		file.open("...\Presets\4.txt");
	case 4:
		file.open("...\Presets\5.txt");
	default:
		file.open("...\Presets\1.txt");
	}

	//Loading current chosen preset into game world


	
}

//EASY4ENCE