/**
 *  Implementation of text.h
 */
#include "euclidean1/system/text.h"
#include "gl_helper.h"

void r_drawCharacter(int x, int y, int c)
{
    int width;
    int height;

    // First we need to save some OpenGL states on the attribute stack
    GLCall(glPushAttrib(GL_VIEWPORT_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT)) // Save the current viewport info, enabled info and context information
    
    // Now we need to save our current projection matrix and create a new one that is from (0,0, -1) to (w, h, 1) (instead of -1, 1)
    GLCall(glMatrixMode(GL_PROJECTION))
    GLCall(glPushMatrix()) // Push the prokjection matrix to the stack
    GLCall(glLoadIdentity())
    
    // Create our new projection matrix
    width   = glutGet(GLUT_WINDOW_WIDTH);
    height  = glutGet(GLUT_WINDOW_HEIGHT);     
    GLCall(glOrtho(0.0f, width, 0.0f, height, -1.0f, 1.0f))
    
    // Now we need to save the current MODELVIEW matrix
    GLCall(glMatrixMode(GL_MODELVIEW))
    GLCall(glPushMatrix())
    GLCall(glLoadIdentity())
    
    GLCall(glColor3f(1.0f, 1.0f, 1.0f)) // Set the raster color
    GLCall(glRasterPos2i(x, height - 13 - y)) // Invert the y position so (0, 0) is the top left corner!
    
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c); // Draw the character!!!

    // Now we need to restore the previous GL state
    GLCall(glPopMatrix()) // Restore MODELVIEW...

    GLCall(glMatrixMode(GL_PROJECTION))
    GLCall(glPopMatrix())
    
    GLCall(glPopAttrib());
}

void r_drawString(int x, int y, const char* msg)
{
    while(*msg != '\0')
    {
        r_drawCharacter(x, y, *msg++);
        
        x += 8;
    }
}
