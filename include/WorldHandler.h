#pragma once
#include "Entities/Player.h"
#include "Graphics/TextureLoader.h"
#include "IO/Inputs.h"
#include "Graphics/Camera.h"
#include "Graphics/Parallax.h"

struct WorldSettings {
    float playerBaseSpeed = 5.0f;
    float playerSprintMultiplier = 2.0f;
    float cameraScrollScale = 0.01f;
    float foregroundScrollSpeed = 1.0f;
    float backgroundScrollSpeed = 0.5f;
};

class WorldHandler
{
public:
    WorldHandler();
    ~WorldHandler();

    void init();
    void update(float dt, Inputs* kBMs);
    void draw();

    float getCameraYaw() const;

private:
    Player* player;
    TextureLoader* road;
    TextureLoader* bg;
    Parallax* foregroundPlx;
    Parallax* backgroundPlx;
    Camera camera;
    Settings settings;
};
