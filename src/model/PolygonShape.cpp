#include "glfw.h"
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

void PolygonShape::draw()
{
    model::LineShape *line;

    glBegin(GL_LINES);

        for(unsigned int i = 0; i < lines()->size(); i++)
        {
            line = &lines()->at(i);

            glVertex2f(line->origin()[0], line->origin()[1]);
            glVertex2f(line->ending()[0], line->ending()[1]);
        }

    glEnd();
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

    for(unsigned int i = 0; i < m_vLines.size(); i++)
    {
        LineShape *line = &m_vLines.at(i);
        if(line->origin()[0] < up_left[0] && line->origin()[1] > up_left[1])
            up_left = line->origin();
        else if(line->ending()[0] < up_left[0] && line->ending()[1] > up_left[1])
            up_left = line->ending();

        if(line->origin()[0] > down_right[0] && line->origin()[1] < down_right[1])
            down_right = line->origin();
        else if(line->ending()[0] > down_right[0] && line->ending()[1] < down_right[1])
            down_right = line->ending();
    }

    return (up_left+down_right)/2.f;
}

void PolygonShape::setCenter(const core::Point2 &pos)
{
    core::Point2 diff = pos - center();
    for(unsigned int i = 0; i < m_vLines.size(); i++)
    {
        LineShape *line = &m_vLines.at(i);

        core::Point2 orig = line->origin()+diff;
        core::Point2 end = line->ending()+diff;

        line->setOrigin(orig);
        line->setEnding(end);
    }
}

