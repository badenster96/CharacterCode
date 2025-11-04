#pragma once
#include "IO/Inputs.h"
#include <gl/glu.h>

class Camera
{
public:
    Camera();
    ~Camera() = default;

    // Camera state
    float angleX;        // pitch
    float angleY;        // yaw
    float distance;

    // Settings
    float minPitch;
    float maxPitch;
    float minDistance;
    float maxDistance;
    float mouseSensitivity;
    float keyZoomSpeed;
    float wheelZoomAmount;

    float targetX;
    float targetY;
    float targetZ;

    // Methods
    void update(Inputs* input, float dt); // update camera angles & zoom
    void setTarget(float x, float y, float z);
    void applyView(); // gluLookAt
};
