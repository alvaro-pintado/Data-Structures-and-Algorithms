#include "graphAlgorithms.h"
#include "priorityQueue.h"
#include <string>
#include <limits>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

graphAlgorithms::graphAlgorithms():
    vertexCount(0), title(""), graphMatrix(NULL), dist(NULL), prev(NULL), topoNodes(NULL),
    topoCount(0){}

graphAlgorithms::graphAlgorithms(int size):
    vertexCount(0), title(""), graphMatrix(NULL), dist(NULL), prev(NULL), topoNodes(NULL),
    topoCount(0)
{
    //check if passed size for graph is at least 5
    if(size < 5)
    {
        cout << "graphAlgorithms: Error, invalid graph size." << endl;
        return;
    }
    else
        newGraph(size);
}

graphAlgorithms::~graphAlgorithms() {destroyGraph();}

void graphAlgorithms::newGraph(int size)
{
    //check for memory leaks
    destroyGraph();

    //allocate matrix memory and initialize weights to 0
    graphMatrix = new int*[size];
    for(int i = 0; i < size; i++)
    {
        graphMatrix[i] = new int[size];
        for(int j = 0; j < size; j++)
            graphMatrix[i][j] = 0;
    }

    vertexCount = size;
}

void graphAlgorithms::addEdge(int v1, int v2, int weight)
{
    //check for valid vertices
    if(v1 > vertexCount || v1 < 0 || v2 > vertexCount || v2 < 0)
    {
        cout << "addEdge: Error, invalid vertex." << endl;
        return;
    }

    if(v1 == v2)
    {
        cout << "addEdge: Error, vertex to and from can not the same." << endl;
        return;
    }

    //set weight between vertices
    graphMatrix[v1][v2] = weight;
}


void graphAlgorithms::topoSort()
{
    //initialization
    bool* visited = new bool[vertexCount];
    topoNodes = new int[vertexCount];
    topoCount = 0;
    for(int i = 0; i < vertexCount; i++)
    {
        visited[i] = false;
        topoNodes[i] = -1;
    }

    //dfs
    for(int i = 0; i < vertexCount; i++)
    {
        if(visited[i] == false)
            dfs(i, visited);
    }

    //print out topo sort
    cout << "Topological Sort: " << endl;
    for(int i = vertexCount-1; i >= 0; i--)
        cout << topoNodes[i] << " ";
    cout << endl;


}

void graphAlgorithms::dfs(int i, bool visited[])
{
    visited[i] = true;
    for(int e = 0; e < vertexCount; e++)
    {
        //if edge exists
        if(graphMatrix[i][e] > 0)
        {
            if(visited[e] == false)
                dfs(e, visited);
        }
    }
    topoNodes[topoCount++] = i;
}
void graphAlgorithms::dijkstraSP(int source)
{
    //initialization
    int maxDist = numeric_limits<int>::max();
    dist = new int[vertexCount];
    prev = new int[vertexCount];
    for(int i = 0; i < vertexCount; i++)
    {
        dist[i] = maxDist;
        prev[i] = -1;
    }

    priorityQueue<int> queue;

    queue.insert(source, 0);
    dist[source] = 0;

    heapNode<int> min;
    while(!queue.isEmpty())
    {
        queue.deleteMin(min.item,min.priority);
        for(int e = 0; e < vertexCount; e++)
        {
            //usleep(100000);
            int newDist = 0;
            //if edge exists
            if(graphMatrix[min.item][e] > 0)
            {
                //cout << "neighboor of " << min.item << " found: " << e << endl;
                newDist = dist[min.item] + graphMatrix[min.item][e];
                //cout << "distance from " << min.item << " to " << e << ": "
                     //<< newDist << endl;

                if(newDist < dist[e])
                {
                    dist[e] = newDist;
                    prev[e] = min.item;
                    queue.insert(e, newDist);
                }
            }
        }
    }
    printDistances(source);

}



void graphAlgorithms::destroyGraph()
{

}

void graphAlgorithms::printDistances(const int source) const
{
    if(dist == NULL)
    {
        cout << "printDistances: Error, no graph data" << endl;
        return;
    }
    cout << "Shortest Paths:" << endl << "From Node: " << source << " to: " << endl;
    cout << setw(15) << right << "Vertex" << setw(15) << "Dist" << setw(15) << "From" << endl;
    for(int i = 0; i < vertexCount; i++)
    {
        int maxDist = numeric_limits<int>::max();
        cout << setw(15) << i << setw(15);

        if(dist[i] == maxDist)
            cout << "n/a";
        else
            cout << dist[i];
        cout << setw(15);

        if(prev[i] == -1)
            cout << "-" << endl;
        else
            cout << prev[i] << endl;
    }
}
void graphAlgorithms::printPath(const int sn, const int dn)
{
    if(dist == NULL)
    {
        cout << "printPath: Error, no graph data" << endl;
        return;
    }

    cout << "Path from: " << sn << " to " << dn << endl;
    showPath(dn);
}

void graphAlgorithms::showPath(const int source) const
{
    if(prev[source] == -1)
    {
        cout << source;
        return;
    }
    else
    {
        showPath(prev[source]);
        cout << " - " << source;
    }
}

bool graphAlgorithms::readGraph(const string filename)
{
    string title = "";
    string in = "";
    int size = 0;
    ifstream inFile(filename);
    if(!inFile.is_open())
    {
        cout << "Error opening file" << endl;
        return false;
    }
    getline(inFile, title);
    setGraphTitle(title);
    inFile >> in;
    size = stoi(in);

    //check for valid graph size
    if(size < 5)
    {
        cout << "readGraph: Error, invalid graph size." << endl;
        return false;
    }

    //initialize graph
    cout << "read size: " << size << endl;
    newGraph(size);

    //add edges
    int v1 = 0; int v2 = 0; int weight = 0;
    while(inFile>>in)
    {
       v1 = stoi(in);
       inFile >> in;
       v2 = stoi(in);
       inFile >> in;
       weight = stoi(in);
       addEdge(v1, v2, weight);
       //cout << "read v1: " << v1 << " v2: " << v2 << " weight: " << weight << endl;
    }
    return true;
}

int graphAlgorithms::getVertexCount() const {return vertexCount;}

void graphAlgorithms::setGraphTitle(const string graphName) {title = graphName;}

string graphAlgorithms::getGraphTitle() const {return title;}

void graphAlgorithms::printMatrix() const
{
    cout << "Graph Adjacency Matrix:" << endl << "    " << "Graph Title: " << title << endl;
    //list vertices horizontally
    cout << "    ";
    for(int i = 0; i < vertexCount; i++)
        cout << setw(3) << right << i;
    cout << endl;

    //add dashed border for x axis
    cout << "    ";
    for(int i = 0; i < 3*vertexCount; i++)
        cout << "-";
    cout << endl;

    //print matrix
    for(int i = 0; i < vertexCount; i++)
    {
        cout << setw(3) << right << i << "|";

        for(int j = 0; j < vertexCount; j++)
        {
            if(graphMatrix[i][j] > 0 || i == j)
                cout << setw(3) << right << graphMatrix[i][j];
            else
                cout << setw(3) << right << "--";
        }

        cout << endl;
    }
}
