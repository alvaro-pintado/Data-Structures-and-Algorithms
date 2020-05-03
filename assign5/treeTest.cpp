//  Main program for testing

#include <iostream>
#include <fstream>
#include <string>

#include "redBlackTree.h"

using namespace std;

int main()
{

// *****************************************************************
//  Headers...

	string	bars, stars;
	bars.append(65, '-');
	stars.append(65, '*');

	cout << bars << endl << "CS 302 - Assignment #5" << endl;
	cout << endl;

// *****************************************************************
/*  Test Tree:
			        10
			      /    \
			    6       14
			   / \     /  \
			  5   8   11  18

Results:
	Pre-order traversal:
	10  6  5  8  14  11  18
*/

	redBlackTree<int>	myTree0;

	int	arr0[] = { 10, 6, 14, 5, 8, 11, 18 };
	int	len0 = sizeof(arr0) / sizeof(arr0[1]);

	for (int i=0; i<len0; i++)
		myTree0.insert(arr0[i]);

	cout << bars << endl << "Test Set #0" << endl;
	cout << "\tNodes:  " << myTree0.countNodes() << endl;
	cout << "\tHeight: " << myTree0.height() << endl << endl;

	cout << "Pre-order traversal: " << endl;
	myTree0.printTree();

	if (!myTree0.search(5))
		cout << "main: search error" << endl;
	if (!myTree0.search(14))
		cout << "main: search error" << endl;
	if (myTree0.search(42))
		cout << "main: search error" << endl;

    cout << endl << "\tdeleting tree..." << endl;

	myTree0.destroyTree();

    cout << "Printing empty tree" << endl;
	myTree0.printTree();

	if (myTree0.search(5))
		cout << "main: destroy tree error" << endl;
	if (myTree0.search(14))
		cout << "main: destroy tree error" << endl;


// *****************************************************************
/*  Test Tree:

Results:
	Pre-order traversal: 
	8  4  2  1  3  6  5  7  12  10  9  11  16  14  13  15
		20  18  17  19  22  21  23  24
*/

	redBlackTree<int>	myTree1;

	for (int i=1; i<=24; i++)
		myTree1.insert(i);

	cout << bars << endl << "Test Set #1" << endl;
	cout << "\tNodes:  " << myTree1.countNodes() << endl;
	cout << "\tHeight: " << myTree1.height() << endl << endl;

	cout << "Pre-order traversal: " << endl;
	myTree1.printTree();
	cout << endl;

	if (!myTree1.search(5))
		cout << "main: search error, 5" << endl;
	if (!myTree1.search(14))
		cout << "main: search error, 14" << endl;
	if (myTree1.search(42))
		cout << "main: search error, 42" << endl;


// *****************************************************************
//  Test Tree:

	redBlackTree<int>	myTree2;

	int	arr2[] = { 44, 17, 88, 32, 65, 97, 28, 54, 82,
				29, 76, 80, 3, 11, 21 };
	int	len2 = sizeof(arr2) / sizeof(arr2[1]);

	for (int i=0; i<len2; i++)
		myTree2.insert(arr2[i]);

	cout << bars << endl << "Test Set #2" << endl;
	cout << "\tNodes:  " << myTree2.countNodes() << endl;
	cout << "\tHeight: " << myTree2.height() << endl << endl;

	cout << "Pre-order traversal: " << endl;
	myTree2.printTree();
	cout << endl;

	if (myTree2.search(78))
		cout << "main: search error, 78" << endl;
	if (!myTree2.search(28))
		cout << "main: search error, 28" << endl;
	if (!myTree2.search(17))
		cout << "main: search error, 17" << endl;
	if (!myTree2.search(65))
		cout << "main: search error, 65" << endl;
	if (!myTree2.search(82))
		cout << "main: search error, 82" << endl;
	if (!myTree2.search(44))
		cout << "main: search error, 44" << endl;
	if (!myTree2.search(97))
		cout << "main: search error, 97" << endl;

// *****************************************************************
//  Large Test Tree
//	Too much to print...

	redBlackTree<int>	myTree3;

	for (int i=1; i<100000; i+=2)
		myTree3.insert(i);

	cout << bars << endl << "Test Set #3" << endl;
	cout << "\tNodes:  " << myTree3.countNodes() << endl;
	cout << "\tHeight: " << myTree3.height() << endl << endl;
	cout << "\ttoo much to print..." << endl;

	if (!myTree3.search(15))
		cout << "main: destroy tree error" << endl;
	if (!myTree3.search(99955))
		cout << "main: destroy tree error" << endl;

	cout << "\tdeleting tree..." << endl;

	myTree3.destroyTree();
	myTree3.printTree();
	cout << "\tNodes:  " << myTree3.countNodes() << endl;
	cout << "\tHeight: " << myTree3.height() << endl << endl;

	if (myTree3.search(15))
		cout << "main: destroy tree error" << endl;
	if (myTree3.search(9955))
		cout << "main: destroy tree error" << endl;


// *****************************************************************
//  All done.

	cout << bars << endl << "Game Over, thank you for playing." << endl;

	return 0;
}


