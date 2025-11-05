#pragma once
#include "Graphics/Light.h"
#include "Graphics/_3DModelLoader.h"
#include "Entities/Player.h"
#include "Graphics/TextureLoader.h"
#include "Graphics/Camera.h"
#include "IO/Inputs.h"
#include <windows.h>
#include <gl/glu.h>

class Level {
public:
    Level();
    ~Level();

    void init();
    void update(float dt, Camera* camera, Inputs* kBMs);
    void draw();

private:
    Light* mainLight;
    Player* myAvatar;
    TextureLoader* road;

    float playerPosX, playerPosY, playerPosZ;
};
