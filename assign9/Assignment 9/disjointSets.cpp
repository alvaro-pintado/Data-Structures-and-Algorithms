#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "disjointSets.h"

using namespace std;

disjointSets::disjointSets():totalSize(0), setsCount(0), links(NULL), sizes(NULL){}     //constructor

disjointSets::~disjointSets()                                                           //destructor
{
    delete []links;
    delete []sizes;
}

void disjointSets::createSets(int size)
{
    if(size < 0)
        return;

    links = new int[size];
    sizes = new int[size];

    for(int i = 0; i < size; i++)
    {
        links[i] = -1;
        sizes[i] = 1;
    }

    totalSize = size;
    setsCount = size;
}

int disjointSets::getTotalSets() const
{
    return totalSize;
}

int disjointSets::getSetCount() const
{
    return setsCount;
}

int disjointSets::getSetSize(const int index) const
{
    return sizes[index];
}

void disjointSets::printSets() const
{
    cout << "      Index: ";
    for(int i = 0; i < totalSize; i++)
    {
        cout << setw(3) << right;
        cout << i;
    }
    cout << endl;

    cout << "      Links: ";
    for(int i = 0; i < totalSize; i++)
    {
        cout << setw(3) << right;
        cout << links[i];
    }
    cout << endl;

    cout << "      Sizes: ";
    for(int i = 0; i < totalSize; i++)
    {
        cout << setw(3) << right;
        cout << sizes[i];
    }
    cout << endl;
}

int disjointSets::setUnion(int a, int b)
{
    a = setFind(a);
    b = setFind(b);
    if(a == b)
        return a;
    int parent;

    setsCount --;
    if(sizes[a] >= sizes[b])
    {
        parent = a;
        links[b]= a;
        sizes[a] = sizes[b] + sizes[a];
        sizes[b] = 0;

        return parent;
    }

    else
    {
        parent = b;
        links[a] = b;
        sizes[b] = sizes[a] + sizes[b];
        sizes[a] = 0;
        return parent;
    }

}

int disjointSets::setFind(int index)
{
    if(index < 0 || index > totalSize)
        return 0;

    if(links[index] < 0)
        return index;

    links[index] = setFind(links[index]);
    return links[index];
}

void disjointSets::largestSets(int &a, int &b)
{
    a = 0;
    b = 0;
    for(int i = 0; i < totalSize; i++)
    {
        if(sizes[i] > a)
            a = i;
        else if(sizes[i] > b)
            b = i;
    }
    cout << "Largest Set Size        = " << sizes[a] << endl;
    cout << "Largest Set Prnt        = " << a << endl;
    cout << "Second largest Set Size = " << sizes[b] << endl;
    cout << "Second largest Set Prnt = " << b << endl;
}
