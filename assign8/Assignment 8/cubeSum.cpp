#include "priorityQueue.h"
#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <array>

using namespace std;

struct cubeSet
{
    unsigned long long sum;
    array<int,2> pair;

};
cubeSet def = {0, 0, 0}; //default values


int main(int argc, char *argv[])
{
// /////////////////////////////////////////////////////////////////////////////////////////////////
    //ARGUMENT CHECKING
    // *****************************************************************
    //  Data declarations...

        string	stars;
        stars.append(65, '*');

        int limit = 0;
        limit = stoi(string(argv[2]));

    // ------------------------------------------------------------------
    //  Get/verify command line arguments.
    //	Error out if bad arguments...

        if (argc == 1) {
            cout << "Usage: cubeSum -l <limit> " << endl;
            exit(1);
        }

        if (argc != 3) {
            cout << "Error, invalid command line options." << endl;
            exit(1);
        }

        if (string(argv[1]) != "-l") {
            cout << "Error, invalid limit specifier." << endl;
            exit(1);
        }

        if (limit > 1000000 || limit < 10) {
            cout << "Error, invalid limit (max = 1,000,000, min = 10)." << endl;
            exit(1);
        }

// //////////////////////////////////////////////////////////////////////////////////////////////////////////
    priorityQueue< array<int,2> > taxiNums;

    cubeSet possSet;

    for(int i = 1; i < limit; i++)
    {
        possSet.pair[0] = i;
        possSet.pair[1] = i;
        possSet.sum = pow(i,3) + pow(i,3);
        taxiNums.insert(possSet.pair, possSet.sum);
    }

    int count = 1;
    int totalCount = 0;
    cubeSet prevSet;
    cubeSet currSet;
    cubeSet newSet;

    while(!taxiNums.isEmpty())
    {
        taxiNums.deleteMin(currSet.pair, currSet.sum);
        if(currSet.sum == prevSet.sum)
        {
            count++;
            if(count == 2)
            {
                cout << currSet.sum << " = " << currSet.pair[0] << "^3 + " << currSet.pair[1] << "^3 = " << prevSet.pair[0] << "^3 + " << prevSet.pair[1] << "^3" << endl;
                totalCount++;
            }

        }
        else
            count = 1;

        prevSet = currSet;

        if(currSet.pair[1] < limit)
        {
            newSet.pair[0] = currSet.pair[0];
            newSet.pair[1] = currSet.pair[1]+1;
            newSet.sum = pow(currSet.pair[0], 3) + pow(currSet.pair[1]+1, 3);
            taxiNums.insert(newSet.pair, newSet.sum);
        }
    }

    cout << "Total \"relaxed\" taxicab numbers found: " << totalCount << endl;
}
