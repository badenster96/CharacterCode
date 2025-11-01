#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Enemy.h"
#include "Player.h"
#include "Inventory.h"

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


// Main function of the enemies, player, and inventory
// Creates an inventory, player character, and Enemy handler classes

// IO in the terminal, for use with configuring the items
// Do not use this function in the main game!
class IO {
    public:
    IO () {
        string choiceStr;
        cout << "Welcome to the character creation debugger!" << endl
            << "Please enter your character's name: ";
            cin >> choiceStr;
        p.name = choiceStr;
        cout << "Your character's name is " << p.name << endl;
        int choice;
        do {
            cout << "Please choose an option from the prompt to power up your character:\n"
            << "1) Print " << p.name << "'s stats" << endl
            << "2) Item equipping wizard" << endl
            << "3) Debug Item Stats" << endl
            << "0) Exit" << endl;
            cin >> choice;
            if(choice == 1){
                printPlayerStatsWizard();
            } else if (choice == 2) {
                itemEquipmentWizard();
            } else if (choice == 3) {
                debugStatsWizard();
            }
        } while(choice != 0);
    }
    void printPlayerStatsWizard() {
        cout << "|==========" << p.name << "==========|" << endl;
            for(const auto& [statName, statVal] : p.stats) {
                cout << statName << ": " << statVal << endl;
            }
    }
    void itemEquipmentWizard() {
        int id;
        Item item;
        char choice;
        cout << "Number of items loaded: " << inv.totalItems() - 1 << endl;
        cout << "Size of character inventory:" << p.inventorySize() << endl;
        do {
            cout << "Please enter Item ID: ";
            cin >> id;
            cout << "Item Stats: " << endl;
            item = inv.getItem(id);
            cout << item.name << ", Type:" << item.type << endl;
            for(const auto& [statName, statVal] : item.stats) {
                cout << statName << ": " << statVal << endl;
            }
            cout << "Add \"" << item.name << "\" to player's inventory? Y or N";
            cin >> choice;
            if(choice == 'Y') p.addItemToInventory(item);
        } while (id > -1);
    }
    void debugStatsWizard() {
        for(int i = 0; i < inv.totalItems(); i++) {
            Item item = inv.getItem(i);
            cout << item.name << ":" << endl;
            for (const auto& [statName, statVal] : item.stats )cout << statName << ":" << statVal << endl;
        }
    }
    private:
    Player p;
    Inventory inv;

};

class GameState {
    public:
    GameState() {
        IO io;
    }


    private:
    Player p;
    //EnemyHandler enemies;
    //Inventory inv;
};
int main () {
    GameState game;
    return 0;
}