#include "Parallax.h"
#include "TextureLoader.h"
#include <gl/glut.h>

Parallax::Parallax()
{
    bTex = new TextureLoader();
    xMax = 1.0;
    yMax = 1.0;
    xMin = 0.0;
    yMin = 0.0;
}

Parallax::~Parallax()
{
    delete bTex;
}

// CHANGED: This function now draws a simple 2D quad
// that will fill a (0,0) to (1,1) orthographic view.
void Parallax::drawSquare()
{
    glColor3f(1.0, 1.0, 1.0);
    bTex->bind();

    glBegin(GL_POLYGON);
        // OLD: glTexCoord2f(xMin, yMin);
        glTexCoord2f(xMin, yMax); // <-- FIX
        glVertex2f(0.0, 0.0); // bottom-left

        // OLD: glTexCoord2f(xMax, yMin);
        glTexCoord2f(xMax, yMax); // <-- FIX
        glVertex2f(1.0, 0.0); // bottom-right

        // OLD: glTexCoord2f(xMax, yMax);
        glTexCoord2f(xMax, yMin); // <-- FIX
        glVertex2f(1.0, 1.0); // top-right

        // OLD: glTexCoord2f(xMin, yMax);
        glTexCoord2f(xMin, yMin); // <-- FIX
        glVertex2f(0.0, 1.0); // top-left
    glEnd();
}

void Parallax::parallaxInit(const char* fileName)
{
    bTex->loadTexture(fileName);
}

void Parallax::scroll(bool Auto, string dir, float speed)
{
    if(Auto)
    {
        if(dir == "up")
        {
            yMin -= speed;
            yMax -= speed;
        }
        else if(dir == "down")
        {
            yMin += speed;
            yMax += speed;
        }
        else if(dir == "left")
        {
            xMin -= speed;
            xMax -= speed;
        }
        else if(dir == "right")
        {
            xMin += speed;
            xMax += speed;
        }
    }
}
