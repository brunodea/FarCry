#include "glfw.h"
#include "model/PolygonShape.h"
#include "util/collision_functions.h"

using namespace model;

PolygonShape::PolygonShape()
    : Shape(Shape::POLYGON), m_vLines(), m_Center(core::point2f(0.f,0.f))
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
    adjustCenter();
}

std::vector<LineShape> *PolygonShape::lines()
{
    return &m_vLines;
}

core::Point2 PolygonShape::center()
{
    return m_Center;
}

void PolygonShape::adjustCenter()
{
    core::Point2 up_left = core::point2f(-999999.f, 999999.f);
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

    m_Center = (up_left+down_right)/2.f;
}

void PolygonShape::setCenter(const core::Point2 &pos)
{
    core::Point2 diff = pos - m_Center;
    for(unsigned int i = 0; i < m_vLines.size(); i++)
    {
        LineShape *line = &m_vLines.at(i);

        core::Point2 orig = line->origin()+diff;
        core::Point2 end = line->ending()+diff;

        line->setOrigin(orig);
        line->setEnding(end);
    }
    m_Center = pos;
}

void PolygonShape::rotate(float angle)
{
    core::Point2 old_center = m_Center;
//    setCenter(core::point2f(0.f,0.f));
    core::Matrix3 transf_mat = core::rotate2d(angle);

    for(unsigned int i = 0; i < m_vLines.size(); i++)
    {
        LineShape *line = &m_vLines.at(i);

        core::Point3 orig3 = core::toPoint3f(line->origin());
        orig3 = transf_mat*orig3;
        core::Point2 orig = core::toPoint2f(orig3);

        core::Point3 end3 = core::toPoint3f(line->ending());
        end3 = transf_mat*end3;
        core::Point2 end = core::toPoint2f(end3);

        line->setOrigin(orig);
        line->setEnding(end);
    }
//    setCenter(old_center);
}
