#pragma once

#include "item.h"

struct Weapon : public Item {
    // Weapons modify several base stats, but have a limit of three
    bool isWeapon();

    int level;
};