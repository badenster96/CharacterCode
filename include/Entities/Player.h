#ifndef PLAYER_H
#define PLAYER_H

#include "Entities/Model.h"     // Include the base class
#include "Virtuals/Item.h"        // Assuming Item.h exists
#include "Helpers/Timer.h"    // Assuming Timer.h exists
#include <map>
#include <string>
#include <vector>
#include "Helpers/Common.h"

class Player : public Model // <-- THE INHERITANCE
{
public:
    Player();
    virtual ~Player();

    // We no longer need a separate 'init', we can use the one from Model.
    // We override it to add our own init logic.
    virtual void initModel(const char* texturePath) override;

    // This is the overridden draw function
    virtual void drawModel() override; 

    // --- Player-Specific Functions ---
    void actions();

    // Stat functions
    void setStat(std::string stat, double value);
    void addStat(std::string stat, double value);
    
    // Combat functions
    int dodgeHandler();
    double armorHandler(double penetration);

    // Inventory functions
    void addItemToInventory(Item newItem);
    int inventorySize(); // Debug

    std::map<std::string, double> stats;
    std::vector<Item> itemStats;

private:
    // Helper functions for inventory
    void equipItem(Item item);
    bool isWeapon(Item item);
    bool isGadget(Item item);

    // --- Player-Specific Data ---

    // Animation state
    int action;
    float frames;
    float xMin, yMin, xMax, yMax;
    
    // Geometry (from Pawn)
    vec3 verticies[4]; 

    // Player's own timer for animations
    Timer* tmr; 
};

#endif // PLAYER_H
