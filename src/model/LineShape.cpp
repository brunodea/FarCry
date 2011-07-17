#include "glfw.h"
#include "model/LineShape.h"
#include "core/matrix_functions.hpp"
#include "util/collision_functions.h"

using namespace model;

LineShape::LineShape()
    : Shape(Shape::LINE), m_Origin(0), m_Ending(0)
{
}

LineShape::~LineShape()
{
}

bool LineShape::collided(Shape *shape)
{
    return util::testCollision(this, shape);
}

void LineShape::rotate(float angle)
{
}

void LineShape::draw()
{
    core::Point2 p = origin();
    core::Point2 d = ending();

    glBegin(GL_LINES);

        glVertex2f(p[0], p[1]);
        glVertex2f(d[0], d[1]);

    glEnd();
}

void LineShape::setOrigin(const core::Point2 &origin)
{
    m_Origin = origin;
}

void LineShape::setEnding(const core::Point2 &ending)
{
    m_Ending = ending;
}

core::Point2 LineShape::origin()
{
    return m_Origin;
}

core::Point2 LineShape::ending()
{
    return m_Ending;
}

core::Point2 LineShape::center()
{
    return (origin()+ending())/2.f;
}

void LineShape::setCenter(const core::Point2 &pos)
{
    core::Point2 diff = pos - center();
    m_Origin += diff;
    m_Ending += diff;
}

