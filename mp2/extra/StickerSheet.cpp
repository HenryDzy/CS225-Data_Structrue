#include "StickerSheet.h"
#include <iostream>

namespace cs225{
StickerSheet::StickerSheet(const Image& picture, unsigned max){
    Img_array = new Image*[max];
    base = new Image(picture);
    xx_cor = new int[max];
    yy_cor = new int[max];
    for (unsigned int i = 0; i < max; i++){
        Img_array[i] = new Image;
        Img_array[i] = nullptr;
    }
    maxIndex = max - 1;
}

StickerSheet::~StickerSheet(){
    for(unsigned int i = 0; i <= maxIndex; i++){
        delete Img_array[i];
        Img_array[i] = nullptr;
    }
    delete []Img_array;
    Img_array = nullptr;
    delete base;
    base = nullptr;
    delete []xx_cor;
    xx_cor = nullptr;
    delete []yy_cor;
    yy_cor = nullptr;
}

StickerSheet::StickerSheet(const StickerSheet & other){
    maxIndex = other.maxIndex;
    Img_array = new Image*[maxIndex+1];
    base = other.base;
    xx_cor = new int[maxIndex+1];
    yy_cor = new int[maxIndex+1];

    for (unsigned i = 0; i<= maxIndex; i++){
        if (other.Img_array[i] == nullptr){
            Img_array[i] = new Image;
            Img_array[i] = nullptr;
        }
        else{
            Img_array[i] = new Image(*other.Img_array[i]);
        }
        xx_cor[i] = other.xx_cor[i];
        yy_cor[i] = other.yy_cor[i];
    }
}

const StickerSheet& StickerSheet::operator=(const StickerSheet& other){
    for(unsigned int i = 0; i <= maxIndex; i++){
        delete Img_array[i];
        Img_array[i] = nullptr;
    }
    delete []Img_array;
    Img_array = nullptr;
    delete base;
    base = nullptr;
    delete []xx_cor;
    xx_cor = nullptr;
    delete []yy_cor;
    yy_cor = nullptr;

    maxIndex = other.maxIndex;
    Img_array = new Image*[maxIndex+1];
    base = other.base;
    xx_cor = new int[maxIndex+1];
    yy_cor = new int[maxIndex+1]; 
    for (unsigned i = 0; i<= maxIndex; i++){
        if (other.Img_array[i] == nullptr){
            Img_array[i] = nullptr;
        }
        else{
            Img_array[i] = new Image(*other.Img_array[i]);
        }
        xx_cor[i] = other.xx_cor[i];
        yy_cor[i] = other.yy_cor[i];
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max){
    if(max >= maxIndex+1){
        Image** new_Img_array = new Image*[max];
        int* new_yy_cor = new int[max];
        int* new_xx_cor = new int[max];
        for(unsigned int i=0; i<=maxIndex; i++){
            new_Img_array[i] = new Image(*Img_array[i]);
            new_yy_cor[i] = yy_cor[i];
            new_xx_cor[i] = xx_cor[i];
        }
        for(unsigned int u=maxIndex+1; u<max;u++){
            new_Img_array[u] = new Image;
            new_Img_array[u] = nullptr;
            new_xx_cor[u] = 0;
            new_yy_cor[u] = 0;
        }
        Img_array = new_Img_array;
        yy_cor = new_yy_cor;
        xx_cor = new_xx_cor;
        maxIndex = max - 1;
        for(unsigned int i = 0; i <= maxIndex; i++){
            delete new_Img_array[i];
            new_Img_array[i] = nullptr;
        }        
        delete []new_Img_array;
        new_Img_array = nullptr;
        delete []new_xx_cor;
        new_xx_cor = nullptr;
        delete []new_yy_cor;
        new_yy_cor = nullptr;
    }
    else{
        for(unsigned i=max; i<=maxIndex; i++){
            removeSticker(i);
        }
    }
}

int StickerSheet::addSticker(Image& sticker, unsigned x, unsigned y){
    for(unsigned int i = 0; i <= maxIndex; i++){
        if(Img_array[i] != nullptr){
            Img_array[i] = &sticker;
            xx_cor[i] = x;
            yy_cor[i] = y;
            return i;
        }
    }
    return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    if(index>maxIndex-1 || Img_array[index] == nullptr){
        return false;
    }
    else if( x + Img_array[index]->width() > base->width() || 
             y + Img_array[index]->height() > base->height() ){
        return false;
    }
    else{
        xx_cor[index] = x;
        yy_cor[index] = y;
        return true;
    }
}

void StickerSheet::removeSticker(unsigned index){
    if (index > maxIndex){
        return;
    }
    maxIndex -= 1;
    Image** new_Img_array = new Image*[maxIndex+1];
    int* new_xx_cor = new int[maxIndex+1];
    int* new_yy_cor = new int[maxIndex+1];
    for(unsigned int i = 0; i<index; i++){
        *new_Img_array[i] = *Img_array[i];
        new_xx_cor[i] = xx_cor[i];
        new_yy_cor[i] = yy_cor[i];
    }
    for (unsigned int u = index+1 ; u<=maxIndex; u++){
        *new_Img_array[u-1] = *Img_array[u];
        new_xx_cor[u-1] = xx_cor[u];
        new_yy_cor[u-1] = yy_cor[u]; 
    }
    Img_array = new_Img_array;
    xx_cor = new_xx_cor;
    yy_cor = new_yy_cor;
    delete[] new_Img_array;
    new_Img_array = nullptr;
    delete[] new_xx_cor;
    new_xx_cor = nullptr;
    delete[] new_yy_cor;
    new_yy_cor = nullptr;
}

Image* StickerSheet::getSticker(unsigned index)const{
    if(index>maxIndex || Img_array[index] ==nullptr){
        return nullptr;
    }
    else{
        return Img_array[index];
    }
}

Image StickerSheet::render()const{
    Image* canvas = new Image;
    HSLAPixel* canvas_pixel;
    HSLAPixel* sticker_pixel;
    unsigned int w = base->width();
    unsigned int h = base->height();
    unsigned int x, y;
    canvas->resize(w, h);

    for(unsigned int i=0; i<w;i++){
        for(unsigned int j=0; j<h; j++){
            HSLAPixel* base_pixel = base->getPixel(i,j);
            canvas_pixel = canvas->getPixel(i,j);
            canvas_pixel->h = base_pixel->h;
            canvas_pixel->a = base_pixel->a;
            canvas_pixel->s = base_pixel->s;
            canvas_pixel->l = base_pixel->l;
        }
    }
    
    for(unsigned int i = 0; i<=maxIndex; i++){
        if(Img_array[i] == nullptr){
            Image* sticker = Img_array[i];
            x = xx_cor[i];
            y = yy_cor[i];
            for(unsigned int j=x; j<x + sticker->width(); j++){
                for(unsigned int k=y; k<y + sticker->height(); k++){
                    canvas_pixel = canvas->getPixel(j, k);
                    sticker_pixel = sticker->getPixel(j-x, k-y);
                    canvas_pixel->a = sticker_pixel->a;
                    canvas_pixel->h = sticker_pixel->h;
                    canvas_pixel->l = sticker_pixel->l;
                    canvas_pixel->s = sticker_pixel->s;
                }
            }
        }
    }

    return *canvas;
}
}