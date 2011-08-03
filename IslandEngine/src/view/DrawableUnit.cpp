#include <math.h>
#include <stdio.h>
#include "glfw.h"
#include "view/DrawableUnit.h"

using namespace view;

DrawableUnit::DrawableUnit(std::vector<model::Shape*> shapes, bool visible)
    : model::Unit(shapes, visible)
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
    drawBounds();
    drawDirection();
}

void DrawableUnit::drawBounds()
{
    for(unsigned int i = 0; i < shapes().size(); i++)
    {
        shapes().at(i)->draw();
    }
}

void DrawableUnit::drawDirection()
{
    core::Point2 p = pos();
    core::Point2 d = direction();

    glColor3f(1.f,0.f,0.f);
    glBegin(GL_LINES);
        glVertex2f(p[0],p[1]);
        glVertex2f(p[0]+(d[0]*30.f),p[1]+(d[1]*30.f));
    glEnd();
}
