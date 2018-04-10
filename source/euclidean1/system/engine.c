/**
 *  Implementation of engine.h
 */
#include "euclidean1/system/engine.h"
#include "euclidean1/system/window.h"

#include "platform.h"
#include "gl_helper.h"

#include "euclidean1/system/text.h"
#include "euclidean1/object/water.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MILLISECOND_TIME 1000.0f

static engine_t engine;

extern water_t water;

static bool drawNormals     = false;
static bool drawTangents    = false;

/**
 *  Our draw function
 */
static void draw(void)
{
    char buffer[256];
    
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT))
    
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
    
	w_drawSine(drawNormals, drawTangents);
  


    glutSwapBuffers();
    engine.frames++;
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
    case 'q':
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
    case 'd':
        engine.debug = !engine.debug;
        break;
    case 's':
        engine.running = !engine.running;
        break;
    case 'n':
        drawNormals = !drawNormals;
        break;
    case 't':
        drawTangents = !drawTangents;
        break;
    default:
        break;
    }
}

void e_update(void)
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
    
    // ALL UPDATE STUFF NEEDS TO GO IN HERE!!!!
    w_calculateSine(dt);



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

    srand(time(NULL));

    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glEnable(GL_BLEND))
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))
    engine.running = true;
    
    
    glutMainLoop();
}
