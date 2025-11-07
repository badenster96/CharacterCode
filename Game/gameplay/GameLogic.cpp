#include "gameplay/GameLogic.h"

#include "Entities/Player.h"
#include "Entities/Enemy.h"


/*
// Main bridge function to handle enemy attacking a player
int GameLogic::enemyHitHandler(Enemy &e, Player &p) {
    double tempDamage = e.attacks.at(0).damage;
    // Next, take the attac ks penetration and modify the effective armor, 
    // multiplying the perentage decrease from the damage
    tempDamage *= p.armorHandler(e.attacks.at(0).penetration);
    //Finally, subtract the damage from the player's health
    p.stats["Health"] -= tempDamage;
    return 1;
}
// Main bridge function to handle player attacking an enemy
// returns 1 if the hit was sucessful, and 0 if it was a miss
int GameLogic::playerHitHandler(Player &p, Attack atk, Enemy &e) {
    double tempDamage = p.attacks.at(0).damage;
    // First, see if the attack actually hits with the player's dodge stat
    // If it misses, return 0
    if(p.dodgeHandler()) return 0;
    // Next, take the attac ks penetration and modify the effective armor, 
    // multiplying the perentage decrease from the damage
    tempDamage *= p.armorHandler(p.attacks.at(0).penetration);
    //Finally, subtract the damage from the player's health
    e.stats["Health"] -= tempDamage;
    return 1;
}
    */