#include "Model.h"
#include "TextureLoader.h"
#include <GL/glut.h> // For glutSolidTorus
#include <cmath>     // For math

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
    scaleX = 1.0;
    scaleY = 1.0;
    scaleZ = 1.0;

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
// This is the "default" draw function.
// Player will override this.
void Model::drawModel()
{
    // Bind this model's specific texture
    tex->bind();

    // Set a default color
    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();

        // Apply transformations based on member variables
        glTranslated(posX, posY, posZ);
        glRotated(rotateX, 1, 0, 0);
        glRotated(rotateY, 0, 1, 0);
        glRotated(rotateZ, 0, 0, 1);
        glScaled(scaleX, scaleY, scaleZ); // Use 3D scale

        // Draw the default shape
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

void Model::setScale(double sx, double sy, double sz)
{
    scaleX = sx;
    scaleY = sy;
    scaleZ = sz;
}

// --- Adjustment Methods ---

void Model::translate(double dx, double dy, double dz)
{
    posX += dx;
    posY += dy;
    posZ += dz;
}
void Model::setObjectID(int newObjID) {
    objectID = newObjID;
}
int Model::getObjectID() {
    return objectID;
}