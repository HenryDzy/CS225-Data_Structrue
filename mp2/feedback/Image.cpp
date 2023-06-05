#include "Image.h"
#include <iostream>

namespace cs225{
Image::Image(){}

void Image::lighten(){
    for (unsigned x=0; x<width(); x++){
        for(unsigned y=0; y<height(); y++){
            HSLAPixel* pixel = getPixel(x, y);
            pixel->l += 0.1;
            if(pixel->l > 1.0){
                pixel->l = 1.0;
            }
        }
    }
}

void Image::lighten(double amount){
    for (unsigned x=0; x<width(); x++){
        for(unsigned y=0; y<height(); y++){
            HSLAPixel* pixel = getPixel(x, y);
            pixel->l += amount;
            if(pixel->l > 1.0){
                pixel->l = 1.0;
            }
        }
    }
}

void Image::darken(){
    for (unsigned x=0; x<width(); x++){
        for(unsigned y=0; y<height(); y++){
            HSLAPixel* pixel = getPixel(x, y);
            pixel->l -= 0.1;
            if(pixel->l < 0.0){
                pixel->l = 0.0;
            }
        }
    }
}

void Image::darken(double amount){
    for (unsigned x=0; x<width(); x++){
        for(unsigned y=0; y<height(); y++){
            HSLAPixel* pixel = getPixel(x, y);
            pixel->l -= amount;
            if(pixel->l < 0.0){
                pixel->l = 0.0;
            }
        }
    }
}

void Image::saturate(){
    for (unsigned x=0; x<width(); x++){
        for(unsigned y=0; y<height(); y++){
            HSLAPixel* pixel = getPixel(x, y);
            pixel->s += 0.1;
            if(pixel->s > 1.0){
                pixel->s = 1.0;
            }
        }
    }
}

void Image::saturate(double amount){
    for (unsigned x=0; x<width(); x++){
        for(unsigned y=0; y<height(); y++){
            HSLAPixel* pixel = getPixel(x, y);
            pixel->s += amount;
            if(pixel->s > 1.0){
                pixel->s = 1.0;
            }
        }
    }
}

void Image::desaturate(){
    for (unsigned x=0; x<width(); x++){
        for(unsigned y=0; y<height(); y++){
            HSLAPixel* pixel = getPixel(x, y);
            pixel->s -= 0.1;
            if(pixel->s < 0.0){
                pixel->s = 0.0;
            }
        }
    }
}

void Image::desaturate(double amount){
    for (unsigned x=0; x<width(); x++){
        for(unsigned y=0; y<height(); y++){
            HSLAPixel* pixel = getPixel(x, y);
            pixel->s -= amount;
            if(pixel->s < 0.0){
                pixel->s = 0.0;
            }
        }
    }
}

void Image::grayscale() {
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel *pixel = getPixel(x, y);
      pixel->s = 0;
    }
  }
}

void Image::rotateColor(double degrees){

    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
        HSLAPixel *pixel = getPixel(x, y);
        pixel->h += degrees;
        for(; pixel->h > 360.0;){
            pixel->h -= 360.0;
        }
        for(; pixel->h < 0.0;){
            pixel->h += 360.0;
        }
        }
    }
}

void Image::illinify(){
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
        HSLAPixel *pixel = getPixel(x, y);
        if (pixel->h >= 0 && pixel->h <= 11){ 
            pixel->h = 11;
        }
        else if (pixel->h > 11 && pixel->h < 216){
            if ((pixel->h - 11)*(pixel->h - 11) < (pixel->h - 216)*(pixel->h - 216)){
            pixel->h = 11;
            }
            else {
            pixel->h = 216;
            }
        }
        else{
            if ((pixel->h - 372)*(pixel->h - 372) < (pixel->h - 216)*(pixel->h - 216)){ //the hues are represented as a circle
            pixel->h = 11;                                                            //so this part considers the case that
            }                                                                           //the color is closer to 371 rather than 216
            else {
            pixel->h = 216;
            }        
            }
        }
    }
}
void Image::scale(double factor){
    unsigned w, h;
    w = factor * width();
    h =  factor * height();
    Image* orig_Image = new Image();
    *orig_Image = *this;
    resize(w, h);

    HSLAPixel* orig_p, *new_p;
    for(unsigned int i=0; i < w; i++){
        for(unsigned int j=0; j < h; j++){
            orig_p = orig_Image->getPixel(i/factor, j/factor);
            new_p = getPixel(i,j);
            *new_p = *orig_p;
        }
    }

    delete orig_Image;
}

void Image::scale(unsigned w, unsigned h){
    Image* orig_Image = new Image();
    *orig_Image = *this;
    resize(w, h);

    double factorW, factorH;
    factorW = w/width();
    factorH = h/height();
    HSLAPixel* orig_p, *new_p;
    for(unsigned int i=0; i < w; i++){
        for(unsigned int j=0; j < h; j++){
            orig_p = orig_Image->getPixel(i/factorW, j/factorH);
            new_p = getPixel(i,j);
            *new_p = *orig_p;
        }
    }

    delete orig_Image;
}
}