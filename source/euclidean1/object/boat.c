/**
 *  Implementation of boat.h
 */
#include "euclidean1/object/boat.h"
#include "euclidean1/object/water.h"
#include "gl_helper.h"

#include <math.h>

extern water_t water;

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

static void r_drawHull(float r, float g, float b, float z_rot, float width, float height)
{
    GLCall(glColor4f(r, g, b, 1.0f))

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
    if(b->flip)
    {
        GLCall(glPushMatrix())
        GLCall(glScalef(-1.0f, 1.0f, 1.0f)) // Flip in the x-axis
        GLCall(glPopMatrix())
    }

	GLCall(glRotatef(b->z_rot, 0.0f, 0.0f, 1.0f));

    // Draw base of the boat
    r_drawHull(b->r, b->g, b->b, b->z_rot, b->width, b->height);

    // Draw the bridge
    GLCall(glTranslatef(0.0f, b->height - 0.05, 0.0f));
    r_drawDeck(b->r, b->g, b->b, b->z_rot);

    // Draw the cannon
    //c_drawCannon(b->cannon, b-r, b->g, b->b, b->z_rot);
    GLCall(glPopMatrix())
}
