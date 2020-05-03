#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

enum nodeColor { RED, BLACK };

template <class myType>
struct nodeType {
    myType keyValue;
    nodeColor color;
    nodeType<myType>  *left;
    nodeType<myType>  *right;
    nodeType<myType>  *parent;
};

template <class myType>
class redBlackTree
{
public:
    redBlackTree();
    ~redBlackTree();
    void destroyTree();
    unsigned int countNodes() const;
    unsigned int height() const;
    void printTree() const;
    void insert(myType);
    bool search(myType);


private:
    nodeType<myType> *root;

    bool search(myType, nodeType<myType>*);
    void destroyTree(nodeType<myType>*);
    unsigned int countNodes(nodeType<myType>*) const;
    unsigned int height(nodeType<myType>*) const;
    void printTree(nodeType<myType>*) const;
    void rightRotate(nodeType<myType>*);
    void leftRotate(nodeType<myType>*);
};

#include <cstdlib>
#include <iostream>

using namespace std;

template <class myType>
redBlackTree<myType>::redBlackTree()
{
    root = NULL;
}

template <class myType>
redBlackTree<myType>::~redBlackTree() {destroyTree();}

template <class myType>
void redBlackTree<myType>::destroyTree() {destroyTree(root); root = NULL;}

template <class myType>
void redBlackTree<myType>::destroyTree(nodeType<myType>* nd)
{
    if(nd != NULL)
    {
        destroyTree(nd->left);
        destroyTree(nd->right);
        nd->left = NULL;
        nd->right = NULL;
        delete nd;
        nd = NULL;
    }
    return;
}

template <class myType>
unsigned int redBlackTree<myType>::countNodes() const {return countNodes(root);}

template <class myType>
unsigned int redBlackTree<myType>::countNodes(nodeType<myType>* nd) const
{
    int count = 0;
    if(nd != NULL)
    {
        count += 1;
        count += countNodes(nd->left);
        count += countNodes(nd->right);
    }
    return count;
}

template <class myType>
unsigned int redBlackTree<myType>::height() const {return height(root);}

template <class myType>
unsigned int redBlackTree<myType>::height(nodeType<myType>* nd) const
{
    int h = 1;
    if(nd  == NULL)
        return 0;
    else if(height(nd->left) >= height(nd->right))
        return h + height(nd->left);
    else
        return h + height(nd->right);
}

template <class myType>
void redBlackTree<myType>::printTree() const {printTree(root); cout << endl;}

template <class myType>
void redBlackTree<myType>::printTree(nodeType<myType>* nd) const
{
   if(nd != NULL)
   {
       cout << nd->keyValue << " ";
       printTree(nd->left);
       printTree(nd->right);
   }

   else
       return;
}

template <class myType>
bool redBlackTree<myType>::search(myType key)
{
     if(root != NULL)
        return search(key, root);
     else
         return false;
}

template <class myType>
bool redBlackTree<myType>::search(myType key, nodeType<myType>* nd)
{
    if(nd != NULL)
    {
        if(nd->keyValue == key)
            return true;
        else if(key < nd->keyValue)
            return search(key, nd->left);
        else if(key > nd->keyValue)
            return search(key, nd->right);
    }

    return false;
}

template <class myType>
void redBlackTree<myType>::insert(myType key)
{
    //search to see if node already exists
    if(search(key))
        return;

    //create node
    nodeType<myType>* x = new nodeType<myType>;
    x->parent = NULL;
    x->left = NULL;
    x->right = NULL;
    x->keyValue = key;
    x->color = RED;

    //check to see if tree is empty
    if(root == NULL)
    {
        root = x;
        x->color = BLACK;
        return;
    }

    //insert node if above are false
    nodeType<myType>* curr = root;
    char lastDir;
    while(curr != NULL)
    {
        if(curr->keyValue > key)
        {
            x->parent = curr;
            lastDir = 'l';
            curr = curr->left;
        }

        else if(curr->keyValue < key)
        {
            x->parent = curr;
            lastDir = 'r';
            curr = curr->right;
        }
    }

    if(lastDir == 'l')
        x->parent->left = x;
    else
        x->parent->right = x;

// /*
    while(x != root && x->parent->color == RED)
    {
        if(x->parent == x->parent->parent->left)
        {
            if(x->parent->parent->right != NULL && x->parent->parent->right->color == RED)
            {
                x->parent->color = BLACK;
                x->parent->parent->right->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }

            else
            {
                if(x == x->parent->right)
                {
                    x = x->parent;
                    leftRotate(x);
                }

                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rightRotate(x->parent->parent);
            }

        }

        else
        {
            if(x->parent->parent->left != NULL && x->parent->parent->left->color == RED)
            {
                x->parent->color = BLACK;
                x->parent->parent->left->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }

            else
            {
                if(x == x->parent->left)
                {
                    x = x->parent;
                    rightRotate(x);
                }

                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                leftRotate(x->parent->parent);
            }
        }

        if(x == root)
            root->color = BLACK;

    } // */
}

template <class myType>
void redBlackTree<myType>::leftRotate(nodeType<myType>* x)
{
    nodeType<myType>* y  = x->right;
    x->right = y->left;

    if(x->right != NULL)
        x->right->parent = x;

    y->parent = x->parent;

    if(x->parent == NULL)
        root = y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right=y;
    y->left = x;
    x->parent = y;
}

template <class myType>
void redBlackTree<myType>::rightRotate(nodeType<myType>* y)
{
    nodeType<myType>* x = y->left;
    y->left = x->right;

    if(x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if(x->parent == NULL)
        root = x;
    else if(y == y->parent->left)
        y->parent->left=x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;

}

#endif
