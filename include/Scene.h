#ifndef _SCENE_H
#define _SCENE_H

#include <windows.h>
#include <GL/glut.h>
#include <math.h>

// Forward declarations
class Inputs;
class Parallax;
class TextureLoader;
class Light;
class _3DModelLoader; // <-- ADD THIS

#ifndef M_PI
#define M_PI 3.1415926535
#endif

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
        // --- Member Variables ---
        // _Model* myModel; // <-- REMOVED
        _3DModelLoader* myAvatar; // <-- ADDED

        Inputs* kBMs;
        Parallax* foregroundPlx;
        Parallax* backgroundPlx;
        TextureLoader* road;
        TextureLoader* bg;
        Light* mainLight;

        // --- Camera & Window ---
        float cameraX, cameraY, cameraZ;
        int screenWidth, screenHeight;

        // --- Time & Movement ---
        DWORD lastFrameTicks;
        float roadRotationY;
};

#endif // _SCENE_H
