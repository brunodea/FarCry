#include <cstdlib>
#include <iostream>
#include "glfw.h"
#include "macros.h"
#include "Controller.h"

using namespace someisland;

/*
 * Callback functions
 */
void GLFWCALL mousePosCallback(int x, int y)
{
    //std::cout << x << "," << y << std::endl;
}

void GLFWCALL keyEventCallback(int key, int state)
{
    CONTROLLER->onKeyEvent(key, state);
}

void GLFWCALL handleResize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void setCallBacks()
{
    glfwSetMousePosCallback(mousePosCallback);
    glfwSetKeyCallback(keyEventCallback);
    glfwSetWindowSizeCallback(handleResize);
}

void initOpenGL()
{
    int w, h;

    glfwGetWindowSize(&w, &h);

    handleResize(w, h);
    glClearColor(0.f, 0.f, 0.f, 1.f);
}

void clear()
{
    delete CONTROLLER;
    delete view::Texture::instance();
}


int main()
{
    if(!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    if(!glfwOpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 8, 8, 8, 8, 8, 8, GLFW_WINDOW))
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    initOpenGL();
    setCallBacks();

    CONTROLLER->run();

    clear();
    exit(EXIT_SUCCESS);
}
