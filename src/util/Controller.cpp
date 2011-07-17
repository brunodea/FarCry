#include <iostream>
#include "glfw.h"
#include "util/Controller.h"
#include "view/DrawableUnit.h"

using namespace util;

Controller *Controller::m_sInstance = NULL;

Controller::Controller()
    : m_bRunning(true), m_DUnit(NULL,true)
{
    model::LineShape l1;
    model::LineShape l2;
    model::LineShape l3;

    l1.setOrigin(core::point2f(-5.f,3.f)*20.f);
    l1.setEnding(core::point2f(5.f,3.f)*20.f);

    l2.setOrigin(core::point2f(-5.f,3.f)*20.f);
    l2.setEnding(core::point2f(0.f,-5.f)*20.f);

    l3.setOrigin(core::point2f(5.f,3.f)*20.f);
    l3.setEnding(core::point2f(0.f,-5.f)*20.f);

    model::PolygonShape *polygon = new model::PolygonShape();
    polygon->addLine(l1);
    polygon->addLine(l2);
    polygon->addLine(l3);

    m_DUnit.setShape(polygon);
    m_DUnit.setAccel(1.f);
    m_DUnit.setMaxSpeed(3.f);
    m_DUnit.setDirection(core::vector2f(0.f,-1.f));
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

    glTranslatef(200, 200, 0);
    glColor3f(1.0, 0, 1.0);
    m_DUnit.onRender();
    /*
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

    //Exemplo de DrawableUnit com PolygonShape como CollisionBounds
    model::LineShape l1;
    model::LineShape l2;
    model::LineShape l3;
    model::LineShape l4;

    core::Point2 p1;
    core::Point2 p2;
    core::Point2 p3;
    core::Point2 p4;

    p1[0] = -20;
    p1[1] = -20;
    p2[0] = 80;
    p2[1] = -20;
    p3[0] = 80;
    p3[1] = 80;
    p4[0] = -20;
    p4[1] = 80;

    l1.setOrigin(p1);
    l1.setEnding(p2);
    l2.setOrigin(p2);
    l2.setEnding(p3);
    l3.setOrigin(p3);
    l3.setEnding(p4);
    l4.setOrigin(p4);
    l4.setEnding(p1);

    model::PolygonShape *polygon = new model::PolygonShape();
    polygon->addLine(l1);
    polygon->addLine(l2);
    polygon->addLine(l3);
    polygon->addLine(l4);

    u.setCollisionShape(polygon);

    glTranslatef(0, 200, 0);
    glColor3f(1.0, 0, 1.0);
    u.draw();*/
}

void Controller::onUpdate()
{
    m_DUnit.move();
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
