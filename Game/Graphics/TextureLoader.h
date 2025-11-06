#pragma once

// This should include gl.h, glu.h, and glut.h
// If _common.h doesn't, you might need to include <GL/glut.h> directly
#include "Helpers/Common.h"
#include "External/SOIL.h"
#include <GL/glu.h> // For mipmapping

class TextureLoader
{
    public:
        TextureLoader();
        virtual ~TextureLoader();

        /**
         * Loads a texture from a file and generates mipmaps.
         * @param fileName The path to the image file.
         * @return true if loading was successful, false otherwise.
         */
        bool loadTexture(const char* fileName);

        /**
         * Binds this texture to be the active GL_TEXTURE_2D.
         */
        void bind();

        /**
         * Unbinds the active GL_TEXTURE_2D (binds to 0).
         */
        static void unbind();

        /**
         * @return The OpenGL texture ID.
         */
        GLuint getID() const;

        int width;
        int height;

    private:
        GLuint textID; // The OpenGL texture handle (ID)
};