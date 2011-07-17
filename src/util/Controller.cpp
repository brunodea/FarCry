#include <iostream>
#include "glfw.h"
#include "util/Controller.h"
#include "view/DrawableUnit.h"

using namespace util;

Controller *Controller::m_sInstance = NULL;

Controller::Controller()
    : m_bRunning(true)
{
}

Controller *Controller::instance()
{
    if(m_sInstance == NULL)
        m_sInstance = new Controller();
    return m_sInstance;
}

void Controller::run()
{
    double last_render = 0;
    double last_update = 0;

    double frame_interval = 1.f/60.f;
    double update_interval = 1.f/90.f;

    double cur_time = 0;
    while(isRunning())
    {
        cur_time = glfwGetTime();
        if(cur_time - last_update > update_interval)
        {
            onUpdate();
            last_update = glfwGetTime();
        }
        if(cur_time - last_render > frame_interval)
        {
            last_render = glfwGetTime();
            onRender();
            glfwSwapBuffers();
        }

        m_bRunning = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
        glfwSleep(update_interval - (cur_time + glfwGetTime()));
    }
}

void Controller::onRender()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);

    glTranslatef(100.f,100.f,0.f);

    view::DrawableUnit u;

    //Exemplo de DrawableUnit com LineShape como CollisionBounds
    core::Point2 o;
    core::Point2 e;

    o[0] = 0;
    o[1] = 0;
    e[0] = 50;
    e[1] = 0;

    model::LineShape *line = new model::LineShape();
    line->setOrigin(o);
    line->setEnding(e);

    u.setCollisionShape(line);

    glColor3f(1, 0, 0);
    u.draw();

    //Exemplo de DrawableUnit com CircleShape como CollisionBounds
    core::Point2 c;
    c[0] = 0;
    c[1] = 0;

    model::CircleShape *circle = new model::CircleShape();
    circle->setCenter(c);
    circle->setRadius(50);

    u.setCollisionShape(circle);

    glTranslatef(150.f, 0, 0);
    glColor3f(0, 1, 0);
    u.draw();
}

void Controller::onUpdate()
{
}

void Controller::onKeyEvent(int key, int state)
{
}
