#include "Parallax.h"
#include "TextureLoader.h"
#include <gl/glut.h>
#include <iostream>
#include <iomanip>

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

void Parallax::draw()
{
    glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    if(!bTex) return;
    bTex->bind();
    glBegin(GL_QUADS);
        glTexCoord2f(xMin, yMax); glVertex2f(0.0, 0.0); // bottom-left
        glTexCoord2f(xMax, yMax); glVertex2f(1.0, 0.0); // bottom-right
        glTexCoord2f(xMax, yMin); glVertex2f(1.0, 1.0); // top-right
        glTexCoord2f(xMin, yMin); glVertex2f(0.0, 1.0); // top-left
    glEnd();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glPopAttrib();
}

void Parallax::parallaxInit(const char* fileName)
{
    bTex->loadTexture(fileName);
}

void Parallax::scroll(bool autoScroll, float speedX, float speedY)
{
    if (!autoScroll) return;

    // Horizontal scroll
    xMin += speedX;
    xMax += speedX;

    // Vertical scroll
    yMin += speedY;
    yMax += speedY;
}