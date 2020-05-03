#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include <cstddef>

template <class myType> struct nodeType {
    myType item;
    nodeType<myType> *link;
};


template <class myType>
class linkedStack
{
    public:

        linkedStack(); // constructor
        ~linkedStack(); // destructor
        bool isEmpty();
        int getStackCount();
        void push(const myType &newItem);
        myType pop();



    private:
        nodeType<myType>* stackTop;
        int itemCount;
};

#endif // LINKEDSTACK_H

#include <cstddef>
#include <iostream>

using namespace std;

template <class myType>
linkedStack<myType>::linkedStack()
{
    stackTop = NULL;
    itemCount = 0;
}

template <class myType>
linkedStack<myType>::~linkedStack()
{
   nodeType<myType>* deleteNode;
   for(deleteNode = stackTop;stackTop;deleteNode = stackTop)
   {
       stackTop = stackTop->link;
       delete deleteNode;
   }
}

template <class myType>
bool linkedStack<myType>::isEmpty()
{
    if(stackTop == NULL)
        return true;
    else
        return false;
}

template <class myType>
int linkedStack<myType>::getStackCount()
{
    return itemCount;
}

template <class myType>
void linkedStack<myType>::push(const myType &newItem)
{
    nodeType<myType> *pushNode = new nodeType<myType>;
    pushNode->item = newItem;
    pushNode->link = stackTop;
    stackTop = pushNode;
    itemCount++;
}

template <class myType>
myType linkedStack<myType>::pop()
{
    if(itemCount>0)
    {
        myType poppedNode = stackTop->item;
        stackTop = stackTop->link;
        itemCount--;
        return poppedNode;
    }
    else
        return 0;
}
