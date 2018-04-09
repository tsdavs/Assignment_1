/**
 *  Implementation of engine.h
 */
#include "euclidean1/system/engine.h"
#include "euclidean1/system/window.h"

#include "platform.h"
#include "gl_helper.h"

#include "euclidean1/system/text.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

#define MILLISECOND_TIME 1000.0f

static engine_t engine;

/**
 *  Our draw function
 */
static void draw(void)
{
    char buffer[256];
    
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    
    // ALL RENDER CODE GOES IN HERE!!!!
    r_drawString(30, 50, "Hello World!");
    sprintf(buffer, "fps: %.2f", engine.framerate);
    r_drawString(0, 0, buffer);

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
    if(prev_t < 0.0f)
    {
        prev_t = t;
        return;
    }          

    dt = t - prev_t;
    
    // ALL UPDATE STUFF NEEDS TO GO IN HERE!!!!
    //
    
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
    engine.frames           = 0;
    engine.frame_interval   = 0.2;
    engine.last_frametime   = 0.0f;
    engine.time_elapsed     = 0.0f;
    engine.framerate        = 0.0f;    

    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

    engine.running = true;
    
    
    glutMainLoop();
}
