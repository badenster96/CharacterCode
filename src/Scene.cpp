#include "Scene.h"

// Include all your class headers
#include "Light.h"
#include "_3DModelLoader.h" // <-- ADDED
#include "Inputs.h"
#include "Parallax.h"
#include "TextureLoader.h"
#include <gl/glu.h> // For gluOrtho2D

// --- Constructor ---
Scene::Scene()
{
    // myModel = nullptr; // <-- REMOVED
    myAvatar = nullptr; // <-- ADDED
    kBMs = nullptr;
    foregroundPlx = nullptr;
    backgroundPlx = nullptr;
    road = nullptr;
    bg = nullptr;
    mainLight = nullptr;
    cameraX = 0.0f;
    cameraY = 0.0f;
    cameraZ = 20.0f;
    screenWidth = 800;
    screenHeight = 600;
    lastFrameTicks = GetTickCount();
    roadRotationY = 0.0f;
}

// --- Destructor ---
Scene::~Scene()
{
    // if (myModel) delete myModel; // <-- REMOVED
    if (myAvatar) delete myAvatar; // <-- ADDED
    if (kBMs) delete kBMs;
    if (foregroundPlx) delete foregroundPlx;
    if (backgroundPlx) delete backgroundPlx;
    if (road) delete road;
    if (bg) delete bg;
    if (mainLight) delete mainLight;
}

// --- initGL ---
GLint Scene::initGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_TEXTURE_2D);

    // --- Transparency ---
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // --- Lighting ---
    mainLight = new Light(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    // --- Instantiate Scene Objects ---
    myAvatar = new _3DModelLoader(); // <-- ADDED
    kBMs = new Inputs();
    foregroundPlx = new Parallax();
    backgroundPlx = new Parallax();
    road = new TextureLoader();
    bg = new TextureLoader();

    // --- Load Textures and Models ---
    // Make sure these paths are correct!
    // You may need "../models/Tekk/tris.md2"
    myAvatar->initModel("models/Tekk/tris.md2"); // <-- ADDED

    // You may need "../images/road.jpg"
    road->loadTexture("images/road.jpg");
    bg->loadTexture("images/sky.png");
    foregroundPlx->parallaxInit("images/floor.png");
    backgroundPlx->parallaxInit("images/p.jpg");

    reSizeScene(screenWidth, screenHeight);
    return true;
}

