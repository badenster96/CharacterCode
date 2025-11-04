#include "Scene.h"

#include "Graphics/Light.h"
#include "Graphics/_3DModelLoader.h"
#include "Entities/Player.h"
#include "IO/Inputs.h"
#include "Graphics/Parallax.h"
#include "Graphics/TextureLoader.h"
#include <gl/glu.h>
#include <cmath>

// --- Constructor ---
Scene::Scene()
{
    // --- 2. Initialize Member Pointers ---
    myAvatar = nullptr;
    // ... (rest is the same) ...
    kBMs = nullptr;
    foregroundPlx = nullptr;
    backgroundPlx = nullptr;
    road = nullptr;
    bg = nullptr;
    camera = nullptr;
    mainLight = nullptr;
    playerPos.x = 0.0f;
    playerPos.y = -3.0f;
    playerPos.z = 0.0f;
    cameraAngleY = 0.0f;
    cameraAngleX = 20.0f;
    cameraDistance = 10.0f;
    screenWidth = 800;
    screenHeight = 600;
    lastFrameTicks = GetTickCount();
}

// --- Destructor ---
// (Unchanged)
Scene::~Scene()
{
    if (myAvatar) delete myAvatar;
    if (kBMs) delete kBMs;
    if (foregroundPlx) delete foregroundPlx;
    if (backgroundPlx) delete backgroundPlx;
    if (road) delete road;
    if (bg) delete bg;
    if (mainLight) delete mainLight;
    if (camera) delete camera;
}

// --- initGL ---
// (Unchanged)
GLint Scene::initGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    mainLight = new Light(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    myAvatar = new Player();
    kBMs = new Inputs();
    foregroundPlx = new Parallax();
    backgroundPlx = new Parallax();
    road = new TextureLoader();
    bg = new TextureLoader();
    camera = new Camera();
    myAvatar->initModel("models/Tekk/tris.md2");
    road->loadTexture("images/road.jpg");
    bg->loadTexture("images/sky.png");
    foregroundPlx->parallaxInit("images/floor.png");
    backgroundPlx->parallaxInit("images/p.jpg");
    reSizeScene(screenWidth, screenHeight);
    ShowCursor(FALSE);
    return true;
}

// --- drawScene ---
GLint Scene::drawScene()
{
    // --- 1. DELTA TIME CALCULATION ---
    DWORD currentFrameTicks = GetTickCount();
    float dt = (float)(currentFrameTicks - lastFrameTicks) / 1000.0f;
    lastFrameTicks = currentFrameTicks;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Parallax sccrolling
    float scrollX = kBMs->mouseDeltaX * settings.cameraScrollScale;
    float scrollY = kBMs->mouseDeltaY * settings.cameraScrollScale;   
    foregroundPlx->scroll(true, scrollX * settings.foregroundScrollSpeed, 0.0f);
    backgroundPlx->scroll(true, scrollX * settings.backgroundScrollSpeed, 0.0f);


    backgroundPlx->draw();
    foregroundPlx->draw();

    // Player and camera movement handler
    myAvatar->handleInputAndMove(dt, camera, kBMs, settings);

    

    // --- 6. DRAW 3D SCENE (PERSPECTIVE) ---
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

        // Draw road
        glPushMatrix();
            glTranslatef(0.0f, -5.2f, 0.0f);
            glScalef(200.0f, 1.0f, 200.0f);
            road->bind();
            glNormal3f(0.0f, 1.0f, 0.0f);

            float textureAspectRatio = (road->height > 0) ? (float)road->width / (float)road->height : 1.0f;
            float roadTile_T = 50.0f;
            float roadTile_S = roadTile_T * textureAspectRatio;

            glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 0.0f);       glVertex3f(-1.0f, 0.0f,  1.0f);
                glTexCoord2f(roadTile_S, 0.0f); glVertex3f( 1.0f, 0.0f,  1.0f);
                glTexCoord2f(roadTile_S, roadTile_T); glVertex3f( 1.0f, 0.0f, -1.0f);
                glTexCoord2f(0.0f, roadTile_T);       glVertex3f(-1.0f, 0.0f, -1.0f);
            glEnd();
        glPopMatrix();

        // Draw player avatar
        glPushMatrix();
            //glScalef(0.05f, 0.05f, 0.05f);
            myAvatar->drawModel();
        glPopMatrix();
    }

    return true;
}

// --- reSizeScene ---
// (Unchanged)
GLvoid Scene::reSizeScene(int width, int height)
{
    screenWidth = width;
    screenHeight = height;
    if (height == 0) height = 1;
    GLfloat aspectRatio = (GLfloat)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspectRatio, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (kBMs) {
        kBMs->windowCenterX = width / 2;
        kBMs->windowCenterY = height / 2;
    }
}

// --- winMsg ---
// (Unchanged)
int Scene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (!kBMs) return 0;
    kBMs->wParam = wParam;
    switch (uMsg)
    {
        case WM_KEYDOWN:
            kBMs->keyPressed();
            break;
        case WM_KEYUP:
            kBMs->keyUp();
            break;
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
            kBMs->mouseMove(x, y);
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