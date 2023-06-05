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

ImageTraversal::Iterator::~Iterator(){
  delete t_;
  t_ = NULL;
  check_finish = true;
}

ImageTraversal::~ImageTraversal(){
  //Nothing
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
  HSLAPixel start_pixel = *t_->getPNG()->getPixel(begin_point.x, begin_point.y);
  HSLAPixel neighbour_pixel;
  t_->setVisited(curr_point.x, curr_point.y);

  Point* right_point = new Point(curr_point.x+1, curr_point.y);
  Point* down_point = new Point(curr_point.x, curr_point.y+1);
  Point* left_point = new Point(curr_point.x-1, curr_point.y);
  Point* up_point = new Point(curr_point.x, curr_point.y-1);

  if(t_->getPNG()->width()> right_point->x){
    neighbour_pixel = *t_->getPNG()->getPixel(curr_point.x+1, curr_point.y);
    delta = calculateDelta(start_pixel, neighbour_pixel);
    if (delta < t_->getTolerance()){
      t_->add(*right_point);
    }
  }

  if(t_->getPNG()->height()> down_point->y){
    neighbour_pixel = *t_->getPNG()->getPixel(curr_point.x, curr_point.y+1);
    delta = calculateDelta(start_pixel, neighbour_pixel);
    if (delta < t_->getTolerance()){
      t_->add(*down_point);
    }
  }

  if(t_->getPNG()->width()> left_point->x){
    neighbour_pixel = *t_->getPNG()->getPixel(curr_point.x-1, curr_point.y);
    delta = calculateDelta(start_pixel, neighbour_pixel);
    if (delta < t_->getTolerance()){
      t_->add(*left_point);
    }
  }

  if(t_->getPNG()->height() > up_point->y){
    neighbour_pixel = *t_->getPNG()->getPixel(curr_point.x, curr_point.y-1);
    delta = calculateDelta(start_pixel, neighbour_pixel);
    if (delta < t_->getTolerance()){
      t_->add(*up_point);
    }
  }
  
  //change!!!!!!!!!!!
  if(!t_->empty()){
    while(t_->checkVisited(t_->peek().x, t_->peek().y)){
      t_->pop();
      if(t_->empty()){break;}
    }
  }
  if (t_->empty()){
    check_finish = true;
  }
  else{
    curr = t_->peek();
  }

  // const int dx[4] ={1, 0, -1, 0};
  // const int dy[4] = {0,1,0,-1};
  // if(!this->t_->empty()){
  //   this->curr = this->t_->pop();
  //   t_->setVisited(curr.x, curr.y);
  //   for(int i=0; i<4;i++){
  //     Point newp(curr.x+dx[i],curr.y+dy[i]);
  //     if(newp.x == curr.x+dx[i] && newp.y == curr.y+dy[i]){
  //       this->t_->add(newp);
  //     }
  //   }
  //   while((!this->t_->empty())){
  //     this->t_->pop();
  //     if(!this->t_->empty()) this->curr = this->t_->peek();
  //   }
  // }
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

Point ImageTraversal::Iterator::getCurr(){
  return curr;
}

// bool ImageTraversal::Iterator::isLegal(const Point & p) const{
//   if (p.x >= t_->)
// }
