#pragma once

#include "Item.h"
#include "Weapon.h"
#include "Gizmo.h"
#include "Gadget.h"
#include "Training.h"

#include <fstream>
#include <sstream>
#include <vector>

class Inventory {
    public:
    Inventory();
    // Loads list of items from "items"
    void loadInventory();
    Item getItem(int ID);

    // Debug functions
    int totalItems();

    private:
    // Master inventory list of all items in the game, loaded from "items"
    std::vector<Item> inventory;
};