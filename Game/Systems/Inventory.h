#pragma once

#include "Inventory/Item.h"
#include "Inventory/Weapon.h"
#include "Inventory/Gizmo.h"
#include "Inventory/Gadget.h"
#include "Inventory/Training.h"

#include <fstream>
#include <sstream>
#include <vector>

class Inventory {
    public:
    Inventory();
    Item getItem(int ID);

    // Debug functions
    int totalItems();

    private:
    // Master inventory list of all items in the game, loaded from "items"
    std::vector<Item> inventory;
};