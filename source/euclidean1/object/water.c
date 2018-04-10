/**
 *	Implementation of water.h
 */
#include "euclidean1/object/water.h"

#include "gl_helper.h"
#include "euclidean1/math/vec2.h"

#include <math.h>

#define M_PI 3.14159265358979323846263383279f

static const float right = 1.0f;
static const float left = -1.0f;
static const float range = 1.0f - -1.0f;

static float anim_timer = 0.0f;

water_t water;

void w_calculateSine(float dt)
{
	float x;

	anim_timer += dt;
	GLCall(glColor3f(1.0f, 0.0f, 0.0f))

	for(int i = 0; i < water.tesselations; i++)
	{
		x = i * (range/water.tesselations)+left;
		water.y_vals[i] = SINE_AMPLITUDE*sinf(2*M_PI*x+anim_timer);
	}
}

void w_drawSine(bool drawNormal, bool drawTangent)
{
	float x;

    GLCall(glColor4f(0.0f, 1.0f, 0.976, 0.6f))
	glBegin(GL_QUAD_STRIP);
	glVertex3f(-1, -1, 1);
	for(int i = 0; i <= water.tesselations; i++)
	{
		x = i * (range/water.tesselations)+left;        
		glVertex3f(x, water.y_vals[i], 1);
        
	    glVertex3f(x, -1, 1);
	}
    glVertex3f(1, -1, 1);
	glEnd();

    if(drawTangent)
    {
        float dy;
        for(int i = 0; i <= water.tesselations; i++)
        {
            x = i * (range/water.tesselations)+left;
            dy = 2*M_PI*SINE_AMPLITUDE*cosf(2*M_PI*x+anim_timer);

            vec2_t vec; 
            vec.x = x;
            vec.y = water.y_vals[i];
            vec.i = 1;
            vec.j = dy;
            v_draw(&vec, 1.0f, 0.0f, 0.0f, 0.05f, true);
        }
    }

    if(drawNormal)
    {
        float dy;
        for(int i = 0; i <= water.tesselations; i++)
        {
            x = i * (range/water.tesselations)+left;
            dy = 2*M_PI*SINE_AMPLITUDE*cosf(2*M_PI*x+anim_timer);

            vec2_t vec; 
            vec.x = x;
            vec.y = water.y_vals[i];
            vec.i = -dy;
            vec.j = 1;
            v_draw(&vec, 0.0f, 1.0f, 0.0f, 0.05f, true);
        }
    }
}
