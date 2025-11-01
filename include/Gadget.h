#pragma once 

#include "item.h"

struct Gadget : public Item {
    // Weapons modify several base stats, but have a limit of three
    bool isGadget() {return true;}
};