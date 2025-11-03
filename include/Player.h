#pragma once

#include <GL/gl.h>
#include <TextureLoader.h>
#include <Timer.h>

#include "Inventory/Item.h"
#include "Systems/Inventory.h"

class Player : public Item
{
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
        virtual ~Player();

        float scale[3]={1.0,1.0,1.0};
        vec3 verticies[4];

        float xPos;   //x position of the Player
        float yPos;   //y position of the Player
        float zPos;   //z position of the Player

        float xSize;
        float ySize;

        float xRotation;
        float yRotation;
        float zRotation;


        float runSpeed;
        float jumpSpeed;

        void drawPlayer();
        void placePlayer();
        void initPlayer(char *);

        void actions();   // may have to pass different frame numbers
        int action;          // give values for run jump etc.
        float frames;
        float xMax,xMin,yMax,yMin;

    protected:

    private:
        std::vector<Item> itemStats;
};