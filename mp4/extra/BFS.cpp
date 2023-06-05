
#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
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
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  BFS* bfs = new BFS(png_, start_point, tolerance_);
  return ImageTraversal::Iterator(start_point, bfs);
}


/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  points.push(point);
  return;
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point tra_point = points.front();
  points.pop();
  return tra_point;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return points.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return points.empty();
}

Point BFS::getStartPoint(){
  return start_point;
}

double BFS::getTolerance(){
  return tolerance_;
}

PNG BFS::getPNG(){
  return png_;
}

void BFS::setVisited(int x, int y){
  checked[y][x] = true;
  return;
}

bool BFS::checkVisited(int x, int y){
  return checked[y][x];
}