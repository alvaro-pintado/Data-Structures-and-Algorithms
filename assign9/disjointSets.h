#ifndef DISJOINTSETS_H
#define DISJOINTSETS_H

class disjointSets
{
public:
    disjointSets();
    ~disjointSets();
    void createSets(int);
    int getTotalSets() const;
    int getSetCount() const;
    int getSetSize(const int) const;
    void printSets() const;
    int setUnion(int, int);
    int setFind(int);
    void largestSets(int&, int&);

private:
    int totalSize;
    int setsCount;
    int* links;
    int* sizes;
};

#endif

