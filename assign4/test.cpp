#include <iostream>
#include "mazeGenerator.h"
#include <string>

using namespace std;

int main()
{
	string noFile = "";
	mazeGenerator testMaze(5,5);
	testMaze.printWalls("mazeFile3.txt");
}
