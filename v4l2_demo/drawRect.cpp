#include "drawRect.h"
#ifndef MAX
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#endif
#ifndef MIN
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#endif

#define POINTB(bgr, x, y, width) ((unsigned char *)bgr)[y*width*3 + x*3]
#define POINTG(bgr, x, y, width) ((unsigned char *)bgr)[y*width*3 + x*3+1]
#define POINTR(bgr, x, y, width) ((unsigned char *)bgr)[y*width*3 + x*3+2]

//drawRectangle((unsigned char *)img->imageData, img->width, img->height, 10, 10, 100, 100);
void drawRectangle(unsigned char *bgr, int width, int height, int left, int top, int right, int bottom) {
    int x, y, i;
    if(width > 0 && height > 0 && top < bottom && left < right) {
        if(left < 0) left = 0;
        right= MIN(right, width);
        if(right < 0) right = 0;

        if(top < 0) top = 0;
        bottom = MIN(bottom, height);
        if(bottom < 0) bottom = 0;
        //(left, top), (right, top)
        for(y = top, x = left; x < right; x++) {
            POINTB(bgr, x, y, width) = 0;
            POINTG(bgr, x, y, width) = 0;
            POINTR(bgr, x, y, width) = 255;
        }

        //(right, top), (right, bottom)
        for(x = right, y = top; y < bottom; y++) {
            POINTB(bgr, x, y, width) = 0;
            POINTG(bgr, x, y, width) = 0;
            POINTR(bgr, x, y, width) = 255;
        }
        //(left, bottom), (right, bottom)
        for(x = left, y = bottom; x < right; x++) {
            POINTB(bgr, x, y, width) = 0;
            POINTG(bgr, x, y, width) = 0;
            POINTR(bgr, x, y, width) = 255;
        }
        //(left, top), (left, bottom)
        for(x = left, y = top; y < bottom; y++) {
            POINTB(bgr, x, y, width) = 0;
            POINTG(bgr, x, y, width) = 0;
            POINTR(bgr, x, y, width) = 255;
        }
    }
}
