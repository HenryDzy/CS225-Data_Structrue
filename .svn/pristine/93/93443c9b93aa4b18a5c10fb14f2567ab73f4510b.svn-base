#ifndef BFS_H
#define BFS_H

#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();
  
  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;

  Point getStartPoint();
  double getTolerance();
  PNG getPNG();
  
  void setVisited(int x, int y);
  bool checkVisited(int x, int y);
private:
  vector<vector<bool>> checked;
  queue<Point> points; 
  PNG png_;
  Point start_point;
  double tolerance_;
};
#endif
