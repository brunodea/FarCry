#include <cstdlib>
#include "GL/glfw.h"

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 512

/*
 * Callback functions
 */
void GLFWCALL keyEventCallback(int key, int state)
{
}

void GLFWCALL handleResize(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.f,(float)width/(float)height,0.1,5000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void setCallBacks()
{
    glfwSetKeyCallback(keyEventCallback);
    glfwSetWindowSizeCallback(handleResize);
}

void initOpenGL()
{
    handleResize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(0.f, 0.f, 0.f, 1.f);
}

void clear()
{
    //limpeza antes de terminar o programa.
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


    clear();
    exit(EXIT_SUCCESS);
}
