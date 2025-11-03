#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "gameplay/Attack.h"
// Forward-declare TextureLoader to avoid including the header here
class TextureLoader;


class Model 
{
public:
    Model();
    // Base class destructors MUST be virtual
    virtual ~Model(); 

    // Public interface for initialization
    virtual void initModel(const char* texturePath);
    
    // This is now virtual, so Player can override it
    virtual void drawModel(); 

    // --- Public "Mutator" Methods ---
    void setPosition(double x, double y, double z);
    void setRotation(double rx, double ry, double rz);
    void setScale(double sx, double sy, double sz);
    void translate(double dx, double dy, double dz);

    // Check functions
    bool isAlive;
    void setObjectID(int newObjID);
    int getObjectID();
protected: 
    // Protected so derived classes (Player) can access them
    double rotateX, rotateY, rotateZ;
    double posX, posY, posZ;
    double scaleX, scaleY, scaleZ; // Changed from single 'scale'
    int objectID;
    std::vector<Attack> attacks;
    // The texture for this model.
    TextureLoader* tex; 
};

#endif // MODEL_H
