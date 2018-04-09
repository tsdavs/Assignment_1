/**
 *  Wrapper functions for GLUT text drawing!
 */
#ifndef _TEXT_H_INCLUDED_
#define _TEXT_H_INCLUDED

/**
 *  Draw an individual character on the screen at position x, y
 */
void r_drawChar(int x, int y, int c);

/**
 *  Draw a string of characters on the screen at position x, y
 */
void r_drawString(int x, int y, const char* msg);

#endif
