#include "CollisionCheck.h"
#include <cmath> // For std::abs, pow, and sqrt

CollisionCheck::CollisionCheck()
{
    //ctor
}

CollisionCheck::~CollisionCheck()
{
    //dtor
}

/*
* NOTE: The original signature 'isLinearCol(vec3, vec3)' was ambiguous.
* This implementation assumes 'linear' collision refers to 1D Axis-Aligned
* Bounding Boxes (AABBs), i.e., checking if two line segments on the same axis overlap.
* The signature is changed to accept 1D center positions and their half-lengths.
*/
bool CollisionCheck::isLinearCol(float p1, float halfSize1, float p2, float halfSize2)
{
    // Check if the distance between centers is less than the sum of half-lengths
    return std::abs(p1 - p2) < (halfSize1 + halfSize2);
}

/*
* Your original implementation, optimized to avoid 'sqrt'.
* Comparing squared distances is much faster.
*/
bool CollisionCheck::isRadialCol(vec2 p1, vec2 p2, float r1, float r2, float threshold)
{
    // Calculate the squared distance between centers
    float distSq = pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2);
    
    // Calculate the total radius + threshold, then square it
    float totalRadius = r1 + r2 + threshold;
    float totalRadiusSq = totalRadius * totalRadius;
    
    // Return true if the squared distance is less than the squared radius
    return distSq < totalRadiusSq;
}

/*
* Your original implementation, optimized to avoid 'sqrt'.
*/
bool CollisionCheck::isSphereCol(vec3 p1, vec3 p2, float r1, float r2, float threshold)
{
    // Calculate the squared distance between centers
    float distSq = pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2) + pow((p1.z - p2.z), 2);
    
    // Calculate the total radius + threshold, then square it
    float totalRadius = r1 + r2 + threshold;
    float totalRadiusSq = totalRadius * totalRadius;
    
    // Return true if the squared distance is less than the squared radius
    return distSq < totalRadiusSq;
}

/*
* NOTE: The original signature 'isPlanarCol(vec2, vec2)' was insufficient
* for a 2D box (planar) collision.
* This implementation assumes 2D Axis-Aligned Bounding Box (AABB) collision.
* The signature is changed to accept center positions and half-sizes (half-width, half-height).
*/
bool CollisionCheck::isPlanarCol(vec2 p1, vec2 halfSize1, vec2 p2, vec2 halfSize2)
{
    // Check for overlap on the X-axis
    bool overlapX = std::abs(p1.x - p2.x) < (halfSize1.x + halfSize2.x);
    
    // Check for overlap on the Y-axis
    bool overlapY = std::abs(p1.y - p2.y) < (halfSize1.y + halfSize2.y);
    
    // Collision occurs only if there is overlap on *both* axes
    return overlapX && overlapY;
}

/*
* NOTE: The original signature 'isCubicCol(vec3, vec3)' was insufficient
* for a 3D box (cubic) collision.
* This implementation assumes 3D Axis-Aligned Bounding Box (AABB) collision.
* The signature is changed to accept center positions and half-sizes.
*/
bool CollisionCheck::isCubicCol(vec3 p1, vec3 halfSize1, vec3 p2, vec3 halfSize2)
{
    // Check for overlap on the X-axis
    bool overlapX = std::abs(p1.x - p2.x) < (halfSize1.x + halfSize2.x);
    
    // Check for overlap on the Y-axis
    bool overlapY = std::abs(p1.y - p2.y) < (halfSize1.y + halfSize2.y);
    
    // Check for overlap on the Z-axis
    bool overlapZ = std::abs(p1.z - p2.z) < (halfSize1.z + halfSize2.z);
    
    // Collision occurs only if there is overlap on *all three* axes
    return overlapX && overlapY && overlapZ;
}