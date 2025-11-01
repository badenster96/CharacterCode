#include "Player.h"


Player::Player () {
        stats["Health"]                 = 100; // 100 to Inf
        stats["Speed"]                  = 1.0; // 1.0 to inf
        stats["Attack_Speed"]           = 1.0; // 1.0 to inf
        stats["Damage"]                 = 1.0; // 1.0 to inf
        stats["Damage_Multiplier"]      = 1.0; // 1.0 to inf
        stats["Critical_Chance"]        = 0.05;// 0.05 to 1
        stats["Critical_Damage"]        = 2.0; // 2.0 to inf
        stats["Armor"]                  = 0.0; // 0.0 to inf
        stats["Dodge"]                  = 1.0; // 1 to 100
}
//Loader Functions: Functions loaded once when the player is created in the game  
// Game Functions: Functions used in the course of the game

//change player stats
void Player::setStat(std::string stat, double value) {
        stats[stat] = value;
}
void Player::addStat(std::string stat, double value) {
        if(stats.count(stat)){
                stats[stat] += value;
        } else {
                stats[stat] = value;
        }
}
int Player::dodgeHandler() {
        double randomNumber = 0.05; // Replace this with a random number
        if(stats["Dodge"] >= randomNumber) return 1;
        else return 0;
}
double Player::armorHandler(double penetration) {
        double effectiveArmor = abs(stats["Armor"] - penetration);
        return 1 - (effectiveArmor / (10 + effectiveArmor));
}
// Player inventory functions
// Adds an item to the player's inventory
void Player::addItemToInventory(Item newItem) {
        int newID = newItem.ID;
        // make the two item vectors the appropriate size if they arent already
        if(itemStats.size() <= newItem.ID) {itemStats.resize(newItem.ID + 1);} 
        // Then, check if the item at the vector space exists. if so, add 1. if not, set to 1
        if(itemStats.at(newID).count == 0){
                itemStats.at(newItem.ID) = newItem;
                itemStats.at(newID).count = 1;
        } else {itemStats.at(newID).count += 1;}
        // Call the helper function to add the new items stats to the player characters stats
        equipItem(newItem);
}
// Helper function to set the player's new stats by adding the item's stats
// also calls the weapon and gadgets checker, so the limits of those can be set
bool Player::isWeapon(Item item){
        if(item.type == "Weapon") return true;
        return false;
}
bool Player::isGadget(Item item){
        if(item.type == "Gadget") return true;
        return false;
}
void Player::equipItem(Item item) {
        for(const auto [statName, stat] : item.stats) {
                if(stats.count(statName)) addStat(statName, item.stats.at(statName));
                else stats[statName] = item.stats.at(statName);
        }
}

// Debug functions
int Player::inventorySize() {
        int size = 0;
        for(int i = 0; i < itemStats.size(); i++){
                if(itemStats.at(i).count > 0) size++;
        }
        return size;
}