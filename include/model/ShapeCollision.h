#ifndef _FAR_CRY_SHAPECOLLISION_H
#define _FAR_CRY_SHAPECOLLISION_H

#include "model/LineShape.h"
#include "model/CircleShape.h"
#include "model/PolygonShape.h"

namespace model
{
    class ShapeCollision
    {
    public:
        ShapeCollision();
        virtual ~ShapeCollision();
        static bool testCollision(Shape *shape1, Shape *shape2);
    private:
        static bool testLineLineCollision(LineShape *line1, LineShape *line2);
        static bool testLineCircleCollision(LineShape *line, CircleShape *circle);
        static bool testLinePolygonCollision(LineShape *line, PolygonShape *polygon);
        static bool testCircleCircleCollision(CircleShape *circle1, CircleShape *circle2);
        static bool testCirclePolygonCollision(CircleShape *circle, PolygonShape *polygon);
        static bool testPolygonPolygonCollision(PolygonShape *polygon1, PolygonShape *polygon2);
    };
}
#endif // _FAR_CRY_SHAPECOLLISION_H
