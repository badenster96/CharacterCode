#ifndef _COLLISIONCHECK_H
#define _COLLISIONCHECK_H

#include <math.h>

#include "Player.h"


class CollisionCheck
{
    public:
        CollisionCheck();
        virtual ~CollisionCheck();

        bool isLinearCol(vec3,vec3);
        bool isRadialCol(vec2,vec2,float,float,float);
        bool isSphereCol(vec3,vec3,float,float,float);
        bool isPlanarCol(vec2,vec2);
        bool isCubicCol (vec3,vec3);


    protected:

    private:
};

#endif // _COLLISIONCHECK_H
