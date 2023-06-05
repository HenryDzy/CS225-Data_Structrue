
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  PNG png_;
  png_.readFromFile("myImage.png");
  FloodFilledImage background(png_);
  BFS bfs(png_, Point(100,100), 0.2);
  DFS dfs(png_, Point(10,10), 0.2);
  HSLAPixel c1(231, 0.5, 0.5);
  HSLAPixel c2(100, 0.3, 0.5);
  MyColorPicker cp1(c1, 100);
  MyColorPicker cp2(c2, 60);

  background.addFloodFill(bfs,cp1);
  background.addFloodFill(dfs,cp2);
  Animation animation = background.animate(1000);

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");

  return 0;
}
