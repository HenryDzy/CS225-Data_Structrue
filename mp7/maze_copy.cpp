/* Your code here! */
#include <iostream>
#include <algorithm>
#include <queue>
#include "maze.h"
#include "dsets.h"
#include <vector>
#include <sys/time.h> 
#include <time.h>
#include <math.h>
#include <cstdlib>
#include "cs225/PNG.h"

using namespace cs225;
using namespace std;

/**
 * No-parameter constructor
 *
 * Create an empty maze
 **/
SquareMaze::SquareMaze():width(0),height(0)
{
    //nothing
}

/**
 * Makes a new SquareMaze of the given height and width
 * if this object already represents a maze it will clear 
 * all the existing data before doing so
 * 
 * @param width teh width of the SquareMaze(number of cells)
 * @param height the height of the SquareMaze(number of cells)
 *
 **/
void SquareMaze::makeMaze(int width, int height)
{
    if(this->width != 0){       // if object exists
        for(int i=0; i<size; i++){
            delete mazes[i]; //delete each maze
        }
        delete[] mazes; //delete the maze list
    }

    //initialize
    this->width = width;    
    this->height = height;
    size = width*height;
    mazes = new maze*[width];
    for(int i=0;i < width; i++){   //allocate each maze pointer
        mazes[i] = new maze[height];
    }


    DisjointSets dset;
    dset.addelements(size);
    int r;
    vector<int> loc_arr;
    
    for(int i=0; i < width ; i++){  
        for(int j=0; j< height; j++){
            mazes[i][j].x = i;  //initialize each maze of mazes
            mazes[i][j].y = j;

            loc_arr.push_back(j*width + i); //store each maze's location
        }
    }

    struct timeval time;    //random generation
    gettimeofday(&time, NULL);
    srand((time.tv_sec * 1000)+(time.tv_usec / 1000));
    random_shuffle(loc_arr.begin(), loc_arr.end());

    int temp = loc_arr[0];
    int current_x, current_y;
    for(unsigned i=0; i < loc_arr.size(); i++){
        current_x  = loc_arr[i] % width;
        current_y = loc_arr[i] / width;
        //delete right wall if possible
        if (current_x < (width - 1) && dset.find(current_y * width + current_x) != dset.find(current_y * width + current_x + 1)) {
            mazes[current_x][current_y].right = false;
            dset.setunion(current_y * width + current_x, current_y * width + current_x + 1);
        }

        // delete bottom wall if possible
        if (current_y < (height - 1) && dset.find(current_y * width + current_x) != dset.find((current_y + 1) * width + current_x)) {
            mazes[current_x][current_y].down = false;
            dset.setunion(current_y * width + current_x, (current_y + 1) * width + current_x);
        }
    }
}

/**
 * This uses representation of the maze to determine whether
 * it is possible to travel in the given direction
 * 
 * @param x the x coordinate of the current cell
 * @param y the y coordinate of the current cell
 * @param dir the desired direction to move from the current cell
 *
 * @returns whether you can travel in the specified direction
 **/
bool SquareMaze::canTravel(int x, int y, int dir) const
{
    //check each direction
    if (dir == 0){
        if (!mazes[x][y].right)
        return true;
    }

    if (dir == 1){
        if (!mazes[x][y].down)
        return true;
    }

    if (dir == 2 && x-1 >= 0){
        if (!mazes[x-1][y].right)
        return true;
    }

    if (dir == 3 && y-1 >= 0){
        if (!mazes[x][y-1].down)
        return true;
    }
    return false;
}

/**
 * This uses representation of the maze to determine whether
 * it is possible to travel in the given direction
 * 
 * @param x the x coordinate of the current cell
 * @param y the y coordinate of the current cell
 * @param dir the desired direction to move from the current cell
 * @param exists
 * 
 **/
void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
    if (dir == 0){
        mazes[x][y].right = exists;
    }
    if(dir == 1){
        mazes[x][y].down = exists;
    }
    return;
}

/**
 * This uses representation of the maze to determine whether
 * it is possible to travel in the given direction
 * Using BFS method!
 * 
 * @return a vector of maze solution
 **/
