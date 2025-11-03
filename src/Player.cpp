#include "Player.h"

TextureLoader *T= new TextureLoader();
Timer *tmr = new Timer();


Player::Player()
{
        stats["Health"]                 = 100; // 100 to Inf
        stats["Speed"]                  = 1.0; // 1.0 to inf
        stats["Attack_Speed"]           = 1.0; // 1.0 to inf
        stats["Damage"]                 = 1.0; // 1.0 to inf
        stats["Damage_Multiplier"]      = 1.0; // 1.0 to inf
        stats["Critical_Chance"]        = 0.05;// 0.05 to 1
        stats["Critical_Damage"]        = 2.0; // 2.0 to inf
        stats["Armor"]                  = 0.0; // 0.0 to inf
        stats["Dodge"]                  = 1.0; // 1 to 100
    //ctor
    verticies[0].x=0.0; verticies[0].y=0.0;verticies[0].z=-1.0;
    verticies[1].x=1.0; verticies[1].y=0.0;verticies[1].z=-1.0;
    verticies[2].x=1.0; verticies[2].y=1.0;verticies[2].z=-1.0;
    verticies[3].x=0.0; verticies[3].y=1.0;verticies[3].z=-1.0;

    runSpeed =0;
    jumpSpeed =0;

    xPos=0.0;   //x position of the Player
    yPos=-2.0;   //y position of the Player
    zPos=-5.0;   //z position of the Player

    xSize =1.0;
    ySize =1.0;

    xRotation=0.0;
    yRotation=0.0;
    zRotation=0.0;

    action =-1;

    frames =9;
    xMin=8/frames;
    yMin=0.5;
    yMax=0.666;
    xMax=1.0;
}

Player::~Player()
{
    //dtor
}

void Player::placePlayer()
{

}

void Player::drawPlayer()
{
    glColor3f(1.0,0.0,0.0);
    glPushMatrix();  //ouping the Quad
    T->bind();

    glTranslatef(xPos,yPos,zPos);
    glRotatef(xRotation,1.0,0.0,0.0);
    glRotatef(yRotation,0.0,1.0,0.0);
    glRotatef(zRotation,0.0,0.0,1.0);
    glScalef(xSize,ySize,1);

    glBegin(GL_QUADS);
      glTexCoord2f(xMin,yMax);
      glVertex3f(verticies[0].x, verticies[0].y,verticies[0].z);
      glTexCoord2f(xMax,yMax);
      glVertex3f(verticies[1].x, verticies[1].y,verticies[1].z);
      glTexCoord2f(xMax,yMin);
      glVertex3f(verticies[2].x, verticies[2].y,verticies[2].z);
      glTexCoord2f(xMin, yMin);
      glVertex3f(verticies[3].x, verticies[3].y,verticies[3].z);
    glEnd();
    glPopMatrix();

}

void Player::initPlayer(char *fileName)
{
   // T->TextureBinder();


   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    T->loadTexture(fileName);
    tmr->start();
}

void Player::actions()
{
    switch(action)
    {

        case 0:
                frames= 9.0;
                if(tmr->getTicks()>60)
                {
                xMin+=1.0/frames;
                xMax+=1.0/frames;
                yMin= 0.333;
                yMax= 0.5;
                if(xMax>=1){xMin=0.0; xMax=1/frames;}

                tmr->reset();
                }

         break;

        case 1:
               frames= 9.0;
                if(tmr->getTicks()>60)
                {
                xMin+=1.0/frames;
                xMax+=1.0/frames;
                yMin= 0.333;
                yMax= 0.5;
                if(xMax>=1){xMin=1.0/frames; xMax=0.0/frames;}

                tmr->reset();
                }

            break;

        case 3:
             frames= 9.0;
             xMin=8/frames;
             yMin=0.5;
             yMax=0.666;
             xMax=1.0;
            break;

    }

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