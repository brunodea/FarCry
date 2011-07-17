#include <math.h>
#include "glfw.h"
#include "view/DrawableUnit.h"

#define PI 3.141592

using namespace view;

DrawableUnit::DrawableUnit(model::Shape *shape, bool visible)
    : model::Unit(shape, visible)
{
}

DrawableUnit::~DrawableUnit()
{
}

void DrawableUnit::onUpdate()
{
}

void DrawableUnit::onRender()
{
    drawDirection();
    drawBounds();
}

void DrawableUnit::drawBounds()
{
    if(shape()->type() == model::Shape::CIRCLE)
    {
        model::CircleShape *circle = (model::CircleShape*)shape();

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
    else if(shape()->type() == model::Shape::LINE)
    {
        model::LineShape *line = (model::LineShape*)shape();
        core::Point2 p = line->origin();
        core::Point2 d = line->ending();

        glBegin(GL_LINES);

        glVertex2f(p[0], p[1]);
        glVertex2f(d[0], d[1]);

        glEnd();
    }
    else if(shape()->type() == model::Shape::POLYGON)
    {
        model::PolygonShape *polygon = (model::PolygonShape*)shape();

        model::LineShape *line;

        glBegin(GL_LINES);

        for(unsigned int i = 0; i < polygon->lines()->size(); i++)
        {
            line = &polygon->lines()->at(i);

            glVertex2f(line->origin()[0], line->origin()[1]);
            glVertex2f(line->ending()[0], line->ending()[1]);
        }

        glEnd();
    }
}

void DrawableUnit::drawDirection()
{
    core::Point2 p = pos();
    core::Point2 d = direction();

    float r;

    if(shape()->type() == model::Shape::CIRCLE)
    {
        r = ((model::CircleShape*)shape())->radius();
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
