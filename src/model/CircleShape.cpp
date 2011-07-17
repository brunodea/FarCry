#include <math.h>
#include "glfw.h"
#include "macros.h"
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

void CircleShape::draw()
{
    glBegin(GL_LINE_LOOP);

        float x = 0.0;
        float y = 0.0;

        for(float ang = 0; ang < 2*PI; ang += 0.1)
        {
            x = radius() * cos(ang);
            y = radius() * sin(ang);

            glVertex2f(x, y);
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
}
