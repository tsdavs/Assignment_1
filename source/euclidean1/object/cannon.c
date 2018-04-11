/**
 *  Implementation of cannon.h
 */
#include "euclidean1/object/cannon.h"

#include "gl_helper.h"

void c_drawCannon(cannon_t* c, float r, float g, float b)
{
    GLCall(glColor4f(r, g, b, 1.0f))

    GLCall(glPushMatrix())
    GLCall(glScalef(0.1f, 0.1f, 1.0f))
    GLCall(glRotatef(c->z_rot, 0.0f, 0.0f, 1.0f))

    glBegin(GL_QUADS);
        glVertex3f(0.0f, 0.0f, -0.8f);
        glVertex3f(c->length, 0.0f, -0.8f);
        glVertex3f(c->length, -0.15f, -0.8f);
        glVertex3f(0.0f, -0.15f, -0.8f);
    glEnd();

    GLCall(glPopMatrix())
}

void c_rotateCannon(cannon_t* c, float angle)
{
    c->z_rot += angle;
}
