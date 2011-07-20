#include <iostream>
#include "glfw.h"
#include "macros.h"
#include "util/Controller.h"
#include "view/DrawableUnit.h"
#include "core/matrix_functions.hpp"

using namespace util;

Controller *Controller::m_sInstance = NULL;

Controller::Controller()
    : m_bRunning(true), m_DUnit(NULL,true), m_DCircleUnit(NULL, true)
{
    model::LineShape *line = new model::LineShape();
    line->setOrigin(core::point2f(0.f, 25.f));
    line->setEnding(core::point2f(0.f, -25.f));
    line->setCenter(core::point2f(0.f, 0.f));

    m_DCircleUnit.setAccel(1.f);
    m_DCircleUnit.setSpeed(0.f);
    m_DCircleUnit.setMaxSpeed(3.f);
    m_DCircleUnit.setVisible(true);
    m_DCircleUnit.setShape(line);

    model::LineShape *line2 = new model::LineShape();
    line2->setOrigin(core::point2f(0.f, 25.f));
    line2->setEnding(core::point2f(0.f, -25.f));
    line2->setCenter(core::point2f(0.f, 0.f));

    m_DUnit.setAccel(1.f);
    m_DUnit.setSpeed(0.f);
    m_DUnit.setMaxSpeed(3.f);
    m_DUnit.setVisible(true);
    m_DUnit.setShape(line2);
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

    glTranslatef(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f, 0.f);

    glColor3f(0.f,1.f,1.f);
    m_DCircleUnit.onRender();
    m_DUnit.onRender();
}

void Controller::onUpdate()
{
    float angle = PI/50.f;
    if(glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        m_DCircleUnit.rotate(-angle);
    }
    else if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        m_DCircleUnit.rotate(angle);
    }

    m_DCircleUnit.move();
    if(m_DUnit.shape()->collided(m_DCircleUnit.shape()))
    {
        std::cout << "Colidiram!\n";
    }
}

void Controller::onKeyEvent(int key, int state)
{
    if(state == GLFW_PRESS)
    {
        if(key == GLFW_KEY_UP)
            m_DCircleUnit.speedUp();
        else if(key == GLFW_KEY_DOWN)
            m_DCircleUnit.speedDown();
    }
}
