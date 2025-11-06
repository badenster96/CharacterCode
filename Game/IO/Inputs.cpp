#include "IO/Inputs.h"
#include <iostream>

Inputs::Inputs()
{
    // Initialize all key states
    isMovingLeft = false;
    isMovingRight = false;
    isMovingUp = false;
    isMovingDown = false;
    isZoomingIn = false;
    isZoomingOut = false;
    isJumping = false;
    isSprinting = false; // Added

    // Initialize mouse deltas
    mouseDeltaX = 0.0;
    mouseDeltaY = 0.0;
    wheelDelta = 0.0;

    // Initialize window center (Scene will update this)
    windowCenterX = 0;
    windowCenterY = 0;

    wParam = 0;
}

Inputs::~Inputs()
{
    //dtor
}

void Inputs::keyPressed()
{
    switch(wParam)
    {
        // --- Movement ---
        case VK_LEFT:   isMovingLeft = true;    break;
        case 'A':       isMovingLeft = true;    break;
        case VK_RIGHT:  isMovingRight = true;   break;
        case 'D':       isMovingRight = true;   break;
        case VK_DOWN:   isMovingDown = true;    break;
        case 'S':       isMovingDown = true;    break;
        case VK_UP:     isMovingUp = true;      break;
        case 'W':       isMovingUp = true;      break;

        // --- Actions ---
        case VK_SPACE:  isJumping = true;       break;
        case VK_SHIFT:  isSprinting = true;     break; // Added

        // --- Zoom ---
        case VK_ADD:      isZoomingIn = true;   break;
        case VK_SUBTRACT: isZoomingOut = true;  break;
    }
}

void Inputs::keyUp()
{
    switch(wParam)
    {
        // --- Movement ---
        case VK_LEFT:   isMovingLeft = false;   break;
        case 'A':       isMovingLeft = false;   break;
        case VK_RIGHT:  isMovingRight = false;  break;
        case 'D':       isMovingRight = false;  break;
        case VK_DOWN:   isMovingDown = false;   break;
        case 'S':       isMovingDown = false;   break;
        case VK_UP:     isMovingUp = false;     break;
        case 'W':       isMovingUp = false;     break;

        // --- Actions ---
        case VK_SPACE:  isJumping = false;      break;
        case VK_SHIFT:  isSprinting = false;    break; // Added

        // --- Zoom ---
        case VK_ADD:      isZoomingIn = false;  break;
        case VK_SUBTRACT: isZoomingOut = false; break;
    }
}

void Inputs::mouseEventDown(double x, double y)
{
    // This is no longer used for camera rotation.
    // You can use this later for actions like "Fire" (MK_LBUTTON)
    // or "Aim" (MK_RBUTTON).
    
    // switch(wParam)
    // {
    //     case MK_LBUTTON: // Fire
    //         break;
    //     case MK_RBUTTON: // Aim
    //         break;
    // }
}

void Inputs::mouseEventUp()
{
    // This is no longer used for camera rotation.
    // Use this to stop firing, aiming, etc.
}

void Inputs::mouseWheel(double delta)
{
    // 'delta' is usually 120 or -120.
    // Divide by 120 to get a normalized -1.0 or 1.0.
    wheelDelta = delta / 120.0;
}

void Inputs::mouseMove(double x, double y)
{
    // Compute delta from window center
    mouseDeltaX = (x - windowCenterX);
    mouseDeltaY = (y - windowCenterY);

    // Recenter cursor immediately
    POINT center = { windowCenterX, windowCenterY };
    HWND hwnd = GetForegroundWindow(); // assumes active game window
    ClientToScreen(hwnd, &center);
    SetCursorPos(center.x, center.y);
}


void Inputs::setWindowCenter(int width, int height) {
    windowCenterX = width / 2;
    windowCenterY = height / 2;
}