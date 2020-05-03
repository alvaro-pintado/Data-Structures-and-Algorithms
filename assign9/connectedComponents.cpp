#include "connectedComponents.h"
#include "disjointSets.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <unistd.h>
#include <sstream>

using namespace std;


connectedComponents::connectedComponents():rows(0), columns(0), threshold(0), image(NULL), disjointSets()
{
}

connectedComponents::~connectedComponents()
{

}

bool connectedComponents::readImageFile(const string filename)              //read image file
{
    ifstream inFile(filename, ios::binary);
    string in= "";
    char symbol = '\0';

    //ensure image fil is P5 format
    getline(inFile, in);
    cout << "file format: " << in << endl;
    if(in != "P5")
        return false;

    //iterate through comments
    inFile.get(symbol);
    while(symbol == '#')
    {
        getline(inFile, in);
        inFile >> symbol;
    }

    //store columns and row info
    inFile >> in;
    in = symbol + in;

    columns = stoi(in);
    inFile >> in;
    rows = stoi(in);
    cout << "image size: " << rows << "x" << columns << endl;

    //ensure pixel values are no greater than 255
    inFile >> in;
    cout << "scale: " << in << endl;
    int gScale = stoi(in);
    if(rows > MAX_SIZE || rows < MIN_SIZE || columns > MAX_SIZE || columns < MIN_SIZE || gScale > 255)
        return false;

    //create two dimensional array to store image
    image = new unsigned char*[rows];
    for(int r = 0; r < rows; r++)
    {
        image[r] = new unsigned char[columns];
    }

    //read input
    getline(inFile, in);
    for(int r = 0; r <rows; r++)
    {
        for(int c = 0; c < columns; c++)
        {
            inFile.get(symbol);
            image[r][c] = symbol;
            //cout << hex << symbol;
            //usleep(100000);
        }
        inFile.get(symbol);
    }
    cout << "file read" << endl;
    return true;
}

void connectedComponents::identify()                                            //identify the objects in an image
{
    imageSet.createSets(rows*columns);
    cout << "Total possible sets: " << imageSet.getSetCount() << endl;

    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < columns; c++)
        {
            //cout << "(" << r << "," << c << ")" << endl;
            //cout << "up" << endl;
            //up
            if(r-1 >= 0)
            {
                //if( abs(image[r][c]-image[r-1][c]) <= threshold )
                if( withinThreshold(image[r][c], image[r-1][c]) )
                {
                    int index = r*columns+c;
                    int adjIndex = (r-1)*columns+c;
                    //cout << "index: " << index << " adjIndex: " << adjIndex << endl;
                    imageSet.setUnion(index, adjIndex);
                }
            }

            //cout << "down" << endl;
            //down
            if(r+1 < rows)
            {
                if( withinThreshold(image[r][c], image[r+1][c]) )
                {
                    int index = r*columns+c;
                    int adjIndex = (r+1)*columns+c;
                    //cout << "index: " << index << " adjIndex: " << adjIndex << endl;
                    imageSet.setUnion(index, adjIndex);
                }
            }

            //cout << "left" << endl;
            //left
            if(c-1 >= 0)
            {
                if( withinThreshold(image[r][c], image[r][c-1]) )
                {
                    int index = r*columns+c;
                    int adjIndex = r*columns+(c-1);
                    //cout << "index: " << index << " adjIndex: " << adjIndex << endl;
                    imageSet.setUnion(index, adjIndex);
                }
            }

            //cout << "right" << endl;
            //right
            if(c+1 < columns)
            {
                if( withinThreshold(image[r][c], image[r][c+1]) )
                {
                    int index = r*columns+c;
                    int adjIndex = r*columns+(c+1);
                    //cout << "index: " << index << " adjIndex: " << adjIndex << endl;
                    imageSet.setUnion(index, adjIndex);
                }
            }
        }
    }
}

void connectedComponents::fillComponent(const int fillValue)
{
    int first, second;
    imageSet.largestSets(first, second);

    int i = 0;
    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < columns; c++)
        {
            if(imageSet.setFind(i) == setFind(second))
                image[r][c] = fillValue;
            i++;
        }
    }

}

bool connectedComponents::writeImageFile(const string filename)
{
    ofstream outFile(filename, ios::binary);
    outFile << "P5" << endl;
    outFile << columns << " " << rows << endl;
    outFile << 255 << endl;
    char output = '\0';

    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < columns; c++)
        {
            output = image[r][c];
            outFile << output;
        }
        outFile << endl;
    }
    outFile.close();
    return true;
}

void connectedComponents::setThreshold(const int value)
{
    if(value <= 255 && value >= 0)
        threshold = value;
    else
        return;
}

void connectedComponents::showStatus() const
{

}

bool connectedComponents::withinThreshold(const unsigned char a, const unsigned char b) const
{

    int inta, intb;
    stringstream ss;
    ss << hex << a;
    ss >> inta;
    ss << hex << b;
    ss >> intb;

    inta = static_cast<int>(inta);
    intb = static_cast<int>(intb);

    if( abs(inta-intb) <= threshold )
       return true;
    else
        return false;

}

int calcIndex()
{

}
