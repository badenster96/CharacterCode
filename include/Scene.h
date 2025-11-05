#pragma once
#include "IO/Inputs.h"
#include "Graphics/Camera.h"
#include "Graphics/Parallax.h"
#include "Level.h"
#include <windows.h>
#include <gl/gl.h>

struct SceneSettings {
    float cameraScrollScale = 0.01f;
    float foregroundScrollSpeed = 0.1f;
    float backgroundScrollSpeed = 0.05f;
};

class Scene {
public:
    Scene();
    ~Scene();

    GLint initGL();
    GLint drawScene();
    GLvoid reSizeScene(int width, int height);
    int winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
    Inputs* kBMs;
    Camera* camera;
    Parallax* foregroundPlx;
    Parallax* backgroundPlx;
    SceneSettings settings;
    int screenWidth;
    int screenHeight;
    DWORD lastFrameTicks;

    Level* level;
};
