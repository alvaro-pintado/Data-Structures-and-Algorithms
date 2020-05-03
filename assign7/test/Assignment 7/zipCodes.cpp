#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "zipCodes.h"
#include <typeinfo>
#include <iomanip>
#include <algorithm>
#include <unistd.h>
#include "hashTable.h"

using namespace std;

zipCodes::zipCodes()
    :hashTable(), goodCount(0), badCount(0){}

zipCodes::~zipCodes()
{
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
        string city = "";                   //holds city
        string state = "";                  //holds state

        getline(inFile, zip);               //first time reads line of category titles to move cursor to data start
        while(inFile>>in)                   //whilst we still have data to read
        {
// ////////////////////////////gets zip //////////////////////////////////////////////////////////////////////////
            zip = "";                       //reset string to hold a new zip code

            inFile.get(in);                 //get first number in zip
            while(in != ',')                //check for numbers to ensure data being stored is the zip
            {
                zip += in;                  //store zip digit in string
                inFile.get(in);             //take in next character to check if number
            }

            zip = zip.substr(0, zip.length()-1);

            inFile.get(in);
            while(in != ',')                //skip zip code type
                inFile.get(in);
// ////////////////////////////gets city //////////////////////////////////////////////////////////////////////////
            city = "";                      //reset string to hold a new city

            inFile.get(in);                 //get first letter in city
            while(in != ',')                //check for character to ensure data being stored is the city
            {
                city += in;                 //store city letter in string
                inFile.get(in);             //take in next character to check if letter
            }
// ////////////////////////////gets state //////////////////////////////////////////////////////////////////////////
            state = "";                     //reset string to hold a new state

            inFile.get(in);                 //get first letter in state
            while(in != ',')                //check for character to ensure data being stored is the state
            {
                state += in;                //store state letter in string
                inFile.get(in);             //take in next character to check if letter
            }

           city = city.substr(1, city.length()-2);
           state = state.substr(1, state.length()-2);

           //cout << "city: " << city << " state: " << state << endl;
           //usleep(10000);
           insert(zip, city, state);      //store newly read zip code in hash table
           getline(inFile, zip);                         //read rest of useless (for now) info on line to move cursor to next zip code
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
        string city = "";
        string state = "";
        string checkCity = "";              //holds the city to be checked
        string checkState = "";             //holds the state to be checked


        getline(inFile, zip);               //reads category title line to move cursor to data start
        while(inFile>>in)                   //while there is data to process
        {
            //cout << "Reading checkfile" << endl;
            checkCity = "";                 //reset city string for new city
            checkState = "";                //reset state string for new state
            zip = "";                       //reset zip string for new zip code


            for(int i = 0; i <2; i++)       //move cursor to start of city (3rd section)
            {
                inFile.get(in);
                while(in != '|')            //new sections are denoted by '|' character
                    inFile.get(in);         //move the cursor along
            }

            inFile.get(in);
            while(in != '|')                //insert city characters until end field marker '|'
            {
                checkCity += in;
                inFile.get(in);
            }

            inFile.get(in);
            while(in != '|')                //insert state characters until end field marker '|'
            {
                checkState += in;
                inFile.get(in);
            }

            inFile.get(in);
            while(in != '\n')                //insert zip characters until end field marker '|'
            {
                zip += in;
                inFile.get(in);
            }

            transform(checkCity.begin(), checkCity.end(), checkCity.begin(), ::toupper);
            transform(checkState.begin(), checkState.end(), checkState.begin(), ::toupper);

            //cout << "checking - zip: " << zip << " city: " << checkCity << " state: " << checkState << endl;
            //usleep(50000);

           if(lookup(zip, city, state))      //search zip code to see if valid
           {
               //cout << "city returned: " << city << " " << "state returned: " << state << endl;
               transform(city.begin(), city.end(), city.begin(), ::toupper);
               transform(state.begin(), state.end(), state.begin(), ::toupper);
               //cout << "zip: " << zip << " city: " << checkCity << " state: " << checkState << endl;
               //cout << "cityMaster: " << city << " stateMaster: " << state << endl;
               //usleep(50000);

               if(city == checkCity && state == checkState)
                    goodCount++;                            //if so, increase valid zip code count
               else
                   badCount++;
           }
           else
                badCount++;                                 //if not, increase invalid zip code count
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



