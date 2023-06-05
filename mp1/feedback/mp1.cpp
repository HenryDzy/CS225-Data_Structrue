#include "cs225/HSLAPixel.h"
#include "mp1.h"
#include <string>
#include "cs225/PNG.h"
#include <iostream>
using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
    HSLAPixel* init_pixel, *final_pixel;
    PNG *File = new PNG();
    File->readFromFile(inputFile);
    PNG *output = new PNG(File->width(), File->height());
    for (unsigned int x = 0; x < File->width(); x++) {
        for (unsigned  int y = 0; y < File->height(); y++) {
            init_pixel = File->getPixel(x, y);
            final_pixel = output->getPixel(File->width()-1-x, File->height()-1-y);
            
            *final_pixel = *init_pixel;
            }
        }
    output->writeToFile(outputFile);

    delete File;
    delete output;
    return;
}