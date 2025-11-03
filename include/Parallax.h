#pragma once

#include <iostream>
#include <string>
#include <gl/gl.h>
#include <windows.h>

using namespace std;

// Forward declaration is cleaner in a header
class TextureLoader;

class Parallax
{
    public:
        Parallax();
        virtual ~Parallax();

        void drawSquare(); // <-- CHANGED
        void parallaxInit(const char* fileName);
        void scroll(bool, string, float);

    private:
        TextureLoader* bTex;
        float xMax, yMax, xMin, yMin; // For texture coordinates
};