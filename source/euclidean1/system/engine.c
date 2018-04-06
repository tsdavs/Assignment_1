/**
 *  Implementation of engine.h
 */
#include "euclidean1/system/engine.h"
#include "euclidean1/system/window.h"
#include "euclidean1/object/shapes.h"

#include "platform.h"
#include "gl_helper.h"

#include <stdio.h>

static engine_t engine;

static square_t square;

static void draw(void)
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GLCall(glClearColor(0.0f, 0.0f, 1.0f, 1.0f));

    //GLCall(glPopMatrix()); // Good example of the GLCall() macro!
    r_drawSquare(0xffffffff, &square);

    glutSwapBuffers();
}

bool e_init(char** argv)
{
    //engine.hwnd = r_createWindow(640, 480, "Test");
    r_createWindow(640, 480, "Test");
    r_setDrawFunction(&draw);

    engine.running = true;

    square.x = -1.0f;
    square.y = 0.0f;
    square.z = 1.0f;
    
    square.width = 0.5f;
    square.height = 0.5f;

    while(engine.running)
    {
        glutMainLoopEvent();
    }

    e_shutdown();
}

void e_shutdown(void)
{
    printf("r_shutdown...\n");
    
    r_freeWindow();
}
