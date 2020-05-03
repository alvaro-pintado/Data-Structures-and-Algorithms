#include <iostream>
#include <string>
#include <fstream>
#include "linkedStack.h"
#include "mazeGenerator.h"
#include <cstdlib>

using namespace std;

mazeGenerator::mazeGenerator(int h = 0, int w = 0)
{
    //checks if requested maze is within limits
    if(h < MIN_SIZE || h > MAX_SIZE ||
       w < MIN_SIZE || w > MAX_SIZE)
    {
        maze = NULL;
        walls = NULL;
    }

    else
    {

        //setting member variables
        height = h;
        width = w;
        int maxWalls = ((width-1)*height + (height-1)*width);
        int wallCount = 0;

        //creating two dimensional array
        maze = new char*[height];
        for(int row = 0; row < height; row++)
        {
            maze[row] = new char[width];
            for(int col = 0; col < width; col++)
                maze[row][col] = 'u';
        }


        //creates 2 dimensional wall array
        walls = new int*[maxWalls];
        for(int wall = 0; wall < maxWalls; wall++)
            walls[wall] = new int[2]; // 2nd dimension is wall sides


        //sets all possible walls for horizontally adjacent cells
        //creates part of all possible walls, x, x = (width-1)*height
        for(int row = 0; row < height; row++)
        {
            for(int wall = 0; wall < width-1; wall++)
            {
                //cout << "Index:  " << wallCount << << " Values: ";
                for(int side = 0; side < 2; side++)
                {
                    walls[wallCount][side] = width*row+wall+side;
                }
                wallCount++;
            }

        }


        //sets all possible walls for vertically adjacent cells
        //creates last part of all possible walls, (height-1)*width
        int vWalls = 0;
        while(wallCount < maxWalls)
        {
            for(int side = 0; side < 2; side++)
            {
                walls[wallCount][side] = vWalls+5*side;
            }
            vWalls++;
            wallCount++;
        }



    }
}

mazeGenerator::~mazeGenerator()
{
    int maxWalls = ((width-1)*height + (height-1)*width);

    for(int row = 0; row < height; row++)
    {
        delete []maze[row];
    }

    for(int wall = 0; wall < maxWalls; wall++)
        delete []walls[wall];
}

void mazeGenerator::createMaze()
{
    int maxWalls = ((width-1)*height + (height-1)*width);
    linkedStack<char*> cellStack;
    char* current, next;
    int unvisited = 0;
    char dir[4];
    int row = 0, col = 0,row2 = 0, col2 = 0;

    cellStack.push(&maze[0][0]);
    while(!cellStack.isEmpty())
    {
        //cout << "Current cell: " << row << " " << col << endl;
        current = cellStack.pop();
        maze[row][col] = 'v';
        //cout << "Current cell visit status: " << maze[row][col] << endl;
        unvisited = 0;

        //check for unvisited neighboors

        //up
        if(row-1 >= 0)
        {
            if(maze[row-1][col] == 'u')
            {
                dir[unvisited]= 'u';
                unvisited++;
            }

            else
                dir[unvisited] = '0';
        }

        //down
        if(row+1 < height)
        {
            if(maze[row+1][col] == 'u')
            {
                dir[unvisited] = 'd';
                unvisited++;
            }
            else
                dir[unvisited] = '0';
        }

        //left
        if(col-1>=0)
        {
            if(maze[row][col-1] == 'u')
            {
                dir[unvisited] = 'l';
                unvisited++;
            }
            else
                dir[unvisited] = '0';
        }

        //right
        if(col+1)
        {
            if(maze[row][col+1] == 'u')
            {
                dir[unvisited] = 'r';
                unvisited++;
            }
            else
                dir[unvisited] = '0';
        }


        //choose random unvisited neighbor
        if(unvisited > 0)
        {
            char direction = dir[rand()%unvisited];
            //for(int i = 0; i < 4; i++)
                //cout << "Neighboor: " << dir[i] << endl;
            //cout << "Direction: " << direction << endl;

            switch (direction){
            case 'u':
                row2--;
                break;
            case 'd':
                row2++;
                break;
            case 'l':
                col2--;
                break;
            case 'r':
                col2++;
                break;
            default:
                break;
            }

        //find & remove wall in between current cell and new cell
        bool wallFound = false;
        next = maze[row2][col2];
        //cout << "Next cell: " << row2 << " " << col2 << endl;
        int i = 0;
        while(!wallFound || i>=maxWalls)
        {
            if(row < row2 || col < col2)
            {
                if(walls[i][0] == row*width+col)
                {
                    if(walls[i][1] == row2*width+col2)
                    {
                        //cout << "Wall removed: " << walls[i][0] << " " << walls[i][1] << endl;
                        walls[i][0] = -1;
                        wallFound = true;
                    }
                }
            }
            else
                {
                    if(row > row2 || col > col2)
                    {
                        if(walls[i][0] == row2*width+col2)
                        {
                            if(walls[i][1] == row*width+col)
                            {
                                //cout << "Wall removed: " << walls[i][0] << " " << walls[i][1] << endl;
                                walls[i][0] = -1;
                                wallFound = true;
                            }
                        }
                    }
                }
            i++;
        }

        row = row2;
        col = col2;

        cellStack.push(&*current);
        cellStack.push(&next);

        }

    }
}

bool mazeGenerator::printWalls(const string filename)
{
    ofstream output;
    output.open(filename);
    int maxWalls = (height-1)*width + (width-1)*height;

    if(output.is_open())
    {
        output << "ROWS " << height << " COLS " << width << endl;

        for(int wall = 0; wall < (maxWalls); wall++)
        {
            if(walls[wall][0] != -1)
            {
                output << "WALL" << " ";
                for(int side = 0; side < 2; side++)
                {
                    output << walls[wall][side] << " ";
                }
                output << endl;
            }
        }
        return true;
    }
    else
        return false;
}

void mazeGenerator::printMaze()
{
    for(int row = 0; row < )
}
