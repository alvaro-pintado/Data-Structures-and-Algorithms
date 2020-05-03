#ifndef ZIPCODES_H
#define ZIPCODES_H

#include "hashTable.h"
#include <string>

class zipCodes: public hashTable
{
public:
    zipCodes();
    ~zipCodes();
    bool readMasterZipCodes(const string);
    bool checkZips(const string);
    void showStats() const;

private:
    int goodCount;
    int badCount;
};

#endif

