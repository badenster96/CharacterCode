#pragma once 

#include "Inventory/Item.h"

struct Gadget : public Item {
    // Weapons modify several base stats, but have a limit of three
    bool isGadget() {return true;}
};