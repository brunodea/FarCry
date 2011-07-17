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

    model::CircleShape *shape = new model::CircleShape();
    shape->setRadius(45);

    view::DrawableUnit u;
    u.setCollisionShape(shape);
    u.draw();
}

void Controller::onUpdate()
{
}

void Controller::onKeyEvent(int key, int state)
{
}
