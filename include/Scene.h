#pragma once

#include <windows.h>
#include "Helpers/Common.h"

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
 * @struct SceneSettings
 * @brief A container for all "magic numbers" and configuration
 * values for the scene, making them easy to edit in one place.
 */
struct SceneSettings
{
    // --- Player Movement ---
    float playerBaseSpeed;
    float playerSprintMultiplier;

    // --- Camera Control ---
    float mouseSensitivity;
    float keyZoomSpeed;
    float wheelZoomAmount;
    float minZoomDistance;
    float maxZoomDistance;
    float minCameraPitch;
    float maxCameraPitch;

    // --- Parallax Background ---
    float foregroundScrollSpeed;
    float backgroundScrollSpeed;
    float cameraScrollScale; // <-- ADD THIS
};



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
    SceneSettings settings;
};

