#ifndef GRAPHALGORITHMS_H
#define GRAPHALGORITHMS_H

#include <string>

using namespace std;

class graphAlgorithms
{
public:
    graphAlgorithms();
    graphAlgorithms(int);
    ~graphAlgorithms();
    void newGraph(int);
    void addEdge(int, int, int);
    bool readGraph(const string);
    int getVertexCount() const;
    void printMatrix() const;
    void topoSort();
    void dijkstraSP(int);
    void printPath(const int, const int);
    void showPath(const int) const;
    string getGraphTitle() const;
    void setGraphTitle(const string);
    void printDistances(const int) const;

private:
    int vertexCount;
    string title;
    int** graphMatrix;
    int* dist;
    int* prev;
    int* topoNodes;
    int topoCount;

    void destroyGraph();
    void dfs(int, bool[]);


};

#endif
