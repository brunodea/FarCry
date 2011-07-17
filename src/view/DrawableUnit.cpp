#include <math.h>
#include "glfw.h"
#include "view/DrawableUnit.h"

#define PI 3.141592

using namespace view;

DrawableUnit::DrawableUnit()
    : Drawable()
{
    core::Point2 pos;
    pos[0] = 0;
    pos[1] = 0;

    core::Point2 dir;
    dir[0] = 1;
    dir[1] = 0;

    m_Unit.setPos(pos);
    m_Unit.setDirection(dir);
}

DrawableUnit::~DrawableUnit()
{
}

void DrawableUnit::draw()
{
    drawDirection();
    drawBounds();
}

void DrawableUnit::drawBounds()
{
    if(m_CollisionBounds->type() == model::Shape::CIRCLE)
    {
        model::CircleShape *circle = (model::CircleShape*)m_CollisionBounds;

        glBegin(GL_LINE_LOOP);

        float x = 0.0;
        float y = 0.0;

        for(float ang = 0; ang < 2*PI; ang += 0.1)
        {
            x = circle->radius() * cos(ang);
            y = circle->radius() * sin(ang);

            glVertex2f(x, y);
        }

        glEnd();
    }
    else if(m_CollisionBounds->type() == model::Shape::LINE)
    {
        model::LineShape *line = (model::LineShape*)m_CollisionBounds;
        core::Point2 p = line->origin();
        core::Point2 d = line->ending();

        glBegin(GL_LINES);

        glVertex2f(p[0], p[1]);
        glVertex2f(d[0], d[1]);

        glEnd();
    }
}

void DrawableUnit::drawDirection()
{
    core::Point2 p = m_Unit.pos();
    core::Point2 d = m_Unit.direction();

    float r;

    if(m_CollisionBounds->type() == model::Shape::CIRCLE)
    {
        r = ((model::CircleShape*)m_CollisionBounds)->radius();
    }
    else
    {
        r = 20;
    }

    glBegin(GL_LINES);

    glVertex2f(p[0], p[1]);
    glVertex2f(d[0] * (r + (r*0.5)), d[1] * (r + (r*0.5)));

    glEnd();
}

void DrawableUnit::setCollisionShape(model::Shape *shape)
{
    m_CollisionBounds = shape;
}
