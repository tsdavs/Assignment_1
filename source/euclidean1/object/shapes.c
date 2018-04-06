/**
 *  Implementation of shapes.h
 */
#include "euclidean1/object/shapes.h"
#include "gl_helper.h"

void r_drawSquare(int color, square_t* s)
{
    if(s != NULL)
    {
        GLCall(glBegin(GL_QUADS))
        GLCall(glVertex3f(s->x, s->y, s->z))
        GLCall(glVertex3f(s->x, s->y + s->height, s->z))
        GLCall(glVertex3f(s->x + s->width, s->y + s->height, s->z))
        GLCall(glVertex3f(s->x + s->width, s->y, s->z))
        GLCall(glEnd())
    }
}
