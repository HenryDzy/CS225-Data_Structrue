#ifndef STICKERSHEET_H
#define STICKERSHEET_H
#include "Image.h"

namespace cs225{
    class StickerSheet{
        public:
        StickerSheet(const Image &picture, unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet &other);
        const StickerSheet& operator= (const StickerSheet &other);
        void changeMaxStickers(unsigned max);
        int addSticker (Image &sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        void removeSticker(unsigned index);
        Image* getSticker(unsigned index) const;
        Image render() const;
        Image** Img_array;
        int *xx_cor, *yy_cor;
        unsigned int maxIndex;
        Image* base;

        private:
    };
}



#endif