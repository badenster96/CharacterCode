#pragma once

struct Attack {
    double damage, penetration;
    Attack() {
        damage = 1;
        penetration = 0;
    }
    Attack(double newDamage, double newPenetration);
};