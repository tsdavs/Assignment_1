/**
 *  Shape structures and functions
 */
#ifndef _SHAPES_H_INCLUDED_
#define _SHAPES_H_INCLUDED_

#include "euclidean1/math/vec2.h"

/**
 *  Structures representing a square
 *
 *  x - X location of top left corner
 *  y - Y location of top left corner
 *  width - Width of square (in pixels)
 *  height - Height of square (in pixels)
 *
 */
typedef struct
{
    float   x;
    float   y;
    float   z;
 
    float   width;
    float   height;
} square_t;

typedef struct
{
    float   x;
    float   y;
    float   z;
 
    float   radius;
} circle_t;

void r_drawSquare(int color, square_t* s);
void r_drawCircle(int color, circle_t* c);













#endif
