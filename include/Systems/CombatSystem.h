#pragma once

class Player;
class Enemy;
class Attack;
class EnemyHandler; // We'll need this

class CombatSystem {
public:
    // When we create the system, we give it references to all
    // the objects it needs to "connect". This is called Dependency Injection.
    CombatSystem(Player& player, EnemyHandler& enemies);

    // Your functions now become methods of this class
    //int handlePlayerHit(Attack atk, Enemy& e);
    //int handleEnemyHit(Enemy& e);

private:
    // It holds references to the objects, not copies
    Player& m_player;
    EnemyHandler& m_enemies;
};