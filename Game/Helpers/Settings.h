#pragma once

/**
 * @struct Settings
 * @brief A container for all configuration values for the game.
 */
struct Settings
{
    // --- Player Movement ---
    float playerBaseSpeed        = 10.0f;
    float playerSprintMultiplier = 2.0f;

    // --- Parallax Background ---
    float foregroundScrollSpeed  = 0.001f;
    float backgroundScrollSpeed  = 0.0005f;
    float cameraScrollScale      = 0.01f;
    float mouseSensitivity       = 0.2f;

    struct PlayerSettings {
        float playerScale = 1.0f;
    } playerSettings;

    // --- Singleton access ---
    static Settings& get() {
        static Settings instance; // Created only once
        return instance;
    }

    // Delete copy/move to enforce single instance
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;
    Settings(Settings&&) = delete;
    Settings& operator=(Settings&&) = delete;

private:
    Settings() = default; // private constructor
};
