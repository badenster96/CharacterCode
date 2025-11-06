#include "Graphics/Camera.h"
#include <cmath>
#include <iostream>

Camera::Camera()
{
    angleX = 20.0f;
    angleY = 0.0f;
    distance = 10.0f;

    // Default settings
    minPitch = 5.0f;
    maxPitch = 85.0f;
    minDistance = 15.0f;
    maxDistance = 50.0f;

    mouseSensitivity = 0.2f;
    keyZoomSpeed = 10.0f;
    wheelZoomAmount = 1.0f;

    targetX = 0.0f;
    targetY = 0.0f;
    targetZ = 0.0f;
}

void Camera::setTarget(float x, float y, float z)
{
    targetX = x;
    targetY = y;
    targetZ = z;
}

void Camera::update(Inputs* input, float dt)
{
    if (!input) return;

    // --- Orbiting ---
    angleX -= input->mouseDeltaY * mouseSensitivity;
    angleY += input->mouseDeltaX * mouseSensitivity;

    // Clamp
    if (angleX > maxPitch) angleX = maxPitch;
    if (angleX < minPitch) angleX = minPitch;
    if (angleY < 0.0f) angleY += 360.0f;
    if (angleY >= 360.0f) angleY -= 360.0f;

    // --- Zooming ---
    if (input->wheelDelta != 0.0) distance -= input->wheelDelta * wheelZoomAmount;
    if (input->isZoomingIn) distance -= keyZoomSpeed * dt;
    if (input->isZoomingOut) distance += keyZoomSpeed * dt;

    if (distance < minDistance) distance = minDistance;
    if (distance > maxDistance) distance = maxDistance;

    // --- Reset input deltas ---
    input->mouseDeltaX = 0.0;
    input->mouseDeltaY = 0.0;
    input->wheelDelta = 0.0;
}


void Camera::applyView()
{
    float angleXRad = angleX * M_PI / 180.0f;
    float angleYRad = angleY * M_PI / 180.0f;

    float eyeX = targetX + distance * cos(angleXRad) * sin(angleYRad);
    float eyeY = targetY + distance * sin(angleXRad);
    float eyeZ = targetZ + distance * cos(angleXRad) * cos(angleYRad);

    gluLookAt(
        eyeX, eyeY, eyeZ,
        targetX, targetY, targetZ,
        0.0f, 1.0f, 0.0f
    );
}
