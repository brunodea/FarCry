#include "model/PolygonShape.h"
#include "util/collision_functions.h"

using namespace model;

PolygonShape::PolygonShape()
    : Shape(Shape::POLYGON), m_vLines()
{
}

PolygonShape::~PolygonShape()
{
}

bool PolygonShape::collided(Shape* shape)
{
    return util::testCollision(this, shape);
}

void PolygonShape::addLine(const LineShape &line)
{
    m_vLines.push_back(line);
}

std::vector<LineShape> *PolygonShape::lines()
{
    return &m_vLines;
}

core::Point2 PolygonShape::center()
{
    core::Point2 up_left = core::point2f(999999.f, -999999.f);
    core::Point2 down_right = up_left*(-1);
    return up_left;
}
