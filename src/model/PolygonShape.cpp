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
}
