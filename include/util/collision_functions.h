#ifndef _FAR_CRY_COLLISIONFUNCTIONS_H_
#define _FAR_CRY_COLLISIONFUNCTIONS_H_

#include "model/Shape.h"
#include "model/LineShape.h"
#include "model/CircleShape.h"
#include "model/PolygonShape.h"

namespace util
{
    bool testCollision(model::Shape *shape1, model::Shape *shape2);
    bool testLineLineCollision(model::LineShape *line1, model::LineShape *line2);
    bool testLineCircleCollision(model::LineShape *line, model::CircleShape *circle);
    bool testLinePolygonCollision(model::LineShape *line, model::PolygonShape *polygon);
    bool testCircleCircleCollision(model::CircleShape *circle1, model::CircleShape *circle2);
    bool testCirclePolygonCollision(model::CircleShape *circle, model::PolygonShape *polygon);
    bool testPolygonPolygonCollision(model::PolygonShape *polygon1, model::PolygonShape *polygon2);
}

#endif
