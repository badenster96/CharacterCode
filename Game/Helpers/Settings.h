#pragma once

/**
 * @struct Settings
 * @brief A container for all configuration values for the game.
 */
struct Settings
{
    std::string projSrc = std::string(PROJECT_SOURCE_DIR);
    // --- Player Movement ---
    float playerBaseSpeed        = 10.0f;
    float playerSprintMultiplier = 2.0f;
    float playerScale = 1.0f;

    // --- Parallax Settings ---
    float foregroundScrollSpeed  = 0.001f;
    float backgroundScrollSpeed  = 0.0005f;
    float cameraScrollScale      = 0.01f;
    float mouseSensitivity       = 0.2f;

    // --- File Locations ---

    // Items
    std::string itemJSONFolder = projSrc + "/data";
    std::string weaponJSON     = itemJSONFolder + "/weapons.json";
    std::string gadgetJSON     = itemJSONFolder + "/gadgets.json";
    std::string gizmoJSON      = itemJSONFolder + "/gizmos.json";
    std::string trainingJSON   = itemJSONFolder + "trainings.json";
    // Models






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
