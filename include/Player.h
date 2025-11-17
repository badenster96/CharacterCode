#pragma once

#include "Inputs.h" // Inputs class (assumed to exist)
#include "Model.h"     // Model base class (assumed to exist)
#include "Timer.h"     // Timer class (assumed to exist)
#include "Common.h"
#include "Settings.h"
#include "Inventory/Item.h" // Item struct (assumed to exist)
#include "_3DModelLoader.h" // For Model base class
#include "Camera.h" // For Camera class

#include <string>
#include <map>
#include <vector>
#include <cmath>


class Player : public Model
{
private:
    // --- NEW: Player's position state is now owned by the Player itself ---
    vec3 playerPos;

    //3D model storage
    _3DModelLoader* md2Model;

    // Existing members (inherited from Pawn/Model)
    Timer* tmr;

public:
    Player();
    ~Player();

    // Core initialization and drawing
    void initModel(const char *fileName);
    void drawModel(); 

    // --- NEW: Function to handle input, movement, and animation updates ---
    void handleInputAndMove(float dt, Camera* camera, Inputs* kBMs, const Settings& settings);
    vec3 getPosition() const { return playerPos; }

    // Existing model functions (assuming they are part of the base Model)
    // Placeholder for Model's update, walk, and stand methods.
    void update(float dt);
    void walk();
    void stand();

    // Existing stat/inventory functions
    void setStat(std::string stat, double value);
    void addStat(std::string stat, double value);
    int dodgeHandler();
    double armorHandler(double penetration);
    // void addItemToInventory(Item newItem);
    bool isWeapon(Item item);
    bool isGadget(Item item);
    void equipItem(Item item);
    int inventorySize();
    vec3 verticies[4];

private:
    // Existing data members
    std::map<std::string, double> stats;
    std::vector<Item> itemStats;
};
