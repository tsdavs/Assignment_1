/**
 *  Axis Aligned Bounding boxes for collision detection
 */
#ifndef _AABB_H_INCLUDED
#define _AABB_H_INCLUDED

#include <stdbool.h>

typedef struct
{
    float origin;   /**< Origin point of the AABB. This is equal to x/2 */
    float x;        /**< x position of the top left corner of the bounding box */
    float y;        /**< y position of the top left corner of the bounding box */
    
    float width;    /**< Bounding box width */
    float height;   /**< Bounding box height */

    float scale;    /**< Scale of this bounding box (to fit visual size of the geometry for glScalef() ) */
} AABB;

/**
 *  Test if two AABB's are intersecting.
 */
static bool testIntersection(AABB* b1, AABB* b2)
{
    if(b1.x < b2.x + b2.width && b1.x + b1.width > b2.x && b1.y < b2.y + b2.height && b1.y + b1.height > b2.y)
        return true;

    return false;
}



#endif
