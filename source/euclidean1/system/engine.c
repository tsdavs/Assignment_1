/**
 *  Implementation of engine.h
 */
#include "euclidean1/system/engine.h"
#include "euclidean1/system/window.h"

#include "platform.h"

#include <stdio.h>

static engine_t engine;

static void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);


    glutSwapBuffers();
}

bool e_init(char** argv)
{
    engine.hwnd = r_createWindow(640, 480, "Test");
    r_setDrawFunction(engine.hwnd, &draw);

    engine.running = true;

    while(engine.running)
    {
        glutMainLoopEvent();
    }

    e_shutdown();
}

void e_shutdown(void)
{
    printf("r_shutdown...\n");
    
    r_freeWindow(engine.hwnd);
}