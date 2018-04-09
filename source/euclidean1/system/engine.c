/**
 *  Implementation of engine.h
 */
#include "euclidean1/system/engine.h"
#include "euclidean1/system/window.h"

#include "platform.h"
#include "gl_helper.h"

#include <stdio.h>
#include <math.h>

static engine_t engine;

/**
 *  Our draw function
 */
static void draw(void)
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    
    // ALL RENDER CODE GOES IN HERE!!!!


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
    static long prev_tl = 0;
    float t = 0.0f;
    float t2 = 0.0f;
    float dt = 0.0f;
    long tl = 0;

    t = glutGet(GLUT_ELAPSED_TIME); // Number of ms since glutInit() was called
    if(prev_t < 0.0f)
    {
        prev_t = t;
        return;
    }          

    dt = t - prev_t;

    // Ew
    t2 = t;
    t2 /= 1000;
    t2 = floor(t2 + 0.5) + 1000.0f;
    tl = (float)t2;
    
    if(tl != prev_tl)
    {
        prev_tl = tl;
        printf("tick: %.2f\n", engine.framerate * 1000);
    }
    
    // ALL UPDATE STUFF NEEDS TO GO IN HERE!!!!
    //
    
    prev_t = t;
    
    dt = t - engine.last_framerate;
    if(dt > engine.frame_interval)
    {        
        engine.framerate = engine.frames/dt;
        engine.last_framerate = t;
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
    engine.last_framerate   = 0.0f;
    engine.time_elapsed     = 0.0f;
    engine.framerate        = 0.0f;    

    GLCall(glClearColor(0.0f, 0.0f, 1.0f, 1.0f));

    engine.running = true;
    
    
    glutMainLoop();
}
