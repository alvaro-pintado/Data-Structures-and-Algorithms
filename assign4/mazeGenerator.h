#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include <string>

using namespace std;

class mazeGenerator
{

    public:
        mazeGenerator(int, int);
        ~mazeGenerator();
        void createMaze();
        bool printWalls(const string);
        void printMaze();


    private:
        int height;
        int width;
        char** maze;
        int** walls;
        static const int MIN_SIZE = 5;
        static const int MAX_SIZE = 1000;


};

#endif

