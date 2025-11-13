#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "Scenes/Scene.h"
#include "Graphics/Camera.h"
#include "IO/Inputs.h"
#include "Core/FileLoader.h"

class SceneManager {
public:
    SceneManager();
    ~SceneManager() = default;

    void addScene(const std::string& name, Scene* scene);
    void switchTo(const std::string& name);
    void update(float dt);
    void draw();
    void handleWinMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    Scene* getCurrentScene(){return currentScene;}
    Inputs* getInputs() { return inputs.get(); }
    Camera* getCamera() { return camera.get(); }
    FileLoader fl;
private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;
    Scene* currentScene;

    std::unique_ptr<Camera> camera;
    std::unique_ptr<Inputs> inputs;
};