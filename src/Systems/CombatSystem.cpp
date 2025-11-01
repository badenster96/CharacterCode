#include "Systems/CombatSystem.h"
#include "Entities/Player.h"
#include "Entities/Enemy.h"
#include "EnemyHandler.h"
#include "Attack.h"

// The constructor saves the references
CombatSystem::CombatSystem(Player& player, EnemyHandler& enemies)
    : m_player(player), m_enemies(enemies) 
{
    // Ready to work
}

int CombatSystem::handlePlayerHit(Attack atk, Enemy& e) {
    double tempDamage = m_player.attacks.at(0).damage; // We can access m_player
    e.stats["Health"] -= tempDamage;
    return 1;
}

int CombatSystem::handleEnemyHit(Enemy& e) {
    double tempDamage = e.attacks.at(0).damage;
    tempDamage *= m_player.armorHandler(e.attacks.at(0).penetration);
    m_player.stats["Health"] -= tempDamage;
    return 1;
}