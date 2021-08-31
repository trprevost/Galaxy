#ifndef BODY
#define BODY

#include"Vec2.h"




typedef struct Color{
    int r;
    int g;
    int b;
} Color;


typedef struct Body{
    Vec2 *pos;
    Vec2 *speed;
    Vec2 *acc;

    int radius;
    int mass;
    Color color;
} Body;




#endif