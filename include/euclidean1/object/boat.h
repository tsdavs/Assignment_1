/**
 *  Boat data structures and functions
 */
#ifndef _BOAT_H_INCLUDED
#define _BOAT_H_INCLUDED

#include <stdbool.h>

typedef struct
{
    float x;        /**< x position to start drawing from */
    float y;        /**< y position to start drawing from */
    float width;    /**< Width of the hull */
    float height;   /**< Height of the hull */

    float r;
    float g;
    float b;

    float z_rot;

    bool flip;
} boat_t;


/**
 *  Draw boat using a hierarchial method.
 */
void b_drawBoat(boat_t* b);

#endif