#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 * 
 * @param p1 First pixel
 * @param p2 Second pixel
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );    
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  check_finish = true;
  t_ = NULL;
}

ImageTraversal::Iterator::Iterator(Point start_point, ImageTraversal* tra) {
  /** @todo [Part 1] */
  t_ = tra;
  begin_point = start_point;
  check_finish = false;
  if(!t_->empty()){
    curr = t_->peek();
  }
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  double delta;
  Point curr_point = t_->pop();
  HSLAPixel start_pixel = *t_->getPNG().getPixel(begin_point.x, begin_point.y);
  HSLAPixel neighbour_pixel;
  t_->setVisited(curr_point.x, curr_point.y);

  Point* right_point = new Point(curr_point.x+1, curr_point.y);
  Point* down_point = new Point(curr_point.x, curr_point.y+1);
  Point* left_point = new Point(curr_point.x-1, curr_point.y);
  Point* up_point = new Point(curr_point.x, curr_point.y-1);

  if(t_->getPNG().height()> right_point->x){
    neighbour_pixel = *t_->getPNG().getPixel(curr_point.x+1, curr_point.y);
    delta = calculateDelta(start_pixel, neighbour_pixel);
    if (delta < t_->getTolerance()){
      t_->add(*right_point);
    }
  }

  if(t_->getPNG().height()> down_point->y){
    neighbour_pixel = *t_->getPNG().getPixel(curr_point.x, curr_point.y+1);
    delta = calculateDelta(start_pixel, neighbour_pixel);
    if (delta < t_->getTolerance()){
      t_->add(*down_point);
    }
  }

  if(t_->getPNG().height()> left_point->x){
    neighbour_pixel = *t_->getPNG().getPixel(curr_point.x-1, curr_point.y);
    delta = calculateDelta(start_pixel, neighbour_pixel);
    if (delta < t_->getTolerance()){
      t_->add(*left_point);
    }
  }

  if(t_->getPNG().height() > up_point->y){
    neighbour_pixel = *t_->getPNG().getPixel(curr_point.x, curr_point.y-1);
    delta = calculateDelta(start_pixel, neighbour_pixel);
    if (delta < t_->getTolerance()){
      t_->add(*up_point);
    }
  }
  if(!t_->empty()){
    while(t_->checkVisited(t_->peek().x, t_->peek().y)){
      t_->pop();
      if(t_->empty()){break;}
    }
  }

  if(!t_->empty()){
    curr = t_->peek();
  }else{
    check_finish = true;
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr;
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return !(check_finish && other.check_finish);
}
