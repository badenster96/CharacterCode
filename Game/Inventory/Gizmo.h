#pragma once 

#include "Inventory/Item.h"

struct Gizmo : public Item {
        bool isGadget() {return true;}
};