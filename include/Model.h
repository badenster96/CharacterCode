#pragma once

#include <windows.h>
#include <GL/glut.h>
#include <iostream>

// Forward declaration
class TextureLoader;

class Model
{
    public:
        Model();
        virtual ~Model();

        // --- Public Methods ---

        // Load the model's texture
        void initModel(const char* texturePath);

        // Draw the model in its current state
        void drawModel();

        // Methods to change the model's state
        void setPosition(double x, double y, double z);
        void setRotation(double rx, double ry, double rz);
        void setScale(double s);

        // Methods to adjust the model's state
        void rotate(double angle, double x, double y, double z);
        void translate(double dx, double dy, double dz);

        // Public variables for mouse control (as used by _inputs)
        // A better design might be setRotation, but this matches your existing code.
        double rotateX;
        double rotateY;
        double rotateZ;
        double scale;

    private:
        // --- Private Member Variables ---
        // All model data is now private and protected

        double posX;
        double posY;
        double posZ;

        // The model now owns its texture loader
        TextureLoader* tex;
};