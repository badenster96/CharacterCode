#pragma once
#include "Scene.h"
#include "Level.h"
#include <memory>

class LevelScene : public Scene {
public:
    LevelScene();
    ~LevelScene() override = default;

    void attachSystems(Inputs* inputs, Camera* camera) override;
    void update(float dt) override;
    void draw() override;
    void handleWinMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;

private:
    std::unique_ptr<Level> level;
    Inputs* kBMs;
    Camera* camera;
};
