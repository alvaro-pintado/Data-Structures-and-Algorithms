#ifndef CONNECTEDCOMPONENTS_H
#define CONNECTEDCOMPONENTS_H

#include "disjointSets.h"
#include <string>

using namespace std;

class connectedComponents: public disjointSets
{
public:
    connectedComponents();
    ~connectedComponents();
    bool readImageFile(const string);
    void identify();
    void fillComponent(const int);
    bool writeImageFile(const string);
    void setThreshold(const int);
    void showStatus() const;
    int calcIndex(int, int);
private:
    unsigned char** image;
    int rows;
    int columns;
    int threshold;
    disjointSets imageSet;
    static constexpr int MIN_SIZE = 10;
    static constexpr int MAX_SIZE = 1000000;
    bool withinThreshold(const unsigned char, const unsigned char) const;


};

#endif
