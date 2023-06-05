/**
 * @file Image.cpp
 *
 * @author Howie Liu
 * @date Fri Mar 17 3:23:54 AM
 */

#include "Image.h"

namespace cs225 {

Image::Image() : PNG() {}

Image::Image(unsigned width, unsigned height) : PNG(width, height) {}

void Image::lighten(double amount) {
    for (unsigned w = 0; w < width(); ++w) {
        for (unsigned h = 0; h < height(); ++h) {
            HSLAPixel* p = getPixel(w, h);
            if ((p->l += amount) > 1) {
                p->l = 1;
            }
        }
    }
}

void Image::darken(double amount) {
    for (unsigned w = 0; w < width(); ++w) {
        for (unsigned h = 0; h < height(); ++h) {
            HSLAPixel* p = getPixel(w, h);
            if ((p->l -= amount) < 0) {
                p->l = 0;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned w = 0; w < width(); ++w) {
        for (unsigned h = 0; h < height(); ++h) {
            HSLAPixel* p = getPixel(w, h);
            if ((p->s += amount) > 1) {
                p->s = 1;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned w = 0; w < width(); ++w) {
        for (unsigned h = 0; h < height(); ++h) {
            HSLAPixel* p = getPixel(w, h);
            if ((p->s -= amount) < 0) {
                p->s = 0;
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned w = 0; w < width(); ++w) {
        for (unsigned h = 0; h < height(); ++h) {
            getPixel(w, h)->s = 0;
        }
    }
}

void Image::rotateColor(double degrees) {
    // std::cout << "Ori degrees: " << degrees;
    if (degrees < 0) {
        degrees += 360 * (1 + int(-degrees)/360);
    }
    if (degrees > 360) {
        degrees -= 360 * (int(degrees) / 360);
    }
    // std::cout << " | New degrees: " << degrees << std::endl;
    for (unsigned w = 0; w < width(); ++w) {
        for (unsigned h = 0; h < height(); ++h) {
            HSLAPixel* p = getPixel(w, h);
            if ((p->h += degrees) > 360) {
                p->h -= 360;
            }
        }
    }
}

#define ILL_Orange 11
#define ILL_Blue   216

void Image::illinify() {
    for (unsigned w = 0; w < width(); ++w) {
        for (unsigned h = 0; h < height(); ++h) {
            HSLAPixel* p = getPixel(w, h);
            p->h = (p->h >= ((ILL_Blue + ILL_Orange) >> 1) &&
                    p->h <= ((ILL_Blue + ILL_Orange + 360) >> 1)
                    ? ILL_Blue : ILL_Orange);
        }
    }
}

#undef ILL_Blue
#undef ILL_Orange

void Image::scale(double factor) {
    PNG* old = new PNG(*this);
    resize(width() * factor, height() * factor);
    for (unsigned w = 0; w < width(); ++w) {
        for (unsigned h = 0; h < height(); ++h) {
            HSLAPixel* new_p = getPixel(w, h);
            HSLAPixel* old_p = old->getPixel(w / factor, h / factor);
            *new_p = *old_p;
        }
    }
    delete old;
    old = nullptr;
}

void Image::scale(unsigned w, unsigned h) {
    double factor_w = double(w) / width();
    double factor_h = double(h) / height();
    scale(factor_w > factor_h ? factor_h : factor_w);
}

void Image::rotate(int degree){
    Image* new_Img = new Image(*this);
    if (degree == 0) return;
    else if (degree == 90){
        for (unsigned i = 0; i<new_Img->height(); i++){
            for (unsigned j = 0; j<new_Img->width(); j++){
                resize(new_Img->height()-1,new_Img->width()-1);
                HSLAPixel* orig_pixel = getPixel(i, j);
                HSLAPixel* new_pixel = new_Img->getPixel(j, new_Img->height()-i);


                if(orig_pixel->a != 0){
                    orig_pixel->a = new_pixel->a;
                    orig_pixel->s = new_pixel->h;
                    orig_pixel->h = new_pixel->s;
                    orig_pixel->l = new_pixel->l;
                }

            }
        }
        delete new_Img;
        return;
    }
    else if (degree == 180){
        for (unsigned i = 0; i<this->width(); i++){
            for (unsigned j = 0; j<this->height(); j++){
                HSLAPixel* orig_pixel = getPixel(i,j);
                HSLAPixel* new_pixel = new_Img->getPixel(new_Img->width()-i,new_Img->height()-j);
                    orig_pixel->a = new_pixel->a;
                    orig_pixel->s = new_pixel->h;
                    orig_pixel->h = new_pixel->s;
                    orig_pixel->l = new_pixel->l;

            }
        }
        delete new_Img;
        return;
    }
    else if (degree == 270){
        for (unsigned i = 0; i<this->width(); i++){
            for (unsigned j = 0; j<this->height(); j++){
                resize(new_Img->height()-1,new_Img->width()-1);
                HSLAPixel* orig_pixel = getPixel(i,j);
                HSLAPixel* new_pixel = new_Img->getPixel(new_Img->height()-j,new_Img->width()-i);
                if(orig_pixel->a != 0){
                    orig_pixel->a = new_pixel->a;
                    orig_pixel->s = new_pixel->h;
                    orig_pixel->h = new_pixel->s;
                    orig_pixel->l = new_pixel->l;
                }

            }
        }
        delete new_Img;
        return;
    }
    else return;
}

void Image::set_factor(double factor){
    scale_factor = factor;
    return;
}

double Image::get_factor(){
    return scale_factor;
}
};