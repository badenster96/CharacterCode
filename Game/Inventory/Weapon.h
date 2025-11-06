#pragma once

#include "Virtuals/Item.h"

struct Weapon : public Item {
    // Weapons modify several base stats, but have a limit of three
    bool isWeapon();

    int level;
};