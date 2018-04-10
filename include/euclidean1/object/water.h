/**
 *	Water structure and functions
 */
#ifndef _WATER_H_INCLUDED_
#define _WATER_H_INCLUDED

#include <limits.h>
#include <stdbool.h>

#define SINE_AMPLITUDE 0.15f
#define WATER_MAX_TESS USHRT_MAX
#define WATER_MIN_TESS 4

typedef struct
{
	int 	tesselations;	/**< Number of tesselations to draw */
	
    float*  x_vals;
	float*	y_vals;			/**< Calculated y values */

} water_t;

/**
 *	Calculate y_values 
 */
void w_calculateSine(float dt);

/**
 *	Draw this sine wave
 */
void w_drawSine(bool drawNormal, bool drawTangent);

float w_calcSineAtX(float x);

float w_getAngleAtX(float x);


#endif
