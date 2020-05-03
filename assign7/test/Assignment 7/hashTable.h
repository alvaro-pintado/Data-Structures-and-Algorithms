#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>

using namespace std;

class hashTable{
public:
    hashTable(); //constructor
    ~hashTable(); // destructor
    bool insert(const string, const string, const string); // inserts key into hash table
    bool lookup(const string, string &, string &) const;   // find zip code and return city, state
    bool remove(const string);                             // removes the key in the hash table
    void printHash() const;                                // prints all non-empty entries in the hash table
    void showHashStats() const;                            // prints current hash size, resize count, and collision count
private:
    unsigned int hashSize;
    unsigned int reSizeCount;
    unsigned int collisionCount;
    unsigned int entries;
    string** addrHash;
    static constexpr double loadFactor = 0.65;
    static constexpr unsigned int initialHashSize = 10000;
    unsigned int hash(string) const;
    void rehash();
};

#endif
