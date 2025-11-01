#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Enemy.h"
#include "Player.h"
#include "Inventory.h"

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