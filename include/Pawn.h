// Pawns are Objects that exist in the world, and each spawn in and come with their own ID. 
// The gamestate stores the number of Pawns according to their ID, and will replace them in the 
// list when they no longer exist

#pragma once

#include "Object.h"
#include "Attack.h"
#include <vector>

struct Pawn : public Object {
    Pawn() {
        stats["Health"] = 1;
        stats["Damage"] = 1;
    }
    // Pawns are objects that exist in the world. Each pawn has a unique ID when they are spawned in the world.
    void setObjectID(int newObjectID);
    void setAlive(bool newIsAlive);
    int getObjectID();

    std::vector<Attack> attacks;
    // The unique identifier for a pawn in the world
    int objectID;
    // Whether or not the pawn is alive
    bool isAlive;
};