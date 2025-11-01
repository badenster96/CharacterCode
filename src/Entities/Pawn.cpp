#include "Entities/Pawn.h"

// Pawns are objects that exist in the world. Each pawn has a unique ID when they are spawned in the world.
void Pawn::setObjectID(int newObjectID) {objectID = newObjectID;}
void Pawn::setAlive(bool newIsAlive){isAlive = newIsAlive;}
int Pawn::getObjectID(){return objectID;}