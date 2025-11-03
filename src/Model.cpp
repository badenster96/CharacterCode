#include "Model.h"
#include "TextureLoader.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.1415926
#endif

// --- Constructor ---
Model::Model()
{
    // Initialize all variables
    rotateX = 0.0;
    rotateY = 0.0;
    rotateZ = 0.0;

    posX = 0.0;
    posY = 0.0;
    posZ = 0.0;

    scale = 1.0;

    // Create this model's own texture loader
    tex = new TextureLoader();
}

// --- Destructor ---
Model::~Model()
{
    // Clean up the memory for the texture loader
    if (tex)
    {
        delete tex;
    }
}

// --- initModel ---
// Load the texture for this specific model
void Model::initModel(const char* texturePath)
{
    tex->loadTexture(texturePath);
}

// --- drawModel ---
// Draw the model using its private member variables
void Model::drawModel()
{
    // Bind this model's specific texture
    tex->bind();

    // Set a default color (will be modulated by texture)
    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();

        // Apply transformations based on member variables
        glTranslated(posX, posY, posZ);
        glRotated(rotateX, 1, 0, 0); // Use the member variables
        glRotated(rotateY, 0, 1, 0);
        glRotated(rotateZ, 0, 0, 1);
        glScaled(scale, scale, scale);

        // Draw the shape
        glutSolidTorus(0.5, 1.5, 40, 40);

    glPopMatrix();
}

// --- Setter Methods ---

void Model::setPosition(double x, double y, double z)
{
    posX = x;
    posY = y;
    posZ = z;
}

void Model::setRotation(double rx, double ry, double rz)
{
    rotateX = rx;
    rotateY = ry;
    rotateZ = rz;
}

void Model::setScale(double s)
{
    scale = s;
}

// --- Adjustment Methods ---

void Model::rotate(double angle, double x, double y, double z)
{
    if (x > 0) rotateX += angle;
    if (y > 0) rotateY += angle;
    if (z > 0) rotateZ += angle;
}

void Model::translate(double dx, double dy, double dz)
{
    posX += dx;
    posY += dy;
    posZ += dz;
}
