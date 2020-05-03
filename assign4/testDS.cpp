//  Main program for testing
//	Test the stack implementation

#include <iostream>
#include <fstream>
#include <string>

#include "linkedStack.h"

using namespace std;

int main()
{
// *****************************************************************
//  Headers...

	string	bars, stars;
	bars.append(65, '-');
	stars.append(65, '*');

	cout << bars << endl << "CS 302 - Assignment #4" << endl;
	cout << "Basic Testing for Linked Stack " <<
		"Data Structure" << endl;

// *****************************************************************
//  Basic tests for linked stack implementation.
//	Reservse number in a list by pushing each item on stack and then poping.

	cout << endl << stars << endl << "Test Stack Operations "
				"- Reversing:" << endl << endl;

// ---------------------
//  Integers

	linkedStack<int> iStack;
	int	inums[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
	int	ilen = ( sizeof(inums) / sizeof(inums[0]) );
	int	iTmp;

	linkedStack<int> iStackA;

	if (!iStack.isEmpty())
		cout << "Error, invalid stack." << endl;

	cout << "Original List:     ";
	for (int i=0; i<ilen; i++) {
		iStack.push(inums[i]);
		cout << inums[i] << " ";
	}

	cout << endl << "Reverse List:      ";
	for (int i=0; i<ilen; i++) {
		iTmp = iStack.pop();
		cout << iTmp << " ";
		iStackA.push(iTmp);
	}

	cout << endl << "Copy A (original): ";
	for (int i=0; i<ilen; i++)
		cout << iStackA.pop() << " ";

	cout << endl << endl;

// ---------------------
//  Doubles
//	Create some stacks for doubles.

	linkedStack<double> dstack;
	linkedStack<double> dstackA;
	
	double	dnums[] = {1.1, 3.3, 5.5, 7.7, 9.9, 11.11, 13.13, 15.15};
	int	dlen = ( sizeof(dnums) / sizeof(dnums[0]) );
	double	dTmp;

	dstack.push(1000.0);

	cout << bars << endl << "Test Stack Operations " <<
			"- Doubles:" << endl << endl;

	cout << "Original List:     ";
	for (int i=0; i<dlen; i++) {
		dstack.push(dnums[i]);
		cout << dnums[i] << " ";
	}

	cout << endl << "Reverse List:      ";
	for (int i=0; i<dlen; i++) {
		dTmp = dstack.pop();
		cout << dTmp << " ";
		dstackA.push(dTmp);
	}

	cout << endl << "Copy A (original): ";
	for (int i=0; i<dlen; i++) {
		cout << dstackA.pop() << " ";
	}

	cout << endl << endl;

// --------------------------------------
//  Multiple links testing
//	Insert 303 items, should be 4 links...

	cout << bars << endl << "Test Stack Operations " <<
			"- Multiple Links Test:" << endl << endl;

	linkedStack<short> mStack;
	int	testSize1=303;
	bool	workedStk1 = true;

	for (int i=1; i<=testSize1; i++)
    {
        //cout << "Pushing: " << i+100 << endl;
		mStack.push(static_cast<short>(i+100));
    }

	if (mStack.getStackCount() != testSize1)
		cout << "main: error, incorrect stack size." << endl;

	cout << "Stack Element Count: " << mStack.getStackCount() << endl;
	cout << endl;

	for (int i=testSize1; i>0; i--) {
		if (mStack.pop() != static_cast<short>(i+100))
			workedStk1 = false;
	}
	if (mStack.getStackCount() != 0)
		workedStk1 = false;

	if (workedStk1)
		cout << "Multiple items, test passed." << endl;
	else
		cout << "Multiple items, test failed." << endl;

	cout << endl;

// --------------------------------------
//  Many entries testing

	cout << bars << endl << "Test Stack Operations " <<
			"- Many Items:" << endl << endl;
	bool	workedStk2 = true;

	linkedStack<int> iStackBig;
	int	testSize2=400000;

	for (int i=1; i<=testSize2; i++)
		iStackBig.push(i);

	if (iStackBig.getStackCount() != testSize2)
		cout << "main: error, incorrect stack size." << endl;

	cout << "Stack Element Count: " << iStackBig.getStackCount() << endl;
	cout << endl;

	for (int i=testSize2; i>0 ; i--) {
		if (iStackBig.pop() != i)
			workedStk2 = false;
	}
	if (iStackBig.getStackCount() != 0)
		workedStk2 = false;

	if (workedStk2)
		cout << "Many items, test passed." << endl;
	else
		cout << "Many items, test failed." << endl;

	cout << endl;


// *****************************************************************
//  All done.

	cout << bars << endl << "Game Over, thank you for playing." << endl;

	return 0;
}


