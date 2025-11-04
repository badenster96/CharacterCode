#pragma once

/**
 * @struct Settings
 * @brief A container for all "magic numbers" and configuration
 * values for the game, making them easy to edit in one place.
 */
struct Settings
{
    // --- Player Movement ---
    float playerBaseSpeed;
    float playerSprintMultiplier;

    // --- Parallax Background ---
    float foregroundScrollSpeed;
    float backgroundScrollSpeed;
    float cameraScrollScale;
    struct PlayerSettings {
        float playerScale;
    };
};