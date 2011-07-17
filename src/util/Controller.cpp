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
    model::LineShape l1;
    model::LineShape l2;
    model::LineShape l3;

    float s = 2.f;
    l1.setOrigin(core::point2f(-5.f,5.f)*s);
    l1.setEnding(core::point2f(5.f,5.f)*s);

    l2.setOrigin(core::point2f(-5.f,5.f)*s);
    l2.setEnding(core::point2f(0.f,-10.f)*s);

    l3.setOrigin(core::point2f(5.f,5.f)*s);
    l3.setEnding(core::point2f(0.f,-10.f)*s);

    model::PolygonShape *polygon = new model::PolygonShape();
    polygon->addLine(l1);
    polygon->addLine(l2);
    polygon->addLine(l3);


//    model::CircleShape *circle1 = new model::CircleShape();
//    circle1->setRadius(10.f*s);

    m_DUnit.setShape(polygon);
    m_DUnit.setAccel(1.f);
    m_DUnit.setMaxSpeed(3.f);
    m_DUnit.setDirection(core::vector2f(0.f,-1.f));

    model::CircleShape *circle = new model::CircleShape();
    circle->setRadius(10.f*s);

    m_DCircleUnit.setShape(circle);
    m_DCircleUnit.setAccel(90.f);
    m_DCircleUnit.setMaxSpeed(100.f);
    m_DCircleUnit.setDirection(core::vector2f(1.f,1.f));
    m_DCircleUnit.speedUp();
    m_DCircleUnit.move();
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
    glColor3f(1.0, 0, 1.0);
    m_DUnit.onRender();

    glColor3f(0.f,1.f,1.f);
    m_DCircleUnit.onRender();
}

void Controller::onUpdate()
{
    float angle = PI/50.f;
    if(glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
        m_DUnit.rotate(-angle);
    else if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
        m_DUnit.rotate(angle);

    m_DUnit.move();
    m_DUnit.shape()->center().print();
//    if(m_DUnit.shape()->collided(m_DCircleUnit.shape()))
//        std::cout << "Colidiram!\n";
}

void Controller::onKeyEvent(int key, int state)
{
    if(state == GLFW_PRESS)
    {
        if(key == GLFW_KEY_UP)
            m_DUnit.speedUp();
        else if(key == GLFW_KEY_DOWN)
            m_DUnit.speedDown();
    }
}
