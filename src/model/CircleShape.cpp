#include <math.h>
#include "glfw.h"
#include "macros.h"
#include "model/CircleShape.h"
#include "util/collision_functions.h"

using namespace model;

CircleShape::CircleShape()
    : Shape(Shape::CIRCLE), m_Radius(0), m_vVertices()
{
}

CircleShape::~CircleShape()
{
}

void CircleShape::adjustVertices()
{
    float x = 0.f;
    float y = 0.f;

    for(float ang = 0; ang < 2*PI; ang += 0.1)
    {
        x = radius() * cos(ang);
        y = radius() * sin(ang);

        m_vVertices.push_back(core::vector2f(x,y));
    }
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

void CircleShape::rotate(float angle)
{
}

void CircleShape::draw()
{
    glBegin(GL_LINE_LOOP);
        for(unsigned int i = 0; i < m_vVertices.size(); i++)
        {
            core::Vector2 v = m_vVertices.at(i);
            glVertex2f(v[0]+m_Center[0],v[1]+m_Center[1]);
        }
    glEnd();
}

core::Point2 CircleShape::center()
{
    return m_Center;
}

void CircleShape::setCenter(const core::Point2 &center)
{
    m_Center = center;
    adjustVertices();
}
