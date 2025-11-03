#include "Inputs.h"

Inputs::Inputs()
{
    //ctor
    Mouse_Rotate = false;
    Mouse_Translate = false;

    // Initialize all states
    isMovingLeft = false;
    isMovingRight = false;
    isMovingUp = false;
    isMovingDown = false;
    isZoomingIn = false;
    isZoomingOut = false;

    prev_Mouse_X = 0.0;
    prev_Mouse_Y = 0.0;
    mouseDeltaX = 0.0;
    mouseDeltaY = 0.0;
    wheelDelta = 0.0;

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
        case VK_LEFT:   isMovingLeft = true;   break;
        case VK_RIGHT:  isMovingRight = true;  break;
        case VK_DOWN:   isMovingDown = true;   break;
        case VK_UP:     isMovingUp = true;     break;
        case VK_ADD:    isZoomingIn = true;    break; // Fixed
        case VK_SUBTRACT: isZoomingOut = true; break; // Fixed
    }
}

void Inputs::keyUp()
{
    switch(wParam)
    {
        case VK_LEFT:   isMovingLeft = false;   break;
        case VK_RIGHT:  isMovingRight = false;  break;
        case VK_DOWN:   isMovingDown = false;   break;
        case VK_UP:     isMovingUp = false;     break;
        case VK_ADD:    isZoomingIn = false;    break;
        case VK_SUBTRACT: isZoomingOut = false; break;
    }
}

void Inputs::mouseEventDown(double x, double y)
{
    prev_Mouse_X = x;
    prev_Mouse_Y = y;

    switch(wParam)
    {
        case MK_LBUTTON:
            Mouse_Rotate = true;
            break;
        case MK_RBUTTON:
            // Mouse_Translate = true; // You had this commented out
            Mouse_Rotate = true;     // You had this enabled instead
            break;
        case MK_MBUTTON:
            break;
        default:
            break;
    }
}

void Inputs::mouseEventUp()
{
    Mouse_Rotate = false;
    Mouse_Translate = false;
}

void Inputs::mouseWheel(double delta)
{
    // Store the wheel movement. Scene will read it.
    wheelDelta = delta / 100.0;
}

//Controls mouse movement
void Inputs::mouseMove(double x, double y)
{
    // Calculate and store the delta (change in position)
    // The Scene will read these values
    mouseDeltaX = (x - prev_Mouse_X);
    mouseDeltaY = (y - prev_Mouse_Y);

    // Update the previous position for the next frame
    prev_Mouse_X = x;
    prev_Mouse_Y = y;
}
