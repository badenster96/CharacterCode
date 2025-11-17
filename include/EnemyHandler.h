#include <vector>

#include "Enemy.h"

using std::vector;

class EnemyHandler {
    public:
    EnemyHandler();
    // Function that adds the enemy to the next available spot of the Enemy vector
    // searches through the vector, finds an open slot, and inputs the enemy,
    // setting the enemies ID to the vector position
    void addEnemy(Enemy &e);
    private:
    // the storage for all enemies in the game
    vector<Enemy> enemies;
};