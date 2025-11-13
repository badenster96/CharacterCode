#pragma once
#include "Scenes/Scene.h"
#include "IO/Inputs.h"
#include "Graphics/Camera.h"
#include "Graphics/Parallax.h"
#include "Graphics/TextureLoader.h"
#include "Entities/Player.h"
#include "Graphics/Light.h"
#include "Helpers/Settings.h"

#include <memory>

class Level : public Scene {
public:
    Level();
    ~Level();

    // --- Scene interface ---
    void attachSystems(Inputs* inputs, Camera* camera) override;
    void update(float dt) override;
    void draw() override;
    void handleWinMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;

    // --- Level-specific ---
    void init();

private:
    Inputs* kBMs;       // Shared input system
    Camera* camera;     // Shared camera system

    // Level objects
    std::unique_ptr<Player> myAvatar;
    std::unique_ptr<Light> mainLight;
    std::unique_ptr<TextureLoader> road;
    std::unique_ptr<Parallax> foregroundPlx;
    std::unique_ptr<Parallax> backgroundPlx;
};
