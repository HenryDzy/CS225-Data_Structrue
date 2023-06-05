#include "../cs225/HSLAPixel.h"
#include "../Point.h"
#include "../cs225/PNG.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

MyColorPicker::MyColorPicker(HSLAPixel grid_color, unsigned spacing){
  this->grid_color = grid_color;
  this->spacing = spacing;
}

/**
 * Picks the color for pixel (x, y).
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  if((x + y) % spacing>=10 && (x + y) % spacing<=20){
    return grid_color;
  }

  double hue = 0;

  hue -= spacing;
  while(hue>=360) {hue -= 360;}
  HSLAPixel pixel(hue,1,0.5);
  return pixel;

  // return HSLAPixel();
}

