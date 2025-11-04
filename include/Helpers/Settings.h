#pragma once

/**
 * @struct Settings
 * @brief A container for all "magic numbers" and configuration
 * values for the game, making them easy to edit in one place.
 */
struct Settings
{
    // --- Player Movement ---
    float playerBaseSpeed                = 10.0f;
    float playerSprintMultiplier          = 2.0f;

    // --- Parallax Background ---
    float foregroundScrollSpeed          = 0.1f; // This is now a relative multiplier
    float backgroundScrollSpeed          = 0.05f; // This is now a relative multiplier
    float cameraScrollScale              = 0.01f;
    struct PlayerSettings {
        float playerScale;
    };
};