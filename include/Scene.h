#pragma once
#include <windows.h>
#include "IO/Inputs.h"
#include "Graphics/Camera.h"

class Scene {
public:
    virtual ~Scene() = default;

    // Attach shared systems (inputs, camera)
    virtual void attachSystems(Inputs* inputs, Camera* camera) = 0;

    // Called every frame
    virtual void update(float dt) = 0;
    virtual void draw() = 0;

    // Handle OS-level messages
    virtual void handleWinMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
};
