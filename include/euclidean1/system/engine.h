/**
 *  Engine related structures and functions
 */
#ifndef _ENGINE_H_INCLUDED
#define _ENGINE_H_INCLUDED

#include <stdbool.h>

#include "euclidean1/system/window.h"

typedef struct
{
    void        (*e_update)();      /**< Engine idle update loop */
    void        (*e_input)();       /**< Engine input function pointer */

    bool        running;            /**< Is the game currently running??? */
} engine_t;

/**
 *  Engine initilisation routine. Gets us out of main.
 *
 *  @param argv Arguments passed from the command line
 */
bool e_init(char** argv);

/**
 *  Engine shutdown function
 */
void e_shutdown(void);





#endif
