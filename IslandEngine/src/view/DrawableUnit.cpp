#include <math.h>
#include <stdio.h>
#include "glfw.h"
#include "view/DrawableUnit.h"
#include "view/SingleAnim.hpp"
#include "view/Animation.hpp"
#include "view/AnimFrame.hpp"

using namespace view;

DrawableUnit::DrawableUnit(bool visible, GLuint image_id)
    : model::Unit(visible)
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
    animation()->render();
}

void DrawableUnit::drawBounds()
{
    SingleAnim *sanim = animation()->currentSingleAnim();
    if(sanim != NULL)
    {
        AnimFrame *frame = sanim->currentFrame();
        if(frame != NULL)
            frame->drawShapes();
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
