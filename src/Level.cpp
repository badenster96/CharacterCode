#include "Level.h"

Level::Level() {
    mainLight = nullptr;
    myAvatar = nullptr;
    road = nullptr;

    playerPosX = 0.0f;
    playerPosY = -3.0f;
    playerPosZ = 0.0f;
}

Level::~Level() {
    if (mainLight) delete mainLight;
    if (myAvatar) delete myAvatar;
    if (road) delete road;
}

void Level::init() {
    mainLight = new Light(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    myAvatar = new Player();
    road = new TextureLoader();

    myAvatar->initModel("models/Tekk/tris.md2");
    road->loadTexture("images/road.jpg");
}

void Level::update(float dt, Camera* camera, Inputs* kBMs) {
    myAvatar->handleInputAndMove(dt, camera, kBMs, {});
}

void Level::draw() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // --- Draw road ---
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

    // --- Draw player avatar ---
    glPushMatrix();
        myAvatar->drawModel();
    glPopMatrix();
}
