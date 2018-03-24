/**
 *  Program entry point
 */
#include <stdio.h>
#include <stdlib.h>

#include "platform.h"
#include "euclidean1/system/engine.h"


int main(int argc, char** argv)
{
    window_t* hwnd;

    glutInit(&argc, argv);
    e_init(argv);

    return EXIT_SUCCESS;
}
