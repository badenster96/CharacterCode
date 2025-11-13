#include <iostream>

#include "Systems/Inventory.h"

Inventory::Inventory() {
        loadItems();
}

void Inventory::loadItems() {
        FileLoader fL;
        weaponStats = fL.getWeapons();
        gadgetStats = fL.getGadgets();
        gizmoStats = fL.getGizmos();
        trainingStats = fL.getTrainings();
}

// Debug functions
int Inventory::totalItems() {
        return inventory.size();
}