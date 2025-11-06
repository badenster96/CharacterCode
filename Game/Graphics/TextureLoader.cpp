#include "Graphics/TextureLoader.h"
#include <iostream> // For error messages

TextureLoader::TextureLoader() : textID(0), width(0), height(0)
{
    // Constructor: Initialize textID to 0
}

TextureLoader::~TextureLoader()
{
    // Destructor: Clean up the texture from GPU memory
    if (textID != 0)
    {
        glDeleteTextures(1, &textID);
    }
}

bool TextureLoader::loadTexture(const char* fileName)
{
    unsigned char* image = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGBA);

    if (!image)
    {
        std::cout << "Error: Texture file '" << fileName << "' did not load." << std::endl;
        return false;
    }

    // Generate the texture ID if it doesn't exist
    if (textID == 0)
    {
        glGenTextures(1, &textID);
    }

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, textID);

    // Set texture wrapping to repeat
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture filtering for better quality
    // GL_LINEAR_MIPMAP_LINEAR is best for minification (zoomed out)
    // GL_LINEAR is best for magnification (zoomed in)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // Build the texture and its mipmaps
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);

    // Free the image data from RAM (it's now on the GPU)
    SOIL_free_image_data(image);

    return true;
}

void TextureLoader::bind()
{
    // The scene should handle glEnable(GL_TEXTURE_2D)
    // This class should only bind.
    glBindTexture(GL_TEXTURE_2D, textID);
}

void TextureLoader::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint TextureLoader::getID() const
{
    return textID;
}
