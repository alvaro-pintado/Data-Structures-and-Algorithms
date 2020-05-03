#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <string>

using namespace std;

template <class myType>
struct heapNode
{
    unsigned long long priority;
    myType item;
};

template <class myType>
class priorityQueue
{
public:
    priorityQueue(int);                                             //constructor
    ~priorityQueue();                                               //destructor
    int entries() const;                                            //returns entry count
    void insert(const myType, const unsigned long long);            //inserts node into heap, resizing if needed, and rebuilding for property maintenance
    bool deleteMin(myType &, unsigned long long &);                 //deletes minimum priority in heap
    bool isEmpty() const;                                           //checks if heap is empty
    void printHeap() const;                                         //prints heap by minimum priority
    bool readData(const string);                                    //


private:
    int count;
    int heapSize;
    int resizes;
    heapNode<myType>* myHeap;

    void reheapUp(int);
    void reheapDown(int);
    void buildHeap();
    void resize();

};

#endif

#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

template <class myType>
priorityQueue<myType>::priorityQueue(int size = 5000):heapSize(5000), count(0), resizes(0)             //constructor
{
    if(size > 5000)                                                                     //if passed value is greater than 5000 (default), set size to passed value
        heapSize = size;
    myHeap = new heapNode<myType>[heapSize];                                                      //dynamically allocate array space for heap

}

template <class myType>
priorityQueue<myType>::~priorityQueue()                                             //destructor
{
    delete []myHeap;                                                                    //delete heap array
}

template <class myType>
int priorityQueue<myType>::entries() const
{
    return count;
}

template <class myType>
void priorityQueue<myType>::insert(const myType item, const unsigned long long pValue)//inserts node into heap with passed priority value and passed item
{
    count++;                                                                              //increment count
    myHeap[count].item = item;                                                          //set the empty spot to the passed node value
    myHeap[count].priority = pValue;                                                    //set the priority of that node to the passed priority value
    if(count+1 == heapSize)                                                                 //if the heap is full, resize
        resize();
    reheapUp(count);                                                                      //apply the order property to newly inserted node
}

template <class myType>
void priorityQueue<myType>::buildHeap()                                             //applies structure and order property to heap
{
    int startIndex = count/2;                                                             //start applying the order property at the second-to-last layer's right most node

    for(int i = startIndex; i > 0; i--)                                                   //for each node from there on up, apply the order property via reheapDown()
        reheapDown(i);
}

template <class myType>
bool priorityQueue<myType>::isEmpty() const                                               //returns true if empty, false otherwise
{
    if(count == 0)
        return true;
    else
        return false;
}

template <class myType>
bool priorityQueue<myType>::deleteMin(myType &item, unsigned long long &pValue)      //deletes min from heap
{
    if(!isEmpty())                                                                            //check for empty heap
    {
        pValue = myHeap[1].priority;
        item = myHeap[1].item;
        myHeap[1] = myHeap[count];                                                          //set last node to first node (i.e deleting the min)
        count--;                                                                            //decrement count
        reheapDown(1);                                                                      //apply the order property to the first node via reheapDown()
        return true;
    }

    else
        return false;
}

template <class myType>
void priorityQueue<myType>::printHeap() const                                      //prints heap layer-by-layer
{
    for(int i = 1; i < count+1; i++)                                                        //iterate through heap
    {
        bool isPow2 = !(i & (i-1));

        if( isPow2)                                                         //if node index is a power of 2, i.e a new layer, start a new line
            cout << endl;
        cout << myHeap[i].item << " " << myHeap[i].priority << endl;                        //print out item and priority value
    }
}

template <class myType>
bool priorityQueue<myType>::readData(const string filename)                         //reads data fromm file and places into heap, (linear time algorithm)
{
    ifstream inFile(filename);

    if(inFile.is_open())                                                                    //check if file is opened
    {
        char in = '\0';                                                                       //cursor
        string item = "";                                                                   //variable to hold item
        string pValue = "";                                                                 //variable to hold priority string

        inFile.get(in);
        while(inFile>>in)
        {
            string item = "";                                                                   //reset item
            string pValue = "";                                                                 //reset priority value

            inFile >> item >> pValue;

            count++;
            //cout << "read: " << item << " & " << pValue << endl;
            myHeap[count].item = item;                                                      //store item in next heap node
            myHeap[count].priority = stoi(pValue);                                          //convert priority value string into numberical value and store
            //cout << "count = " << count << endl;
            if(count+1 == heapSize)                                                           //check if heap is full
                resize();

        }

        buildHeap();                                                                        //apply order property to heap

        return true;
    }

    else
        return false;


}

template <class myType>
void priorityQueue<myType>::reheapUp(int current)                                     //moves node up if needed
{
    int parent = current/2;                                                                 //index of parent of current
    if(current == 1)                                                                        //if node is root, return
        return;

    else if(myHeap[parent].priority > myHeap[current].priority)                             //if the parent is bigger (min heap)
    {
        swap(myHeap[parent], myHeap[current]);                                              //swap current and parent
        //reheapDown(current);                                                                //check if swapped node (parent) is correctly in place
        reheapUp(parent);                                                                   //recursively call itself to check if more "bubbling up" is needed
        return;
    }

    else                                                                                    //else the node is in the correct order
        return;
}

template <class myType>
void priorityQueue<myType>::reheapDown(int current)                                   //moves node down if needed
{
    if(current > count/2)                                                                    //if the node is in the last layer, return
        return;
    else
    {
        int lChild = current*2;
        int rChild = (current*2)+1;

        if(myHeap[lChild].priority < myHeap[rChild].priority)                               //if left child is less than right
        {
            if(myHeap[lChild].priority < myHeap[current].priority)                          //and left child is less than current (parent)
            {
                swap(myHeap[lChild], myHeap[current]);                                      //swap left child and current
                reheapDown(lChild);
                //reheapUp(current);                                                          //check if swapped node is correctly in place
                return;
            }

            else
                return;
        }

        else                                                                                //if right child is less than less
        {
            if(myHeap[rChild].priority < myHeap[current].priority)                          //and right child is less than current (parent)
            {
                swap(myHeap[rChild], myHeap[current]);                                      //swap right child and current
                reheapDown(rChild);
                //reheapUp(current);                                                          //check if swapped node is correctly in place
                return;
            }

            else
                return;
        }
    }
}

template <class myType>
void priorityQueue<myType>::resize()
{
    //resizes++;
    //cout << "resize #" << resizes << endl;
    heapNode<myType>* oldHeap = myHeap;
    myHeap = new heapNode<myType>[heapSize*2];
    int oldCount = count;
    count = 0;

    heapSize = heapSize*2;
    for(int i = 1; i < oldCount+1; i++)
        insert(oldHeap[i].item, oldHeap[i].priority);

    //cout << "done resizing" << endl;
}
