#include "EnemyHandler.h"

EnemyHandler::EnemyHandler() {
    // The number of enemies in the game that can exist at once
    enemies.resize(200); 
}
// Function that adds the enemy to the next available spot of the Enemy vector
// searches through the vector, finds an open slot, and inputs the enemy,
// setting the enemies ID to the vector position
void EnemyHandler::addEnemy(Enemy &e) {
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