#pragma once
#include <string>
#include <unordered_map>
#include <filesystem>
#include <nlohmann/json.hpp>
#include "Inventory/Item.h"
#include "Inventory/Weapon.h"
#include "Inventory/Gadget.h"
#include "Inventory/Gizmo.h"
#include "Inventory/Training.h"

namespace fs = std::filesystem;
using json = nlohmann::json;

class FileLoader {
public:
    FileLoader();
    ~FileLoader() = default;

    void loadWeaponsFromJSON();
    void loadGadgetsFromJSON();
    void loadGizmosFromJSON();
    void loadTrainingsFromJSON();


private:
    std::unordered_map<std::string, Weapon> weapons;
    std::unordered_map<std::string, Gadget> gadgets;
    std::unordered_map<std::string, Gizmo>  gizmos;
    std::unordered_map<std::string, Training> trainings;
    std::unordered_map<std::string, std::unordered_map<std::string, Item>> allItems;
};
