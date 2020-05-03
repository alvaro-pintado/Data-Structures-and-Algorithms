#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "redBlackTree.h"
#include "zipCodes.h"
#include <typeinfo>

using namespace std;

zipCodes::zipCodes()
    :goodCount(0), badCount(0){}

zipCodes::~zipCodes()
{
    masterZipCodes.destroyTree();
    goodCount = 0;
    badCount = 0;
}

bool zipCodes::readMasterZipCodes(const string masterFile)
{
    ifstream inFile(masterFile);

    if(inFile.is_open())
    {

        char in = '\0';                     //holds zip code digits
        string zip = "";                    //holds zip code

        getline(inFile, zip);               //first time reads line of category titles to move cursor to data start
        while(inFile>>in)                   //whilst we still have data to read
        {
            zip = "";                       //reset string to hold a new zip code

            inFile.get(in);                 //get first number in zip
            while(in != ',')                //check for numbers to ensure data being stored is the zip
            {
                zip += in;                  //store zip digit in string
                inFile.get(in);             //take in next character to check if number
            }

            zip.pop_back();

           masterZipCodes.insert(zip);      //store newly read zip code in red-black tree
           getline(inFile, zip);            //read rest of useless (for now) info on line to move cursor to next zip code
        }

       inFile.close();
       return true;
    }

    else
        return false;

}

bool zipCodes::checkZips(const string checkFile)
{
    ifstream inFile(checkFile);

    if(inFile.is_open())                    //check to see if file was opened properly
    {
        char in = '\0';                     //holds character to be checked for vertical bar
        string zip = "";                    //holds zip code to be checked

        getline(inFile, zip);               //reads category title line to move cursor to data start
        while(inFile>>in)                   //while there is data to process
        {

            zip = "";                       //reset zip string for new zip code

            for(int i = 0; i <4; i++)       //move cursor to start of zip codes (5th section)
            {
                inFile.get(in);
                while(in != '|')            //new sections are denoted by '|' character
                    inFile.get(in);         //move the cursor along
            }

            inFile.get(in);
            while(in != '\n')
            {
                zip += in;
                inFile.get(in);
            }

           if(masterZipCodes.search(zip))   //search zip code to see if valid
                goodCount++;                //if so, increase valid zip code count
           else
                badCount++;                 //if not, increase invalid zip code count
        }
        return true;
    }

    cout << "Error opening file" << endl;
    return false;
}

void zipCodes::showStats() const
{
    double total = badCount + goodCount;
    double passed = goodCount/total*100;
    double failed = badCount/total*100;

    cout << "Zip Code Validation Statistics: " << endl << endl;
    cout << "Master Zip Codes Tree Statistics: " << endl;
    cout << "    Tree Entries: " << masterZipCodes.countNodes() << endl;
    cout << "    Tree Height: " << masterZipCodes.height() << endl << endl;
    cout << "Zip Codes Data File Statistics: " << endl;
    cout << "    Total Zip Codes: " << total << endl;
    cout << "      Good: " << goodCount << endl;
    cout << "      Bad: " << badCount << endl;
    cout << "    Percentage Good: " << passed << endl;
    cout << "    Percentage Bad: " << failed << endl;

    if( passed >= 97.0)
        cout << "Validation - PASSED" << endl;
    else
        cout << "Validation - FAILED" << endl;
}



