#pragma once

/**
 * @struct SceneSettings
 * @brief A container for all "magic numbers" and configuration
 * values for the scene, making them easy to edit in one place.
 */
struct SceneSettings
{
    // --- Player Movement ---
    float playerBaseSpeed;
    float playerSprintMultiplier;

    // --- Camera Control ---
    float mouseSensitivity;
    float keyZoomSpeed;
    float wheelZoomAmount;
    float minZoomDistance;
    float maxZoomDistance;
    float minCameraPitch;
    float maxCameraPitch;

    // --- Parallax Background ---
    float foregroundScrollSpeed;
    float backgroundScrollSpeed;
    float cameraScrollScale; // <-- ADD THIS
};