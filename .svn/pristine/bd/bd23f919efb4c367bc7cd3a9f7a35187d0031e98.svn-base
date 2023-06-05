#ifndef DFS_H
#define DFS_H

#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A depth-first ImageTraversal.
 */
class DFS : public ImageTraversal {
public:
  DFS(const PNG & png, const Point & start, double tolerance);

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
  stack<Point> points; 
  PNG png_;
  Point start_point;
  double tolerance_;
};

#endif
