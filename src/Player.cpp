#include "Player.h"
#include "TextureLoader.h"
#include <GL/glut.h>
#include <cmath>
#include <iostream> // For potential debugging

// Assuming Model.h provides:
// class Model { protected: TextureLoader* tex; float posX, posY, posZ; float rotateX, rotateY, rotateZ; float scaleX, scaleY, scaleZ; struct Vertex { float x, y, z; }; Vertex verticies[4]; };
// and that `walk()`, `stand()`, and `update(dt)` are implemented in Model or Player.

// Define M_PI if it's not defined by <cmath> on this platform
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

// --- Placeholder Implementations (Updated to use 3D model) ---

// This function now just forwards the call to the encapsulated 3D model
void Player::update(float dt) 
{ 
    if (md2Model) 
    {
        // MD2 models often need the time step for animation
        md2Model->update(dt); 
    }
}

// These methods set the animation state on the 3D model
void Player::walk() 
{ 
    if (md2Model) md2Model->walk(); // Assuming 1 is the Walk animation ID
} 
void Player::stand() 
{ 
    if (md2Model) md2Model->stand(); // Assuming 3 is the Stand animation ID
} 
// --- End Placeholders ---


Player::Player()
    : Model() // Call the base class constructor
{
    // --- Initialize Player Position (NEW) ---
    playerPos.x = 0.0f;
    playerPos.y = -3.0f; 
    playerPos.z = 0.0f;

    md2Model = new _3DModelLoader();
    
    // --- Initialize Stats (from Player) ---
    stats["Health"] = 100;
    stats["Speed"] = 1.0;
    stats["Attack_Speed"] = 1.0;
    stats["Dodge"] = 1.0;
    stats["Armor"] = 0.0;

    // --- Initialize Model Position/Scale (using Model setters) ---
    // Note: Model's internal posX/Y/Z are used for the quad's local translation, 
    // but the Player's world position is now stored in playerPos.
    setPosition(0.0, 0.0, 0.0); 
    setScale(0.1, 0.1, 0.1); 
    setRotation(0.0, 0.0, 0.0);

    // Create the player's animation timer
    tmr = new Timer();
}

Player::~Player()
{
    if (md2Model){delete md2Model;}
    if (tmr){delete tmr;}
}

void Player::initModel(const char *fileName)
{
    // Enable transparency settings
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // -----------------------------------------------------------------
    // FIX: Load the 3D model file instead of a texture sheet
    // -----------------------------------------------------------------
    if (md2Model)
    {
        md2Model->initModel(fileName);
        stand();
    }
    
    // Start the animation timer
    tmr->start();
}

// This is the OVERRIDDEN draw function
void Player::drawModel()
{
    glPushMatrix();
    if (md2Model)
    {
        glPushMatrix();
        glTranslatef(playerPos.x, playerPos.y, playerPos.z);
        glRotatef(rotateY, 0.0f, 1.0f, 0.0f);
        glScalef(scaleX, scaleY, scaleZ);
        md2Model->Draw();
        glPopMatrix();
    }
    glPopMatrix();
}

// --- NEW CORE FUNCTION: Handles Input, Movement, and Animation ---
void Player::handleInputAndMove(float dt, Camera* camera, Inputs* kBMs, const Settings& settings)
{
    // --- 1. Movement Speed Calculation ---
    float playerMoveSpeed = settings.playerBaseSpeed * dt;
    if (kBMs->isSprinting) playerMoveSpeed *= settings.playerSprintMultiplier;

    // Use Camera class for direction
    float angleYRad = camera->angleY * M_PI / 180.0f;  // <-- camera class
    vec2 camForward = { -sin(angleYRad), -cos(angleYRad) };
    vec2 camRight   = {  cos(angleYRad), -sin(angleYRad) };

    // Combine movement input
    vec2 moveVector = {0.0f, 0.0f};
    if (kBMs->isMovingUp)    { moveVector.x += camForward.x; moveVector.y += camForward.y; }
    if (kBMs->isMovingDown)  { moveVector.x -= camForward.x; moveVector.y -= camForward.y; }
    if (kBMs->isMovingLeft)  { moveVector.x -= camRight.x;   moveVector.y -= camRight.y; }
    if (kBMs->isMovingRight) { moveVector.x += camRight.x;   moveVector.y += camRight.y; }

    bool isMoving = (moveVector.x != 0.0f || moveVector.y != 0.0f);

    if (isMoving)
    {
        // Normalize movement vector
        float mag = sqrt(moveVector.x * moveVector.x + moveVector.y * moveVector.y);
        moveVector.x /= mag;
        moveVector.y /= mag;

        // Apply movement
        playerPos.x += moveVector.x * playerMoveSpeed;
        playerPos.z += moveVector.y * playerMoveSpeed;

        // Rotate avatar to face movement
        rotateY = atan2(moveVector.x, moveVector.y) * 180.0f / M_PI;
        walk();
    }
    else
    {
        stand();
    }

    // Update avatar animation
    update(dt);
}
// --- End NEW CORE FUNCTION ---


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
    // In a real game, replace 0.05 with a random number generator that yields [0.0, 1.0]
    double randomNumber = 0.05; 
    if(stats["Dodge"] >= randomNumber) return 1;
    else return 0;
}
double Player::armorHandler(double penetration) {
    double effectiveArmor = abs(stats["Armor"] - penetration);
    return 1 - (effectiveArmor / (10 + effectiveArmor));
}
// void Player::addItemToInventory(Item newItem) {
//     int newID = newItem.ID;
//     if(itemStats.size() <= newItem.ID) {itemStats.resize(newItem.ID + 1);} 
//     if(itemStats.at(newID).count == 0){
//         itemStats.at(newItem.ID) = newItem;
//         itemStats.at(newID).count = 1;
//     } else {itemStats.at(newID).count += 1;}
//     equipItem(newItem);
// }
bool Player::isWeapon(Item item){
    if(item.type == "Weapon") return true;
    return false;
}
bool Player::isGadget(Item item){
    if(item.type == "Gadget") return true;
    return false;
}
void Player::equipItem(Item item) {
    for(const auto& pair : item.stats) {
        const std::string& statName = pair.first;
        double statValue = pair.second;

        if(stats.count(statName)) {
            // Apply a modifier, assuming item stats are bonuses
            addStat(statName, statValue); 
        } else {
            stats[statName] = statValue;
        }
    }
}
int Player::inventorySize() {
    int size = 0;
    for(int i = 0; i < itemStats.size(); i++){
        if(itemStats.at(i).count > 0) size++;
    }
    return size;
}
