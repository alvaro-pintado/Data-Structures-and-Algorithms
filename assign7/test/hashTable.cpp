#include "hashTable.h"
#include <string>
#include <iostream>

using namespace std;

hashTable::hashTable()
{
    hashSize = initialHashSize;
    reSizeCount = 0;
    collisionCount = 0;
    entries = 0;

    addrHash = new string*[initialHashSize];                // creates hash table
    for(unsigned int i = 0; i < initialHashSize; i++)
       addrHash[i] = new string[3];                         // for each entry, a string array of size 3 (zip, city, state)  is created

    for(unsigned int i = 0; i < initialHashSize; i++)       // initialize the zip field to -1, represents empty state
       addrHash[i][0] = "-1";
}

hashTable::~hashTable()
{
    for(unsigned int i = 0; i < hashSize; i++)              // iterate through hash table and delete arrays
        delete[] addrHash[i];
}

bool hashTable::insert(const string zip, const string city, const string state)
{
    //cout << "city: " << city << " state: " << state << endl;
    string cityCheck = "";
    string stateCheck = "";
    if(!lookup(zip, cityCheck, stateCheck))                 // check if zip is in hash table
    {
        //cout << "inserting zip: " << zip << endl;
        unsigned int hashedZip = hash(zip);
        while(addrHash[hashedZip][0] != "-1" && addrHash[hashedZip][0] != "*")     // while a possible slot has not been found, increment via linear probing
        {
            //cout << "COLLISION DETECTED for " << zip << " at " << hashedZip << endl;
            //cout << addrHash[hashedZip][0] << " occupying slot" << endl;
            collisionCount++;
            hashedZip++;
            if(hashedZip == hashSize)
                hashedZip = 0;
        }

        addrHash[hashedZip][0] = zip;
        addrHash[hashedZip][1] = city;
        addrHash[hashedZip][2] = state;
        //cout << addrHash[hashedZip][0] << " " << addrHash[hashedZip][1] << " " << addrHash[hashedZip][2] << endl;
        entries++;
        //cout << "entries location: " << &entries << endl;

        double lFactor = double(entries)/hashSize;
        if( lFactor > loadFactor)                           // at the end of insertion, check rehashing requirements
        {
            //cout << "Load factor " << lFactor << endl;
            //cout << "Needs rehashing" << endl;
            rehash();
        }
        return true;
    }

    else                                                    // if zip found, return false and exit
        return false;
}

bool hashTable::lookup(const string zip, string & city, string & state) const
{
    unsigned int hashedZip = hash(zip);

    while(addrHash[hashedZip][0] != "-1" && addrHash[hashedZip][0] != "*" && addrHash[hashedZip][0] != zip)     // while the duplicate nor an empty slot has been found, increment via linear probing
    {
        //cout << "looking for: " << zip << " at: " << hashedZip << endl;
        //cout << "index has: " << addrHash[hashedZip][0] << endl;
        hashedZip++;
        if(hashedZip == hashSize)
            hashedZip = 0;
    }
    if(addrHash[hashedZip][0] == "-1")                      // if any empty slot was found, zip doesn't exist, return false
        return false;
    else if(addrHash[hashedZip][0] == "*")                  // if a tombstone was found, zip might not exist
    {
        unsigned int probeIndex = hashedZip;
        while(addrHash[probeIndex][0] != "-1" && addrHash[probeIndex][0] != zip)    // keep probing until an empty slot or duplicate is found
        {
            probeIndex++;
            if(probeIndex == hashSize)
                probeIndex = 0;
        }

        if(addrHash[probeIndex][0] == "-1")                 // if empty slot found, zip indeed does not exist, return false
            return false;
        else if(addrHash[probeIndex][0] == zip)             // if duplicate found, zip exists, return true
        {
            city = addrHash[probeIndex][1];
            state = addrHash[probeIndex][2];
            return true;
        }
    }
    else if(addrHash[hashedZip][0] == zip)                  // if duplicate was found, return true
    {
            city = addrHash[hashedZip][1];
            state = addrHash[hashedZip][2];
            return true;
    }


}

void hashTable::showHashStats() const
{
    cout << "Hash Stats" << endl;
    cout << "   Current Entries Count:  " << entries << endl;
    cout << "   Current Hash Size:      " << hashSize << endl;
    cout << "   Hash Resize Operations: " << reSizeCount << endl;
    cout << "   Hash Collisions:        " << collisionCount << endl;

    for(int i = 0; i < 65; i++)
        cout << "*";
    cout << endl;
}

void hashTable::printHash() const
{

    for(int i = 0; i < hashSize; i++)
    {
        if(addrHash[i][0] != "*" && addrHash[i][0] != "-1")
        {
            for(int j = 0; j < 3; j++)                             // iterate through hashtable printing all 3 fields
                cout << addrHash[i][j] << " : ";
            cout << endl;
        }
    }
}

bool hashTable::remove(const string zip)
{
    string cityCheck = "";
    string stateCheck = "";
    unsigned int hashedZip = hash(zip);
    //cout << "remove fail" << endl;
    if(lookup(zip, cityCheck, stateCheck))                     // look too see if zip exits
    {
        while(addrHash[hashedZip][0] != zip)                   // loop to zip index
        {
            hashedZip++;
            if(hashedZip == hashSize)
                hashedZip = 0;
        }

        addrHash[hashedZip][0] = "*";                          // set a tombstone
        entries--;
        return true;
    }

    else
        return false;
}

void hashTable::rehash()
{
    string** oldTable = addrHash;
    hashSize = hashSize*2;
    //cout << "new hash table size: " << hashSize << endl;
    addrHash = NULL;
    addrHash = new string*[hashSize];                           // creates hash table twice as big
    entries = 0;                                                // resets entries to 0

    for(unsigned int i = 0; i < hashSize; i++)
       addrHash[i] = new string[3];                             // for each entry, a string array of size 3 (zip, city, state)  is created

        for(unsigned int i = 0; i < hashSize; i++)              // initialize the zip field to *, represents empty state
           addrHash[i][0] = "-1";

    //cout << "new table created" << endl;
    //printHash();
    for(int i = 0; i < hashSize/2; i++)
    {
        if(oldTable[i][0] != "*" && oldTable[i][0] != "-1")
        {
            //cout << "inserting " << oldTable[i][0] << " into new table" << endl;
            insert(oldTable[i][0], oldTable[i][1], oldTable[i][2]);
        }
    }

    for(int i = 0; i < hashSize/2; i++)
        delete []oldTable[i];

    reSizeCount++;
    //cout << "Rehashed, rehash count: " << reSizeCount << endl;
}

/*
unsigned int hashTable::hash(string key) const
{
    unsigned int hash = 0;
    for(int i = (key.length()-1); i >= 0; i--)
    {
        hash = (key[i] + 128*hash) % hashSize;
    }
    return hash;
}
 */

// ASCII Sum Value Hash Function
/*
unsigned int hashTable::hash(string key) const
{
    unsigned int hash = 0;
    for(int i = 0; i < key.length(); i++)
    {
        hash += key[i];
    }
    return hash%hashSize;
}
*/

// Zip Code to Integer Hash Function
 /*
unsigned int hashTable::hash(string key) const
{
    unsigned int hash = 0;
    hash = stoi(key) % hashSize;
    return hash;
} */

// My Hash Function
unsigned int hashTable::hash(string key) const
{
    unsigned int hash = 0;
    hash = stoi(key)*37 % hashSize;
    return hash;
}
