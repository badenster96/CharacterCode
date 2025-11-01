/*
The character class!

The player in the GunGame has an allocation of stats that modify behavior:
HP                | Scalar - A value that starts at 100. At 0, the game is over.
Speed             | Multiplier - A value between 1 and infinity, acts as a multiplier for how fast the player moves
Attack Speed      | Multiplier - A value between 1 and infinity, multiplier value for the speed the player attacks
Damage            | Scalar - The damage the player does, a flat value that is transmitted via the Attack class to enemies
Damage Multiplier | Multiplier - The multiplier the damage oes to enemies. 
Critical Chance   | Scalar - A value between 0 and 100 that represents the chance the player's attack is a crit, multiplying it by its critical hit value
Critical Damage   | Multiplier - The amount the critical hit is multiplied by.
Armor             | Scalar - A value that reduces the amount of damage the player takes. At 10 Armor, the damage a player takes is reduced by half.
Armor Piercing    | Multiplier - The amount of armor an attack ignores when the player is hit.

There will then be several types of player upgrades:
|====| Weapons |====|
Weapons don't have tiers of upgrades, but instead modify the player's  base stats.
Weapons set the base HP, Attack Speed, Damage, Critical Chance, and Armor of the player.
|--| Max: 3 |--|


Tools - 
 -- Tools are upgrades that add bonuses to a specific player stat. Max at 3 Tools.
Items - 
 -- Items modify individual stats, but have no limit to the number of them you can hold. Unlimited.
Training - 
 -- Promotions are small, incremental bonuses to stats that the player achieves when completing objectives around the map.


|==| Upgrades |==|
Once a player gets a Weapon or Item, leveling up will give them the option of one of three upgrades. These upgrades can be one of four levels:
 - Common: Green
 - Uncommon: Blue
 - Rare: Purple
 - Legendary: Yellow
The rarity of the upgrade determines the amount of the upgrade the weapon is getting.
*/

#pragma once

#include "Pawn.h"
#include "Item.h"

#include <string>


class Player : public Pawn {
    public:
    Player ();
    //Loader Functions: Functions loaded once when the player is created in the game  
    // Game Functions: Functions used in the course of the game

    //change player stats
    void setStat(std::string stat, double value);
    void addStat(std::string stat, double value);
    int dodgeHandler();
    double armorHandler(double penetration);
    // Player inventory functions
    // Adds an item to the player's inventory
    void addItemToInventory(Item newItem);
    // Helper function to set the player's new stats by adding the item's stats
    // also calls the weapon and gadgets checker, so the limits of those can be set
    bool isWeapon(Item item);
    bool isGadget(Item item);
    void equipItem(Item item);
    
    // Debug functions
    int inventorySize();
    private:
    // Player inventory
    std::vector<Item> itemStats;
};