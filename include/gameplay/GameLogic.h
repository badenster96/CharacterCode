class Player;
class Enemy;
class Attack;

namespace GameLogic{
    int enemyHitHandler(Enemy &e, Player &p);
    // Main bridge function to handle player attacking an enemy
    // returns 1 if the hit was sucessful, and 0 if it was a miss
    int playerHitHandler(Player &p, Attack atk, Enemy &e);
}
