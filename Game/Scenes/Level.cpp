#include "Scenes/Level.h"
#include <gl/gl.h>
#include <gl/glu.h>

Level::Level()
    : kBMs(nullptr), camera(nullptr)
{}

Level::~Level() = default;

void Level::attachSystems(Inputs* inputs, Camera* cam) {
    kBMs = inputs;
    camera = cam;
}

void Level::init() {
    mainLight = std::make_unique<Light>(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    myAvatar = std::make_unique<Player>();
    myAvatar->initModel("models/Tekk/tris.md2");

    road = std::make_unique<TextureLoader>();
    road->loadTexture("images/road.jpg");

    foregroundPlx = std::make_unique<Parallax>();
    foregroundPlx->parallaxInit("images/floor.png");

    backgroundPlx = std::make_unique<Parallax>();
    backgroundPlx->parallaxInit("images/p.jpg");
}

void Level::update(float dt) {
    if (camera && kBMs) {
        camera->update(kBMs, dt);  // <--- important
    }
    if (myAvatar && camera && kBMs) {
        myAvatar->handleInputAndMove(dt, camera, kBMs, {});
    }
}

void Level::draw() {
    if (!kBMs) return;
    auto& s = Settings::get();

    // --- Parallax background ---
    
    bool isMLeftDebug = false;

    glDisable(GL_DEPTH_TEST); // draw background without depth test
    glDisable(GL_LIGHTING);
    float parallaxScrollFore = -kBMs->mouseDeltaPrevX * s.cameraScrollScale;
    float parallaxScrollBack = -kBMs->mouseDeltaPrevX * s.cameraScrollScale;
    //std::cout << "MouseX: " << kBMs->mouseDeltaPrevX << "|MouseY: " << kBMs->mouseDeltaPrevY << std::endl;

    glPushMatrix();
    foregroundPlx->scroll(true, parallaxScrollFore * s.foregroundScrollSpeed, 0.0f);
    backgroundPlx->scroll(true, parallaxScrollBack * s.backgroundScrollSpeed, 0.0f);
    backgroundPlx->draw();
    foregroundPlx->draw();
    glPopMatrix();

    // --- 3D objects ---
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    if (camera) {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        camera->setTarget(myAvatar->getPosition().x, myAvatar->getPosition().y, myAvatar->getPosition().z);
        camera->applyView();   // <--- this positions the camera properly
    }
    // Road
    glPushMatrix();
        glTranslatef(0.0f, -5.2f, 0.0f);
        glScalef(200.0f, 1.0f, 200.0f);
        road->bind();
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 0.0f, 1.0f);
            glTexCoord2f(50.0f, 0.0f); glVertex3f(1.0f, 0.0f, 1.0f);
            glTexCoord2f(50.0f, 50.0f); glVertex3f(1.0f, 0.0f, -1.0f);
            glTexCoord2f(0.0f, 50.0f); glVertex3f(-1.0f, 0.0f, -1.0f);
        glEnd();
    glPopMatrix();

    // Player
    myAvatar->drawModel();
}


void Level::handleWinMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (!kBMs) return;

    kBMs->wParam = wParam;
    switch (uMsg) {
        case WM_KEYDOWN: kBMs->keyPressed(); break;
        case WM_KEYUP:   kBMs->keyUp(); break;
        case WM_LBUTTONDOWN: case WM_RBUTTONDOWN: case WM_MBUTTONDOWN:
            kBMs->mouseEventDown(LOWORD(lParam), HIWORD(lParam)); break;
        case WM_LBUTTONUP: case WM_RBUTTONUP: case WM_MBUTTONUP:
            kBMs->mouseEventUp(); break;
        case WM_MOUSEMOVE:
            kBMs->mouseMove(LOWORD(lParam), HIWORD(lParam));
            break;
        case WM_MOUSEWHEEL:
            kBMs->mouseWheel((double)GET_WHEEL_DELTA_WPARAM(wParam));
            break;
    }
}
