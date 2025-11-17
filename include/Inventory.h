#pragma once

#include "Inventory/Item.h"
#include "Inventory/Weapon.h"
#include "Inventory/Gizmo.h"
#include "Inventory/Gadget.h"
#include "Inventory/Training.h"
#include "FileLoader.h"

#include <fstream>
#include <sstream>
#include <vector>

class Inventory {
    public:
    Inventory();
    void loadItems();
    auto getItem(std::string iD);

    Weapon getWeapon(std::string name){return weaponStats[name];}
    Gizmo getGizmo(std::string name){return gizmoStats[name];}
    Gadget getGadget(std::string name){return gadgetStats[name];}
    Training getTraining(std::string name){return trainingStats[name];}

    // Debug functions
    int totalItems();

    private:
    std::unordered_map<std::string, Weapon> weaponStats;
    std::unordered_map<std::string, Gizmo> gizmoStats;
    std::unordered_map<std::string, Gadget> gadgetStats;
    std::unordered_map<std::string, Training> trainingStats;
    // Master inventory list of all items in the game, loaded from "items"
    std::vector<Item> inventory;
};