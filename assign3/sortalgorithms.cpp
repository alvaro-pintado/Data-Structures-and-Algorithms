#include "sortalgorithms.h"
#include <iomanip>
#include <iostream>
#include <cstdlib>

using namespace std;

sortAlgorithms::sortAlgorithms(){}

sortAlgorithms::~sortAlgorithms(){delete [] myArray;}

void sortAlgorithms::generateData(int n)
{
    myArray = new short[n];
    length = n;

    for (int i=0; i<n; i++)
        myArray[i] = rand() % LIMIT;
}

int sortAlgorithms::getLength()
{
    return length;
}

short sortAlgorithms::getItem(int index)
{
    return myArray[index];
}

void sortAlgorithms::printData()
{
    for(int i = 0; i < length; i++)
    {
        cout << setw(6) << right;

        if(i%10 == 0)
            cout << endl;
        cout << myArray[i] << " ";
    }
    cout << endl;
}

void sortAlgorithms::bubbleSort()
{
    bool swapped;
    for(int i = (length-1); i>0; i++)
    {
        int n = i;
        bool swapped = false;
        while(!swapped)
        {
            if(myArray[n] > myArray[n-1])
            {
                swap(myArray[n], myArray[n-1]);
                swapped = true;
            }
        }
    }
}
/*
void sortAlgorithms::selectionSort();
void sortAlgorithms::quickSort();
void sortAlgorithms::countSort();
void sortAlgorithms::selectionSort(int, int);
void sortAlgorithms::quickSort(int, int);
int sortAlgorithms::partition(int, int);
*/
