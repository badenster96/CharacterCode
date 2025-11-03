#ifndef _COLLISIONCHECK_H
#define _COLLISIONCHECK_H

#include "Helpers/Common.h"
#include "Entities/Player.h"

class CollisionCheck
{
public:
    CollisionCheck();
    virtual ~CollisionCheck();

    /*
    * NOTE: The collision functions are marked 'static' because they don't
    * depend on any instance member variables. This lets you call them
    * directly without creating an object.
    */

    /**
     * @brief Checks for overlap between two 1D line segments (AABBs).
     * @param p1 Center position of the first line segment.
     * @param halfSize1 Half-length of the first line segment.
     * @param p2 Center position of the second line segment.
     * @param halfSize2 Half-length of the second line segment.
     */
    static bool isLinearCol(float p1, float halfSize1, float p2, float halfSize2);

    /**
     * @brief Checks for collision between two 2D circles (radial).
     * 
     * @param p1 Center position of the first circle.
     * @param p2 Center position of the second circle.
     * @param r1 Radius of the first circle.
     * @param r2 Radius of the second circle.
     * @param threshold An extra "buffer" distance. Collision is detected
     * if (distance - (r1+r2)) < threshold.
     */
    static bool isRadialCol(vec2 p1, vec2 p2, float r1, float r2, float threshold);

    /**
     * @brief Checks for collision between two 3D spheres.
     * @param p1 Center position of the first sphere.
     * @param p2 Center position of the second sphere.
     * @param r1 Radius of the first sphere.
     * @param r2 Radius of the second sphere.
     * @param threshold An extra "buffer" distance.
     */
    static bool isSphereCol(vec3 p1, vec3 p2, float r1, float r2, float threshold);

    /**
     * @brief Checks for overlap between two 2D Axis-Aligned Bounding Boxes (AABBs).
     * 
     * @param p1 Center position of the first box.
     * @param halfSize1 vec2 containing half-width and half-height of the first box.
     * @param p2 Center position of the second box.
     * @param halfSize2 vec2 containing half-width and half-height of the second box.
     */
    static bool isPlanarCol(vec2 p1, vec2 halfSize1, vec2 p2, vec2 halfSize2);

    /**
     * @brief Checks for overlap between two 3D Axis-Aligned Bounding Boxes (AABBs).
     * @param p1 Center position of the first box.
     * @param halfSize1 vec3 containing half-width, half-height, and half-depth.
     * @param p2 Center position of the second box.
     * @param halfSize2 vec3 containing half-width, half-height, and half-depth.
     */
    static bool isCubicCol(vec3 p1, vec3 halfSize1, vec3 p2, vec3 halfSize2);


protected:

private:
};

#endif // _COLLISIONCHECK_H