#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

using namespace std;
/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance){  
  /** @todo [Part 1] */
  add(start);
  checked.resize(png.height());
  for(unsigned int i = 0; i<png.height(); i++){
    checked[i].resize(png.width());
    unsigned int j=0;
    for(; j<png.width(); j++){
      checked[i][j] = false;
    }
  }
  checked[start.y][start.x] = true;
  png_ = png;
  start_point = start;
  tolerance_ = tolerance;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  DFS* dfs = new DFS(png_, start_point, tolerance_);
  return ImageTraversal::Iterator(start_point, dfs);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  points.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point tra_point = points.top();
  points.pop();
  return tra_point;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return points.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return points.empty();
}

Point DFS::getStartPoint(){
  return start_point;
}

double DFS::getTolerance(){
  return tolerance_;
}

PNG DFS::getPNG(){
  return png_;
}

void DFS::setVisited(int x, int y){
  checked[y][x] = true;
  return;
}

bool DFS::checkVisited(int x, int y){
  return checked[y][x];
}
