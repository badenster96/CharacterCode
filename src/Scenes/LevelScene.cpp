#include "Scenes/LevelScene.h"
#include "Scenes/Level.h"

// Constructor
LevelScene::LevelScene() {
    level = std::make_unique<Level>();
}

// Attach shared systems (camera, inputs)
void LevelScene::attachSystems(Inputs* sharedInputs, Camera* sharedCamera) {
    kBMs = sharedInputs;
    camera = sharedCamera;

    // Pass shared systems to the Level
    level->attachSystems(kBMs, camera);
}

// Update the scene every frame
void LevelScene::update(float dt) {
    if (level) level->update(dt);
}

// Draw the scene
void LevelScene::draw() {
    if (level) level->draw();
}

// Handle Windows messages
void LevelScene::handleWinMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (level) level->handleWinMsg(hWnd, uMsg, wParam, lParam);
}
