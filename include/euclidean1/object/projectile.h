/**
 *  Projectile structure and functions
 */
#ifndef _PROJECTILE_H_INCLUDED
#define _PROJECTILE_H_INCLUDED

#include "euclidean1/system/aabb.h"

#define MAX_PROJECTILES 12
#define GRAVITY         -9.8f

/**
 *  Projectile data structure
 */
typedef struct
{
    float   x;    /**< Projectile's current x position */
    float   y;    /**< Projectile's current y position */

    float   vx;   /**< Velocity in the x axis (constant)*/
    float   vy;   /**< Velocity in the y axis */

    float   r;    /**< Projectile's radius */

    AABB    b_vol; /**< This projectile's bounding volume */
} projectile_t;

/**
 *  Active projectile list
 */
typedef struct
{
    projectile_t* projectiles[MAX_PROJECTILES]; /**< Projectile list */
    
    int num; /**< Number of projectile's that are currently on screen */
} active_list_t;

/**
 *  Projectile initialisation
 */
void p_init(projectile_t* p, float x, float y, float vx, float vy, float r);

/**
 *  Projectile update
 */
int p_update(projectile_t* projectile, float dt);

/**
 *  Draw a projectile to the screen
 */
void p_draw(projectile_t* projectile);

/**
 *  Remove a projectile from the actile list
 */
void p_remove(projectile_t* p, int i);



#endif
