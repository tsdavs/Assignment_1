/**
 *  Implementation of engine.h
 */
#include "euclidean1/system/engine.h"
#include "euclidean1/system/window.h"

#include "platform.h"
#include "gl_helper.h"

#include "euclidean1/math/angle.h"
#include "euclidean1/system/text.h"
#include "euclidean1/object/water.h"
#include "euclidean1/object/boat.h"
#include "euclidean1/object/cannon.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MILLISECOND_TIME 1000.0f

static engine_t engine;

extern water_t water;

static bool drawNormals     = false;
static bool drawTangents    = false;

static boat_t p1;
static boat_t p2;

static cannon_t c;

/**
 *  Our draw function
 */
static void draw(void)
{
    char buffer[256];
    
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT))
    GLCall(glEnable(GL_DEPTH_TEST))

    if(engine.wireframe)
    {
        GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE))
    }
    else
    {
        GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL))
	}

    sprintf(buffer, "fps: %.2f", engine.framerate);

    if(engine.debug)
    {
        r_drawString(0, 0, buffer);
        r_drawString(0, 30, "DEBUG");
    }

    b_drawBoat(&p1);
    b_drawBoat(&p2);
    c_drawCannon(&c, 0.0f, 1.0f, 0.0f);

	w_drawSine(drawNormals, drawTangents);
  


    glutSwapBuffers();
    engine.frames++;
}

static void e_update(void)
{
    static float prev_t = -1.0f;
    float t = 0.0f;
    float dt = 0.0f;

    t = glutGet(GLUT_ELAPSED_TIME) / MILLISECOND_TIME; // Number of ms since glutInit() was called

    // Skip the first frame to prevent / 0
    // Also keep the clock running even if the sim is paused to dt doesn't become huge
    if(prev_t < 0.0f || !engine.running)
    {
        prev_t = t;
        return;
    }          

    dt = t - prev_t;
    
    w_calculateSine(dt);

    p1.y = w_calcSineAtX(p1.x); // Absolutely disgusting hack
    p1.z_rot = ANG_2_DEGREES(w_getAngleAtX(p1.x));

    p2.y = w_calcSineAtX(p2.x); // Absolutely disgusting hack
    p2.z_rot = ANG_2_DEGREES(w_getAngleAtX(p2.x));

    prev_t = t;
    
    dt = t - engine.last_frametime;
    if(dt > 0.2)
    {        
        engine.framerate = (engine.frames/dt);
        engine.last_frametime = t;
        engine.frames = 0;
    }

    glutPostRedisplay();
}

static void r_reshape(int width, int height)
{
    r_setDimensions(width, height); // Update our logical screen to retain resize info!
    
    // Set the GL viewport to perform affine transformation to the current stuff on the screen (so it doesn't become all warped!)
    GLCall(glViewport(0, 0, width, height))

    // Reload our projection matrix
    GLCall(glMatrixMode(GL_PROJECTION))
    GLCall(glLoadIdentity())
    GLCall(glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f)) // Fill it with an orthographic matrix
    
    GLCall(glMatrixMode(GL_MODELVIEW))
    GLCall(glLoadIdentity())
}

void e_input(unsigned char c, int x, int y)
{
    switch(c)
    {
    case 27:
        exit(EXIT_SUCCESS);
        break;
	case '+':
		water.tesselations *= 2;
		if(water.tesselations > WATER_MAX_TESS)
			water.tesselations = WATER_MAX_TESS;
		break;
	case '-':
		water.tesselations /= 2;
		if(water.tesselations < WATER_MIN_TESS)
			water.tesselations = WATER_MIN_TESS;
		break;
    case 'w':
        engine.wireframe = !engine.wireframe;
        break;
    case '\'':
        engine.debug = !engine.debug;
        break;
    case 'g':
        engine.running = !engine.running;
        break;
    case 'n':
        drawNormals = !drawNormals;
        break;
    case 't':
        drawTangents = !drawTangents;
        break;
    // Left player controls
    case 'a':
        p1.x -= 0.01;
        break;
    case 'd':
        p1.x += 0.01;
        break;
    case 'q':
        if(p1.cannon.z_rot < 90.0f)
            c_rotateCannon(&p1.cannon, 2.0f);
        break;
    case 'Q':
        if(p1.cannon.z_rot > 0.0f)
            c_rotateCannon(&p1.cannon, -2.0f);
        break;
    // Right player controls
    case 'k':
        p2.x -= 0.01;
        break;
    case 'l':
        p2.x += 0.01;
        break;
    case 'o':
        if(p2.cannon.z_rot < 90.0f)
            c_rotateCannon(&p2.cannon, 2.0f);
        break;
    case 'O':
        if(p2.cannon.z_rot > 0.0f)
            c_rotateCannon(&p2.cannon, -2.0f);
        break;
    default:
        break;
    }
}

bool e_init(char** argv)
{
    r_createWindow(640, 480, "Test");
    r_setDrawFunction(&draw);
    
    glutIdleFunc(e_update);
    glutKeyboardFunc(e_input);
    //glutReshapeFunc(r_reshape);    

    // Engine stuff
    engine.debug            = false;
    engine.wireframe        = false;
    engine.frames           = 0;
    engine.frame_interval   = 0.2;
    engine.last_frametime   = 0.0f;
    engine.time_elapsed     = 0.0f;
    engine.framerate        = 0.0f;    

	// Water init
	water.tesselations = 64;
	water.y_vals = (float*)calloc(WATER_MAX_TESS + 1, sizeof(float));
    water.x_vals = (float*)calloc(WATER_MAX_TESS + 1, sizeof(float));

    p1.x = -0.8f;
    p1.y = 0.0f;
    p1.width = 0.1f;
    p1.height = 0.1f;
    p1.r = 1.0f;
    p1.g = 0.0f;
    p1.b = 0.0f;
    p1.flip = false;
    p1.cannon.length = 0.5f;
    p1.cannon.z_rot = 45.0f;

    p2.x = 0.8f;
    p2.y = 0.0f;
    p2.width = 0.1f;
    p2.height = 0.1f;
    p2.r = 0.0f;
    p2.g = 0.0f;
    p2.b = 1.0f;
    p2.flip = true;
    p2.cannon.length = 0.5f;
    p2.cannon.z_rot = 45.0f;

    c.length = 0.5;
    c.z_rot = 45.0f;

    srand(time(NULL));

    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glEnable(GL_BLEND))
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))
    engine.running = true;
    
    
    glutMainLoop();
}
