/**
 *  Implementation of boat.h
 */
#include "euclidean1/object/boat.h"

#include "gl_helper.h"

#include <math.h>


static float prev_z_rot = 0.0f;

static void r_drawDeck(float r, float g, float b, float z_rot)
{
    GLCall(glColor4f(r, g, b, 1.0f))

    GLCall(glPushMatrix())
    GLCall(glScalef(0.1f, 0.35f, 1.0f))

    glBegin(GL_POLYGON);
        glVertex3f(0.0f - 0.2, 0.0f + 0.1, -0.8f);
        glVertex3f(0.0f + 0.2, 0.0f + 0.1, -0.8f);
        glVertex3f(0.0f + 0.2, 0.0f - 0.1, -0.8f);
        glVertex3f(0.0f - 0.2, 0.0f - 0.1, -0.8f);
    glEnd();

    GLCall(glPopMatrix())
}

static void r_drawHull(float r, float g, float b, float z_rot, float width, float height, bool flip)
{
    GLCall(glColor4f(r, g, b, 1.0f))

    if(flip)
    {
        GLCall(glScalef(-1.0f, 1.0f, 1.0f))
    }

    GLCall(glPushMatrix())
    GLCall(glScalef(0.35f, 0.35f, 1.0f))

    glBegin(GL_POLYGON);
        glVertex3f(0.0f - width - 0.1, 0.0f + height, -0.8f);
        glVertex3f(0.0f + width + 0.1, 0.0f + height, -0.8f);
        glVertex3f(0.0f + width, 0.0f - height, -0.8f);
        glVertex3f(0.0f - width, 0.0f - height, -0.8f);
    glEnd();

    GLCall(glPopMatrix())
}

void b_drawBoat(boat_t* b)
{
    GLCall(glPushMatrix())
    GLCall(glTranslatef(b->x, b->y, 0.0f))

	GLCall(glRotatef(b->z_rot, 0.0f, 0.0f, 1.0f));

    // Draw base of the boat
    r_drawHull(b->r, b->g, b->b, b->z_rot, b->width, b->height, b->flip);

    // Draw the bridge
    GLCall(glTranslatef(0.0f, b->height - 0.05, 0.0f));
    r_drawDeck(b->r, b->g, b->b, b->z_rot);

    // HACK HACK HACK along, hack hack while I sing this song
    // There's obviously a way to do this without a sheer fuckload of
    // magic numbers, but it works so hey!
    b->cannon.x = b->x + b->width - 0.065f; 
    b->cannon.y = b->y + b->height - 0.05f - 0.015f;

    // Draw the cannon
    GLCall(glTranslatef(b->width - 0.065, -0.015f, 0.0f))
    c_drawCannon(&b->cannon, b->r, b->g, b->b);
    GLCall(glPopMatrix())
}
