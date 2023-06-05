/* Your code here! */
#ifndef _MAZE_H_
#define _MAZE_H_

#include <iostream>
#include "cs225/PNG.h"
#include "dsets.h"

using namespace cs225;
using namespace std;

class SquareMaze{
    public:
    SquareMaze();

    void makeMaze(int width, int height);

    bool canTravel(int x, int y, int dir) const;

    void setWall(int x, int y, int dir, bool exists);

    vector<int> solveMaze();
    
    PNG* drawMaze() const;

    PNG* drawMazeWithSolution();

    private:
    struct maze{
        bool right = true;
        bool down = true;
        int x;
        int y;
    };

    int width;

    int height;
    
    int size;

    maze** mazes;
    
    maze end;

};

#endif