//  CS 302
//  Provided Main Program

//  Maze generation assignment.

// ***********************************************************************
//  Includes and prototypes.
  
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

#include "mazeGenerator.h"

// *********************************************************************
//  Verify command line arguments.
//  Required format:
//	-h <heightValue> -w <widthValue> -f <fileName> <-p|>

bool	getArgs(int argc, char *argv[], int &height, int &width,
		string &fileName, bool &prtMazeOpt)
{
	stringstream ss;

	if (argc == 1) {
		cout << "Usage: ./makeMaze -h <heightValue> -w <widthValue> -f <fileName> <-p|>" << endl;
		return	false;
	}

	if (argc < 7 || argc > 8) {
		cout << "Error, invalid command line arguments." << endl;
		return	false;
	}

	if (string(argv[1]) != "-h") {
		cout << "Error, invalid height specifier." << endl;
		return	false;
	}

	ss.clear();
	if (string(argv[2]) != "") {
		ss << argv[2];
		ss >> height;
	}

	if (string(argv[3]) != "-w") {
		cout << "Error, invalid width specifier." << endl;
		return	false;
	}

	ss.clear();
	if (string(argv[4]) != "") {
		ss << argv[4];
		ss >> width;
	}

	if (string(argv[5]) != "-f") {
		cout << "Error, invalid file name specifier." << endl;
		return	false;
	}

	if (string(argv[6]) == "") {
		cout << "Error, file does not exist." << endl;
		return	false;
	}

	fileName = string(argv[6]);

	prtMazeOpt = false;
	if (argc == 8 && string(argv[7]) == "-p")
		prtMazeOpt = true;


	return	true;

}

// *******************************************************************

int main(int argc, char *argv[])
{
// ------------------------------
//  Declarations and headers.

	string			stars;
	string			mazeFile;
	bool			prtTextMaze;
	int			height, width;

	stars.append(60,'*');
	const char* bold   = "\033[1m";
	const char* unbold   = "\033[0m";
	const char* green   = "\033[32m";

// ------------------------------
//  If command line arguments ok
//	display headers
//	create/initialize maxe object
//	create a random maze
//	if requested, print maze

	if (getArgs (argc, argv, height, width, mazeFile, prtTextMaze)) {

		cout << stars << endl;
		cout << "CS 302 - Assignment #4" << endl;
		cout << bold << green << "Maze Generator." << unbold << endl;
		cout << endl << endl;

		mazeGenerator	myMaze(height, width);

		myMaze.createMaze();

		if (prtTextMaze)
			myMaze.printMaze();

		if (!myMaze.printWalls(mazeFile))
			cout << "Error, " << mazeFile << " not created." << endl;

		//  Done, terminate program.
		cout << endl;
		cout << "Game over, thanks for playing." << endl;

	}

	return 0;
}

