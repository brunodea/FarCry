#include <math.h>
#include "model/CircleShape.h"

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
    if(shape->type() == Shape::LINE)
    {
        float s = 0;
        float t = 0;

        LineShape *line = (LineShape*)shape;

        return intersectsLine(*line, s, t);
    }
    else if(shape->type() == Shape::POLYGON)
    {

    }
    else if(shape->type() == Shape::CIRCLE)
    {
        CircleShape *circle = (CircleShape*)shape;

        return intersectsCircle(circle);
    }

    return false;
}

void CircleShape::setCenter(const core::Point2 &center)
{
    m_Center = center;
}

core::Point2 CircleShape::center()
{
    return m_Center;
}

bool CircleShape::intersectsCircle(CircleShape *circle)
{
    core::Point2 c = circle->center();

    float distance = sqrt(pow((m_Center[0] - c[0]), 2) + pow((m_Center[1] - c[1]), 2));

    return distance <= (m_Radius + circle->radius());
}

bool CircleShape::intersectsLine(LineShape &line, float &s, float &t)
{
    float a, b, c, r2, delta;

    core::Point2 center;
    core::Point2 p = line.origin();
    core::Point2 d = line.ending();

    center[0] = p[0] - m_Center[0];
    center[1] = p[1] - m_Center[1];

    r2 = m_Radius * m_Radius;

    a = d[0] * d[0] + d[1] * d[1];
    b = 2 * (m_Center[0] *d[0] + m_Center[1] * d[1]);
    c = m_Center[0] * m_Center[0] + m_Center[1] * m_Center[1] - r2;

    delta = b*b - 4*a*c;

    if(delta < 0)
    {
        return false;
    }
    else
    {
        s = ((-b)+sqrt(delta)) / (2*a);
        t = ((-b)-sqrt(delta)) / (2*a);

        if((t > 0 && t < 1) || (s > 0 && s < 1))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool CircleShape::intersectsPolygon(PolygonShape *polygon)
{
    for(unsigned int i = 0; i < polygon->lines()->size(); i++)
    {
        float s = 0;
        float t = 0;

        LineShape line = polygon->lines()->at(i);

        if(intersectsLine(line, s, t))
        {
            return true;
        }
    }

    return false;
}
