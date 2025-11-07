#include <iostream>

#include "Systems/Inventory.h"

Inventory::Inventory() {
        
}

Item Inventory::getItem(int ID) {
        return inventory.at(ID);
}

// Debug functions
int Inventory::totalItems() {
        return inventory.size();
}