// --- drawScene ---
GLint Scene::drawScene()
{
    // --- Delta Time Calculation ---
    DWORD currentFrameTicks = GetTickCount();
    float dt = (float)(currentFrameTicks - lastFrameTicks) / 1000.0f;
    lastFrameTicks = currentFrameTicks;

    // --- Scene Setup ---
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Note: glLoadIdentity() will be called in each projection block

    // --- Input Logic (Run this first) ---
    float foreSpeed = 0.1f;
    float backSpeed = 0.05f;
    float roadSpinSpeed = 50.0f;
    float zoomSpeed = 0.01f;

    if (kBMs->isMovingLeft) {
        foregroundPlx->scroll(true, "left", foreSpeed * dt);
        backgroundPlx->scroll(true, "left", backSpeed * dt);
        roadRotationY += roadSpinSpeed * dt;
        myAvatar->walk();
        myAvatar->rotateY = 270; // Face left
    } else if (kBMs->isMovingRight) {
        foregroundPlx->scroll(true, "right", foreSpeed * dt);
        backgroundPlx->scroll(true, "right", backSpeed * dt);
        roadRotationY-= roadSpinSpeed * dt;
        myAvatar->walk();
        myAvatar->rotateY = 90; // Face right
    } else if (kBMs->isMovingUp) {
        //foregroundPlx->scroll(true, "left", foreSpeed * dt);
        //backgroundPlx->scroll(true, "left", backSpeed * dt);
        //roadRotationY += roadSpinSpeed * dt;
        cameraZ -= zoomSpeed;
        myAvatar->walk();
        myAvatar->rotateY = 180; // Face left
    } else if (kBMs->isMovingDown) {
        //foregroundPlx->scroll(true, "right", foreSpeed * dt);
        //backgroundPlx->scroll(true, "right", backSpeed * dt);
        //roadRotationY-= roadSpinSpeed * dt;
        cameraZ += zoomSpeed;
        myAvatar->walk();
        myAvatar->rotateY = 0; // Face right
    } else {
        myAvatar->stand(); // Not moving
    }

    myAvatar->update(dt); // Update animation state

    // 3. Mouse & Zoom Logic
    if (kBMs->Mouse_Rotate) {
        myAvatar->rotateY += kBMs->mouseDeltaX / 3.0;
        myAvatar->rotateX += kBMs->mouseDeltaY / 3.0;
    }
    if (kBMs->Mouse_Translate) {
        myAvatar->translate(kBMs->mouseDeltaX / 100.0, -kBMs->mouseDeltaY / 100.0, 0);
    }
    if (kBMs->wheelDelta != 0.0) {
        myAvatar->translate(0, 0, kBMs->wheelDelta);
    }
    if (kBMs->isZoomingIn) {
        myAvatar->translate(0, 0, 0.1 * dt);
    }
    if (kBMs->isZoomingOut) {
        myAvatar->translate(0, 0, -0.1 * dt);
    }

    // Reset deltas
    kBMs->mouseDeltaX = 0.0;
    kBMs->mouseDeltaY = 0.0;
    kBMs->wheelDelta = 0.0;


    // --- 1. 2D DRAWING (MUST COME FIRST) ---
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST); // No depth test for 2D background
    glDisable(GL_LIGHTING);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // 1. Static Sky
    bg->bind();
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex2f(0.0, 0.0);
        glTexCoord2f(1.0, 0.0); glVertex2f(1.0, 0.0);
        glTexCoord2f(1.0, 1.0); glVertex2f(1.0, 1.0);
        glTexCoord2f(0.0, 1.0); glVertex2f(0.0, 1.0);
    glEnd();

    // 2. Parallax Layers
    backgroundPlx->drawSquare();

    glPushMatrix(); // For scaling the foreground
        glScalef(1.0, 1.0, 1.0); // Scale to 50% height
        foregroundPlx->drawSquare();
    glPopMatrix();

    // --- Restore 3D Matrix state ---
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();


    // --- 2. 3D DRAWING (MUST COME SECOND) ---
    // (The projection matrix is already set from reSizeScene, but we
    // could reset it here if we wanted to be extra safe)

    glMatrixMode(GL_MODELVIEW); // Make sure we are in modelview
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    // Enable 3D states
    glEnable(GL_DEPTH_TEST); // Enable depth test for 3D objects
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Draw the Road
    glPushMatrix();
        glTranslatef(0.0f, -5.2f, -15.0f);
        glRotatef(roadRotationY, 0.0f, 1.0f, 0.0f);
        glScalef(50.0f, 1.0f, 50.0f);
        road->bind();
        glNormal3f(0.0f, 1.0f, 0.0f);
        float textureAspectRatio = 1.0f;

        if(road->height > 0){
            textureAspectRatio = (float)road->width / (float)road->height;
        }
        float roadTile_T = 5.0f;
        float roadTile_S = roadTile_T * textureAspectRatio;
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 0.0f,  1.0f);
            glTexCoord2f(roadTile_S, 0.0f); glVertex3f( 1.0f, 0.0f,  1.0f);
            glTexCoord2f(roadTile_S, roadTile_T); glVertex3f( 1.0f, 0.0f, -1.0f);
            glTexCoord2f(0.0f, roadTile_T); glVertex3f(-1.0f, 0.0f, -1.0f);
        glEnd();
    glPopMatrix();

    // Draw the Avatar
    glPushMatrix();
        // Position the avatar on the "floor"
        glTranslatef(0.0, -3.0, cameraZ - 20.0f);
        glScalef(0.05, 0.05, 0.05);
        myAvatar->Draw();
    glPopMatrix();

    return true;
}
// --- reSizeScene ---
GLvoid Scene::reSizeScene(int width, int height)
{
    // ... (no changes) ...
    screenWidth = width;
    screenHeight = height;
    if (height == 0) height = 1;
    GLfloat aspectRatio = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspectRatio, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// --- winMsg ---
int Scene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // ... (no changes) ...
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
            kBMs->mouseMove(LOWORD(lParam), HIWORD(lParam));
            break;
        case WM_MOUSEWHEEL:
            kBMs->mouseWheel((double)GET_WHEEL_DELTA_WPARAM(wParam));
            break;
    }
    return 0;
}
