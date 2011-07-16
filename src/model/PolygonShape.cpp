#include "model/PolygonShape.h"

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
    if(shape->type() == Shape::LINE)
    {

    }
    else if(shape->type() == Shape::POLYGON)
    {

    }
    else if(shape->type() == Shape::CIRCLE)
    {

    }

    return false;
}

void PolygonShape::addLine(const LineShape &line)
{
    m_vLines.push_back(line);
}

std::vector<LineShape> *PolygonShape::lines()
{
    return &m_vLines;
}
