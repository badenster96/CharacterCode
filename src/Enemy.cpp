#include "Enemy.h"

Enemy::Enemy() {
        Attack atk;
        attacks.push_back(atk);
        isAlive = true;
}
Enemy::Enemy(Attack setAtk){
        attacks.push_back(setAtk);
        isAlive = true;
}
Enemy::Enemy(int newDamage, int newPenetration){
        Attack a(newDamage, newPenetration);
        attacks.push_back(a);
        isAlive = true;
}

void Enemy::setAttack(Attack newAtk){ attacks.at(0) = newAtk;}

Attack Enemy::getAttack(){return attacks.at(0);}