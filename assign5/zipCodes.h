#ifndef ZIPCODES_H
#define ZIPCODES_H

#include "redBlackTree.h"
#include <string>

class zipCodes: public redBlackTree<string>
{
public:
    zipCodes();
    ~zipCodes();
    bool readMasterZipCodes(const string);
    bool checkZips(const string);
    void showStats() const;

private:
    redBlackTree<string> masterZipCodes;
    int goodCount;
    int badCount;
};

#endif

