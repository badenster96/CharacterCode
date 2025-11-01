#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Entities/Enemy.h"
#include "Entities/Player.h"
#include "Systems/Inventory.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;


class TerminalIO {
    public:
    TerminalIO ();
    void printPlayerStatsWizard();
    void itemEquipmentWizard();
    void debugStatsWizard();

    private:
    Player p;
    Inventory inv;
};