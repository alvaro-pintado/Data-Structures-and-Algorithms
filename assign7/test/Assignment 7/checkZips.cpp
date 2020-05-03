//  CS 302 Assignment #7
//  Check zip codes
//  Provided main program.

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <chrono>

#include "zipCodes.h"

using namespace std;

int main(int argc, char *argv[])
{
    // get start timer...
    auto t1 = chrono::high_resolution_clock::now();

// *****************************************************************
//  Data declarations...

	string	stars;
	stars.append(65, '*');

	string	zipsFile;
	string	dataFile;

// ------------------------------------------------------------------
//  Get/verify command line arguments.
//	Error out if bad arguments...

	if (argc == 1) {
		cout << "Usage: checkZips -z <masterZipCodesFile> -d <inputDataFile>" << endl;
		exit(1);
	}

	if (argc != 5) {
		cout << "Error, invalid command line options." << endl;
		exit(1);
	}

	if (string(argv[1]) != "-z") {
		cout << "Error, invalid master zip code file specifier." << endl;
		exit(1);
	}

	if (string(argv[3]) != "-d") {
		cout << "Error, invalid input data file specifier." << endl;
		exit(1);
	}

	zipsFile = string(argv[2]);
	dataFile = string(argv[4]);

// ------------------------------------------------------------------
//  Display some cute headers...

	cout << stars << endl << "CS 302 - Assignment #7" << endl;
	cout << "ZIP Code Checking Program" << endl;
	cout << endl;

// ------------------------------------------------------------------
//  Main processing.
//	Read master zip codes.
//	Check zip-code data file.

	zipCodes	zipSet1;

	if (!zipSet1.readMasterZipCodes(zipsFile)) {
		cout << "checkZips: Error reading master zip codes file." << endl;
		exit(1);
	}

	if (!zipSet1.checkZips(dataFile)) {
		cout << "checkZips: Error reading ZIPS data file." << endl;
		exit(1);
	}

	zipSet1.showHashStats();
	zipSet1.showStats();

// *****************************************************************
//  All done.

	cout << stars << endl << "Game Over, thank you for playing." << endl;
    // //////////////////////////////////////////////////////////////////////////////
        // get end time...
        auto t2 = chrono::high_resolution_clock::now();

        // show results with times
       cout << "Program took: " << std::chrono::duration_cast<std::chrono::milliseconds>
               (t2-t1).count() << " milliseconds" << endl;

	return 0;
}