vector<int> SquareMaze::solveMaze()
{
    //initialization
    queue<maze> q; //queue of maze, used for BFS
    vector<maze> parent;
    vector<int> bottomRow;
    vector<int> ret;
    maze curr;
    int x = 0;
    int y = 0;
    int dist = 0;
    bool** visited = new bool*[width];

    bottomRow.reserve(width);
    parent.reserve(width*height);
    for (int i = 0; i < width; i++) {
        visited[i] = new bool[height];
        for(int j=0; j < height; j++){
            visited[i][j] = false;
        }
    }

    //push the starting maze onto queue and mark as visisted
    q.push(mazes[0][0]);
    visited[0][0] = true;

    //BFS traversal
    while (!q.empty()) {
        curr = q.front();
        q.pop();
        x = curr.x;
        y = curr.y;

        //check if it is the bottom line
        if (y == (height - 1)){
            bottomRow[x] = dist;
        }
        //check right
        if (canTravel(x, y, 0) && !visited[x + 1][y]){
            q.push(mazes[x + 1][y]);
            visited[x + 1][y] = true;
            parent[y * width + x + 1] = curr;
        }
        //check bottom
        if (canTravel(x, y, 1) && !visited[x][y + 1]) {
            q.push(mazes[x][y + 1]);
            visited[x][y + 1] = true;
            parent[(y + 1) * width + x] = curr;
        }
        //check left
        if (canTravel(x, y, 2) && !visited[x-1][y]) {
            q.push(mazes[x-1][y]);
            visited[x-1][y] = true;
            parent[y*width + x-1] = curr;
        }   
        //check up
        if (canTravel(x, y, 3) && !visited[x][y-1]) {
            q.push(mazes[x][y - 1]);
            visited[x][y - 1] = true;
            parent[(y - 1) * width + x] = curr;
        }
        //increase distance
        dist++;
    }

    int maxDist = 0;
    int destX;
    //find which maze in the bottom row is furthest from origin
    for(int i=0;i < width;i++) {
        if(bottomRow[i] > maxDist) {
            maxDist = bottomRow[i];
            destX = i;
        }
    }

    end = mazes[destX][height-1];
    curr = end;
    maze par;
    int dir;

    // use parent vector to back from dest
    while(!(curr.x == 0 && curr.y == 0)) {
        par = parent[(curr.y) * width + curr.x];

        if (par.x == curr.x) {
            if (par.y + 1 == curr.y)
                dir = 1;

            if (par.y - 1 == curr.y)
                dir = 3;
        }

        if (par.y == curr.y) {
            if (par.x + 1 == curr.x)
                dir = 0;

            if (par.x - 1 == curr.x)
                dir = 2;
        }

        ret.insert(ret.begin(), dir);
        curr = par;
    }

    //release memory
    for(int i = 0; i < width; i++){
        delete visited[i];
    }
    delete[] visited;

    return ret;    
}

/**
 * Draws the maze without the solution
 * 
 * @return a pointer to the maze PNG
 **/
PNG* SquareMaze::drawMaze() const
{
    //allocate the memory
    PNG* ret = new PNG(width * 10 + 1, height * 10 + 1);

    //draw the boarder
    for (unsigned i=0;i < ret->width();){
        ret->getPixel(i, 0)->l = 0;
        i++;
    }
    
    for (unsigned i=0;i < ret->height();){
        ret->getPixel(0, i)->l = 0;
        i++;
    }

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (mazes[i][j].right){
                for(int k = 0; k <= 10; k++){
                    ret->getPixel((i + 1) * 10, j * 10 + k)->l = 0;
                }
            }

            if (mazes[i][j].down){
                for (int k = 0; k <= 10; k++){
                ret->getPixel(i * 10 + k, (j + 1) * 10)->l = 0;
                }
            }
        }
    }

    return ret;
}

/**
 * Draws the maze with the solution
 * 
 * @return a pointer to the solution maze PNG
 **/
PNG* SquareMaze::drawMazeWithSolution()
{
    //first draw the raw png
    PNG *ret = drawMaze();
    vector<int> path = solveMaze(); //get the solution

    HSLAPixel red (0,1,0.5,1);
    //set the line position
    int currx = 5;
    int curry = 5;
    int counter; //set path length counter

    for (unsigned i = 0; i < path.size(); i++) {

        counter = 0;
        //iterate through each direction
        if (path[i] == 0) {
            while (counter < 10) {
                *ret->getPixel(currx + counter, curry) = red;
                counter++;
            }

            currx += counter;
        }

        else if (path[i] == 1) {
            while (counter < 10) {
                *ret->getPixel(currx, curry + counter) = red;
                counter++;
            }
            
            curry += counter;
        }

        else if (path[i] == 2) {
            while (counter < 10) {
                *ret->getPixel(currx - counter, curry) = red;
                counter++;
            }

            currx -= counter;
        }

        else if (path[i] == 3) {
            while (counter < 10) {
                *ret->getPixel(currx, curry - counter) = red;
                counter++;
            }

            curry -= counter;
        }
    }

    *ret->getPixel(currx, curry) = red;

    end.down = false;
    mazes[end.x][end.y].down = false;
    //set the exit
    for (int k = 1; k <= 9; k++) {
        ret->getPixel(end.x * 10 + k, (end.y + 1) * 10)->l = 1.0;
    }

    return ret;
}