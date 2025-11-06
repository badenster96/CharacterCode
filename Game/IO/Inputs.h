#pragma once
#include <windows.h>

/**
 * @class Inputs
 * @brief Handles all raw keyboard and mouse input from the OS.
 * This class acts as a state machine. The Scene::winMsg function sends
 * events to this class, which updates boolean flags (like 'isMovingLeft').
 * The Scene::drawScene function then reads these flags to perform actions.
 */
class Inputs
{
public:
    Inputs();
    virtual ~Inputs();

    // --- Keyboard Functions ---
    void keyPressed();
    void keyUp();

    // --- Mouse Functions ---
    void mouseEventDown(double x, double y);
    void mouseEventUp();
    void mouseWheel(double delta);
    void mouseMove(double x, double y);
    void setWindowCenter(int width, int height);

    // --- Keyboard State (for Scene to read) ---
    bool isMovingLeft;
    bool isMovingRight;
    bool isMovingUp;
    bool isMovingDown;
    bool isZoomingIn;
    bool isZoomingOut;
    bool isJumping;
    bool isSprinting; // Added

    // --- Mouse State (for Scene to read) ---
    double mouseDeltaX; // Change in mouse X (from center)
    double mouseDeltaPrevX; // Previous change in mouse X (from center)
    double mouseDeltaY; // Change in mouse Y (from center)
    double mouseDeltaPrevY; // Previous change in mouse Y (from center)
    double wheelDelta;  // Mouse wheel scroll amount

    // --- Window State (for Scene to set) ---
    int windowCenterX; // Center of the window (set by Scene::reSizeScene)
    int windowCenterY; // Center of the window (set by Scene::reSizeScene)

    // --- Event Data ---
    WPARAM wParam; // Scene will set this with the key/mouse code

protected:
private:
    // 'prev_Mouse_X/Y' and 'Mouse_Rotate' are no longer needed
    // for the re-centering mouselook system.
};
