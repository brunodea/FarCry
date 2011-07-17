#include <math.h>
#include "model/CircleShape.h"
#include "util/collision_functions.h"

using namespace model;

CircleShape::CircleShape()
    : Shape(Shape::CIRCLE), m_Radius(0)
{
}

CircleShape::~CircleShape()
{
}

void CircleShape::setRadius(float radius)
{
    m_Radius = radius;
}

float CircleShape::radius()
{
    return m_Radius;
}

bool CircleShape::collided(Shape* shape)
{
    return util::testCollision(this, shape);
}

void CircleShape::setCenter(const core::Point2 &center)
{
    m_Center = center;
}

core::Point2 CircleShape::center()
{
    return m_Center;
}
