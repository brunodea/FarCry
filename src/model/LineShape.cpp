#include "model/LineShape.h"
#include "core/matrix_functions.hpp"

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

    }

    return false;
}

void LineShape::setOrigin(core::Point2 &origin)
{
    m_Origin = origin;
}

void LineShape::setEnding(core::Point2 &ending)
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

bool LineShape::intersectsLine(LineShape &line, float &s, float &t)
{
    core::Point2 d = line.ending();

    float det = (d[0] * m_Ending[1]) - (d[1] * m_Ending[0]);

    core::Point2 diff = line.origin() - m_Origin;

    if(det*det > 0.001 * core::norm(m_Ending) * core::norm(d))
    {
        double invDet = 1.0/det;

        s = (d[0] * diff[1] - d[1] * diff[0]) * invDet;
        t = (m_Ending[0] * diff[1] - m_Ending[1] * diff[0]) * invDet;

        if(t > 0 && t < 1 && s > 0 && s < 1)
        {
            return true;
        }
    }

    return false;
}

/*bool LineShape::intersectsCircle(CircleShape *circle)
{
    float a, b, c, r2, delta;

    core::Point2 p = circle->center();
    core::Point2 center;

    center[0] = m_Origin[0] -
}
*/
