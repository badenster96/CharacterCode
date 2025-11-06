#include "Core/SceneManager.h"
#include <iostream>

SceneManager::SceneManager()
    : currentScene(nullptr),
      camera(std::make_unique<Camera>()),
      inputs(std::make_unique<Inputs>()) {}

void SceneManager::addScene(const std::string& name, Scene* scene) {
    scene->attachSystems(inputs.get(), camera.get());
    scenes[name].reset(scene);
}

void SceneManager::switchTo(const std::string& name) {
    if (scenes.count(name))
        currentScene = scenes[name].get();
}

void SceneManager::update(float dt) {
    if (currentScene) currentScene->update(dt);
}

void SceneManager::draw() {
    if (currentScene) currentScene->draw();
}

void SceneManager::handleWinMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (currentScene) currentScene->handleWinMsg(hWnd, uMsg, wParam, lParam);
}
