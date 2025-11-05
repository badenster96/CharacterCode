#include "Scene.h"
#include <gl/glu.h>

Scene::Scene()
{
    kBMs = nullptr;
    camera = nullptr;
    foregroundPlx = nullptr;
    backgroundPlx = nullptr;
    screenWidth = 800;
    screenHeight = 600;
    lastFrameTicks = GetTickCount();
    level = nullptr;
}

Scene::~Scene()
{
    if (kBMs) delete kBMs;
    if (camera) delete camera;
    if (foregroundPlx) delete foregroundPlx;
    if (backgroundPlx) delete backgroundPlx;
    if (level) delete level;
}

GLint Scene::initGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    kBMs = new Inputs();
    camera = new Camera();

    foregroundPlx = new Parallax();
    backgroundPlx = new Parallax();
    foregroundPlx->parallaxInit("images/floor.png");
    backgroundPlx->parallaxInit("images/p.jpg");

    level = new Level();
    level->init();

    reSizeScene(screenWidth, screenHeight);
    ShowCursor(FALSE);
    return true;
}

GLint Scene::drawScene()
{
    DWORD currentFrameTicks = GetTickCount();
    float dt = (float)(currentFrameTicks - lastFrameTicks) / 1000.0f;
    lastFrameTicks = currentFrameTicks;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // --- Handle parallax scrolling ---
    float scrollX = - kBMs->mouseDeltaX * settings.cameraScrollScale;
    float scrollY = 0;//kBMs->mouseDeltaY * settings.cameraScrollScale;

    foregroundPlx->scroll(true, scrollX * settings.foregroundScrollSpeed, scrollY * settings.foregroundScrollSpeed);
    backgroundPlx->scroll(true, scrollX * settings.backgroundScrollSpeed, scrollY * settings.backgroundScrollSpeed);

    backgroundPlx->draw();
    foregroundPlx->draw();

    // --- 3D Level ---
    level->update(dt, camera, kBMs);
    level->draw();

    return true;
}

GLvoid Scene::reSizeScene(int width, int height)
{
    screenWidth = width;
    screenHeight = height;
    if (height == 0) height = 1;

    GLfloat aspectRatio = (GLfloat)width / (float)height;
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspectRatio, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (kBMs) {
        kBMs->windowCenterX = width / 2;
        kBMs->windowCenterY = height / 2;
    }
}

int Scene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (!kBMs) return 0;
    kBMs->wParam = wParam;
    switch (uMsg)
    {
        case WM_KEYDOWN: kBMs->keyPressed(); break;
        case WM_KEYUP:   kBMs->keyUp(); break;
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
            kBMs->mouseEventDown(LOWORD(lParam), HIWORD(lParam));
            break;
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
            kBMs->mouseEventUp();
            break;
        case WM_MOUSEMOVE:
        {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            kBMs->mouseMove(x,y);
            if (x != kBMs->windowCenterX || y != kBMs->windowCenterY)
            {
                POINT center;
                center.x = kBMs->windowCenterX;
                center.y = kBMs->windowCenterY;
                ClientToScreen(hWnd, &center);
                SetCursorPos(center.x, center.y);
            }
            break;
        }
        case WM_MOUSEWHEEL:
            kBMs->mouseWheel((double)GET_WHEEL_DELTA_WPARAM(wParam));
            break;
    }
    return 0;
}
