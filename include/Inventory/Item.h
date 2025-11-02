#pragma once

#include "Inventory/Object.h"

struct Item : public Object {
    //Items are objects that don't exist in the world, and come in 4 types: Weapon, Tool, Item, and Promotion
    int count = 0;
};