#include "StickerSheet.h"
#include <iostream>

namespace cs225{
StickerSheet::StickerSheet(){}

StickerSheet::StickerSheet(const Image& picture, unsigned max){
    Img_array = new Image*[max];
    base = new Image(picture);
    xx_cor = new int[max];
    yy_cor = new int[max];
    for (unsigned int i = 0; i < max; i++){
        // Img_array[i] = new Image;
        Img_array[i] = nullptr;
    }
    maxIndex = max - 1;
}

StickerSheet::~StickerSheet(){
    for(unsigned int i = 0; i <= maxIndex; i++){
        if(Img_array != nullptr){
            delete Img_array[i];
            Img_array[i] = nullptr;
        }
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
    base = new Image(*other.base);
    xx_cor = new int[maxIndex+1];
    yy_cor = new int[maxIndex+1];

    for (unsigned i = 0; i<= maxIndex; i++){
        if (other.Img_array[i] == nullptr){
            // Img_array[i] = new Image;
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
    if(this != &other){
        for(unsigned int i = 0; i <= maxIndex; i++){
            if(Img_array[i] != nullptr){
                delete Img_array[i];
                Img_array[i] = nullptr;
            }
        }
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
    base = new Image(*other.base);
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
    if(max == maxIndex + 1) return;
    else if(max > maxIndex+1){
        Image** new_Img_array = new Image*[max];
        int* new_yy_cor = new int[max];
        int* new_xx_cor = new int[max];
        for(unsigned int i=0; i<=maxIndex; i++){
            new_Img_array[i] = new Image(*Img_array[i]);
            new_yy_cor[i] = yy_cor[i];
            new_xx_cor[i] = xx_cor[i];
        }
        for(unsigned int u=maxIndex+1; u<max;u++){
            new_Img_array[u] = nullptr;
            new_xx_cor[u] = 0;
            new_yy_cor[u] = 0;
        }
        for(unsigned int i = 0; i <= maxIndex; i++){
            delete Img_array[i];
            Img_array[i] = nullptr;
        }        
        delete []Img_array;
        delete []xx_cor;
        delete []yy_cor;

        Img_array = new_Img_array;
        yy_cor = new_yy_cor;
        xx_cor = new_xx_cor;
        maxIndex = max - 1;

    }
    else{
        for(unsigned i=max; i<=maxIndex; i++){
            removeSticker(i);
        }
        int new_maxIndex = maxIndex -(maxIndex - max + 1);
        Image** new_Img_array = new Image*[new_maxIndex+1];
        int* new_xx_cor = new int[new_maxIndex+1];
        int* new_yy_cor = new int[new_maxIndex+1];
        for(int j = 0; j <= new_maxIndex; j++){
            new_Img_array[j] = new Image(*Img_array[j]);
            new_xx_cor[j] = xx_cor[j];
            new_yy_cor[j] = yy_cor[j];
        }
        for(int i = 0; i <= new_maxIndex; i++){
            delete Img_array[i];
            Img_array[i] = nullptr;
        }        
        delete []Img_array;
        delete []xx_cor;
        delete []yy_cor;

        Img_array = new_Img_array;
        yy_cor = new_yy_cor;
        xx_cor = new_xx_cor;
        
    }
}

int StickerSheet::addSticker(Image& sticker, unsigned x, unsigned y){
    for(unsigned int i = 0; i <= maxIndex; i++){
        if(Img_array[i] == nullptr){
            Img_array[i] = new Image(sticker);
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
    if (index > maxIndex || Img_array[index] == nullptr){
        return;
    }
    else{
        delete Img_array[index];
        Img_array[index] = nullptr;
        xx_cor[index] = 0;
        yy_cor[index] = 0;
    }

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
    Image* canvas = new Image(*base);
    HSLAPixel* canvas_pixel, *sticker_pixel;
    unsigned int canvas_w = base->width();
    unsigned int canvas_h = base->height();

    for(unsigned int i = 0; i<=maxIndex; i++){
        if(Img_array[i] == nullptr) continue;
        else{
            if(xx_cor[i] + Img_array[i]->width() > canvas_w){
                canvas_w  = xx_cor[i] + Img_array[i]->width();
            }
            if(yy_cor[i] + Img_array[i]->height() > canvas_h){
                canvas_h  = yy_cor[i] + Img_array[i]->height();                
            }
        }
    }
    canvas->resize(canvas_w, canvas_h);

    for(unsigned int i = 0; i<=maxIndex; i++){
        if(Img_array[i] == nullptr) continue;
        else{
            for(unsigned int x = xx_cor[i]; x < xx_cor[i] + Img_array[i]->width(); x++){
                for(unsigned int y = yy_cor[i];y < yy_cor[i] + Img_array[i]->height(); y++){
                    canvas_pixel = canvas->getPixel(x, y);
                    sticker_pixel = Img_array[i]->getPixel(x-xx_cor[i], y-yy_cor[i]);
                    if(sticker_pixel->a != 0){
                    canvas_pixel->a = sticker_pixel->a;
                    canvas_pixel->h = sticker_pixel->h;
                    canvas_pixel->l = sticker_pixel->l;
                    canvas_pixel->s = sticker_pixel->s;
                    }
                }
            }
        }
    }

    return *canvas;
}
}