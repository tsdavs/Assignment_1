/**
 *  Axis Aligned Bounding boxes for collision detection
 */
#ifndef _AABB_H_INCLUDED
#define _AABB_H_INCLUDED

#include "gl_helper.h"

#include <stdbool.h>

typedef struct
{
    float origin;   /**< Origin point of the AABB. This is equal to x/2 */
    float x;        /**< x position of the top left corner of the bounding box */
    float y;        /**< y position of the top left corner of the bounding box */
    
    float min;      /**< Minimum x-value, x - width */
    float max;      /**< Maximum x-value, x + width */
    
    float width;    /**< Bounding box width */
    float height;   /**< Bounding box height */

    float z_rot;    /**< Bounding volume rotation along z-axis */
    float scale;    /**< Scale of this bounding box (to fit visual size of the geometry for glScalef() ) */
} AABB;

/**
 *  Test if two AABB's are intersecting.
 */
static bool testIntersection(AABB* b1, AABB* b2)
{
    if(b1->max > b2->min && b1->min < b2->max && b1->y < b2->y + b2->height && b1->y + b1->height > b2->y)
        return true;

    return false;
}

static void printAABB(AABB* b)
{
    printf("bounding volume info: x: %f, y: %f, min: %f, max: %f, width: %f, height: %f\n", b->x, b->y, b->min, b->max, b->width, b->height);
}

static void drawAABB(AABB* b)
{
    GLCall(glPushMatrix())
    GLCall(glColor3f(1.0f, 1.0f, 1.0f))
    //GLCall(glScalef(b->scale, b->scale, 1.0f))
    
    GLCall(glDisable(GL_BLEND))
    
    glBegin(GL_LINE_LOOP);
        glVertex2f(b->min, b->y);
        glVertex2f(b->max, b->y);
        glVertex2f(b->max, b->y + b->height);
        glVertex2f(b->min, b->y + b->height);
    glEnd();

    GLCall(glEnable(GL_BLEND))
    GLCall(glPopMatrix())
}

#endif
