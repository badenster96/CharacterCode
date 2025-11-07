#pragma once 

#include "Inventory/Item.h"

struct Training : public Item {
        bool isTraining() {return true;}
};