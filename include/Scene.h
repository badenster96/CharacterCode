#pragma once

#include <windows.h>
#include "Helpers/Common.h"
#include "Graphics/Camera.h"
#include "Helpers/Settings.h"

// --- Forward Declarations ---
class Inputs;
class Parallax;
class TextureLoader;
class Light;
class _3DModelLoader;

// --- Constants ---
#ifndef M_PI
#define M_PI 3.1415926535
#endif



/**
 * @class Scene
 * @brief Manages all objects, logic, and rendering for the main game scene.
 */
class Scene
{
public:
    Scene();
    virtual ~Scene();

    GLint initGL();
    GLint drawScene();
    GLvoid reSizeScene(int width, int height);
    int winMsg(HWND, UINT, WPARAM, LPARAM);

private:
    // --- Scene Objects (Heap-allocated) ---
    _3DModelLoader* myAvatar;
    Inputs* kBMs;
    Parallax* foregroundPlx;
    Parallax* backgroundPlx;
    TextureLoader* road;
    TextureLoader* bg;
    Light* mainLight;
    Camera* camera;

    // --- Player & Camera State ---
    vec3  playerPos;
    float cameraAngleY;
    float cameraAngleX;
    float cameraDistance;

    // --- Window & Time ---
    int   screenWidth;
    int   screenHeight;
    DWORD lastFrameTicks;

    // --- CONFIGURATION ---
    Settings settings;
};

