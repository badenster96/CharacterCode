#include "Collisioncheck.h"

CollisionCheck::CollisionCheck()
{
    //ctor
}

CollisionCheck::~CollisionCheck()
{
    //dtor
}
bool CollisionCheck::isLinearCol(vec3, vec3)
{
        return false;
}

bool CollisionCheck::isRadialCol(vec2 p1, vec2 p2, float r1, float r2, float threshold)
{
    return (sqrt(pow((p1.x - p2.x),2) + pow((p1.y - p2.y),2)) - (r1+r2) < threshold);
}

bool CollisionCheck::isSphereCol(vec3 p1, vec3 p2, float r1, float r2, float threshold)
{
    return (sqrt(pow((p1.x - p2.x),2) + pow((p1.y - p2.y),2) + pow((p1.z - p2.z),2)) - (r1+r2) < threshold);
}

bool CollisionCheck::isPlanarCol(vec2 , vec2)
{
        return false;
}

bool CollisionCheck::isCubicCol(vec3, vec3)
{
        return false;
}

