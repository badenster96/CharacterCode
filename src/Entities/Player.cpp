#include "Entities/Player.h"
#include "Graphics/TextureLoader.h" // We still need this for 'tex'
#include <GL/glut.h>
#include <cmath>

// NO MORE GLOBAL 'T' or 'tmr'

Player::Player()
    : Model() // Call the base class constructor
{
    // --- Initialize Stats (from Player) ---
    stats["Health"] = 100;
    stats["Speed"] = 1.0;
    stats["Attack_Speed"] = 1.0;
    // ... (all other stats) ...
    stats["Dodge"] = 1.0;

    // --- Initialize Animation (from Player) ---
    action = -1;
    frames = 9;
    xMin = 8.0f / frames;
    yMin = 0.5;
    yMax = 0.666;
    xMax = 1.0;

    // --- Initialize Geometry (from Pawn) ---
    verticies[0].x = 0.0; verticies[0].y = 0.0; verticies[0].z = -1.0;
    verticies[1].x = 1.0; verticies[1].y = 0.0; verticies[1].z = -1.0;
    verticies[2].x = 1.0; verticies[2].y = 1.0; verticies[2].z = -1.0;
    verticies[3].x = 0.0; verticies[3].y = 1.0; verticies[3].z = -1.0;

    // --- Initialize Position/Scale (from Pawn, using Model setters) ---
    setPosition(0.0, -2.0, -5.0); // Use base class method
    setScale(1.0, 1.0, 1.0);    // Use base class method
    setRotation(0.0, 0.0, 0.0);

    // Create the player's animation timer
    tmr = new Timer();
}

Player::~Player()
{
    // Clean up our timer
    if (tmr)
    {
        delete tmr;
    }
    // The base class ~Model() destructor will be called automatically
    // to clean up 'tex'
}

void Player::initModel(const char *fileName)
{
    // Enable transparency settings
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Use the INHERITED 'tex' pointer to load the texture
    tex->loadTexture(fileName); 
    
    // Start the animation timer
    tmr->start();
}

// This is the OVERRIDDEN draw function
void Player::drawModel()
{
    glColor3f(1.0, 1.0, 1.0); // Use white so texture is not tinted
    glPushMatrix();
    
    // Use the INHERITED 'tex' pointer
    tex->bind(); 

    // Use the INHERITED position, rotation, and scale variables
    glTranslatef(posX, posY, posZ);
    glRotatef(rotateX, 1.0, 0.0, 0.0);
    glRotatef(rotateY, 0.0, 1.0, 0.0);
    glRotatef(rotateZ, 0.0, 0.0, 1.0);
    glScalef(scaleX, scaleY, scaleZ);

    // Draw the animated quad (from original Player::draw)
    glBegin(GL_QUADS);
        glTexCoord2f(xMin, yMax);
        glVertex3f(verticies[0].x, verticies[0].y, verticies[0].z);
        glTexCoord2f(xMax, yMax);
        glVertex3f(verticies[1].x, verticies[1].y, verticies[1].z);
        glTexCoord2f(xMax, yMin);
        glVertex3f(verticies[2].x, verticies[2].y, verticies[2].z);
        glTexCoord2f(xMin, yMin);
        glVertex3f(verticies[3].x, verticies[3].y, verticies[3].z);
    glEnd();
    glPopMatrix();
}

// --- All other Player functions remain unchanged ---
// (actions(), setStat(), addStat(), dodgeHandler(), etc.)

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
        
        // ... all other cases ...
        
        case 3:
            frames= 9.0;
            xMin=8/frames;
            yMin=0.5;
            yMax=0.666;
            xMax=1.0;
        break;
    }
}

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
    double randomNumber = 0.05; // Replace with rand
    if(stats["Dodge"] >= randomNumber) return 1;
    else return 0;
}
double Player::armorHandler(double penetration) {
    double effectiveArmor = abs(stats["Armor"] - penetration);
    return 1 - (effectiveArmor / (10 + effectiveArmor));
}
void Player::addItemToInventory(Item newItem) {
    int newID = newItem.ID;
    if(itemStats.size() <= newItem.ID) {itemStats.resize(newItem.ID + 1);} 
    if(itemStats.at(newID).count == 0){
        itemStats.at(newItem.ID) = newItem;
        itemStats.at(newID).count = 1;
    } else {itemStats.at(newID).count += 1;}
    equipItem(newItem);
}
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
int Player::inventorySize() {
    int size = 0;
    for(int i = 0; i < itemStats.size(); i++){
        if(itemStats.at(i).count > 0) size++;
    }
    return size;
}
