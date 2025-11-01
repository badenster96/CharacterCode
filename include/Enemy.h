// The enemy class handles the spawning of each enemy of the game. When created, the gamestate
// adds the enemy Pawn to the enemy storage, and removes them from it when they die

#pragma once

#include "Pawn.h"

class Enemy : public Pawn {
    public:
    Enemy();
    Enemy(Attack setAtk);
    Enemy(int newDamage, int newPenetration);

    void setAttack(Attack newAtk);

    Attack getAttack();
};