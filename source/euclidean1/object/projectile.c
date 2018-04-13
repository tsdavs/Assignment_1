/**
 *  Implementation of projectile.h
 */
#include "euclidean1/object/projectile.h"

static const float GRAVITY_CONST = -3.8f;

active_list_t p_list;

void p_init(projectile_t* p, float x, float y, float vx, float vy, float r)
{
    if(p_list.num >= MAX_PROJECTILES)
    {
        printf("[warn]: Max number of projectiles active!\n");
        return;
    }

    p = (projectile_t*)malloc(sizeof(projectile_t));

    p->x    = x;
    p->y    = y;
    
    p->vx   = vx;
    p->vy   = vy;
    
    p->r    = r;

    p->b_vol.x      = x - r;
    p->b_vol.y      = y + r;
    p->b_vol.width  = r * 2.0f; // radius -> diameter
    p->b_vol.height = -(r * 2.0f);
    p->b_vol.min    = x - r; // Top left corner of bounding box is already the edge
    p->b_vol.max    = x + r;

    for(int i = 0; i < MAX_PROJECTILES; i++)
    {
        if(p_list.projectiles[i] == NULL)
        {
            p_list.projectiles[i] = p;
            break;   
        }
    }

    p_list.num++;
}

int p_update(projectile_t* p, float dt)
{ 
    // TODO: Mark the projetctile for removal
    if(p->x < -1.0f || p->x > 1.0f || p->y < -1.0f)
    {
        if(p != NULL)
        {
            free(p);
            p = NULL; // Prevent a dangling pointer
            p_list.num--;
        
            return 1;
        }
    }

    p->x += p->vx * dt;
    p->y += p->vy * dt;
    
    p->b_vol.x = p->x - p->r;
    p->b_vol.y = p->y + p->r;
    p->b_vol.min = p->x - p->r;
    p->b_vol.max = p->x + p->r;
    
    // Apply physics!
    p->vy += GRAVITY_CONST * dt;

    return 0;
}

void p_draw(projectile_t* p)
{
    // Wow, how fucking easy is this one!

    GLCall(glPushMatrix())
    GLCall(glColor3f(1.0f, 0.0f, 0.0f));

    GLCall(glTranslatef(p->x, p->y, 0.0f))
    glutSolidSphere(p->r, 10, 10); 

    GLCall(glPopMatrix())
}

void p_remove(projectile_t* p, int i)
{
    if(p == NULL)
        return;

    free(p);
    p = NULL;
    p_list.projectiles[i] = NULL;
    p_list.num--;
}
