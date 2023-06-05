#include "Image.h"
#include "StickerSheet.h"
#include "./cs225/PNG.h"
#include "./cs225/HSLAPixel.h"
#include <iostream>

using namespace cs225;
using namespace std;

int main() {
  Image alma, melt, thumb, fist;
  alma.readFromFile("alma.png");
  melt.readFromFile("melting_face_3d.png");
  thumb.readFromFile("thumbs_up_3d_default.png");
  fist.readFromFile("left-facing_fist_3d_default.png");
  melt.scale(0.23);
  thumb.scale(0.15);
  fist.scale(0.15);
  StickerSheet myImage(alma, 5);
  myImage.addSticker(melt, alma.width()/2-35, alma.height()/2 - 275);
  myImage.addSticker(fist, alma.width()/2-140, alma.height()/2 - 215);
  myImage.addSticker(thumb, alma.width()/2+107, alma.height()/2 - 222);
  Image printout = myImage.render();
  printout.writeToFile("myImage.png");
  return 0;
}
