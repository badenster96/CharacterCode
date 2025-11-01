#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Enemy.h"
#include "Player.h"
#include "Inventory.h"
#include "TerminalIO.h"

using namespace std;


// Object
// Main bridge function to handle enemy attacking a player
int enemyHitHandler(Enemy &e, Player &p) {
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
int playerHitHandler(Player &p, Attack atk, Enemy &e) {
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
// The class that stores all the enemies of the game
class EnemyHandler {
    public:
    EnemyHandler() {
        // The number of enemies in the game that can exist at once
        enemies.resize(200); 
    }
    // Function that adds the enemy to the next available spot of the Enemy vector
    // searches through the vector, finds an open slot, and inputs the enemy,
    // setting the enemies ID to the vector position
    void addEnemy(Enemy &e) {
        // Check isAlive bool to see the nearest slot an enemy can be spawned in
        int i = 0;
        while(enemies.at(i).isAlive && i < enemies.size()) {
            i++;
        }
        enemies.at(i) = e;
        enemies.at(i).isAlive = true;
        if(i == enemies.size()) {
            e.setObjectID(i);
            e.setAlive(true);
            enemies.push_back(e);
        }
    }
    private:
    // the storage for all enemies in the game
    vector<Enemy> enemies;
};

int main () {
    TerminalIO io;
    return 0;
}