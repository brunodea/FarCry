#include <math.h>
#include <stdio.h>
#include "glfw.h"
#include "view/DrawableUnit.h"

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
    drawBounds();
    drawDirection();
}

void DrawableUnit::drawBounds()
{
    core::Point2 p = pos();
    core::Point2 d = direction();

    //printf("DUnit: %.2f %.2f %.2f %.2f\n", p[0], p[1], d[0], d[1]);

    shape()->draw();
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
