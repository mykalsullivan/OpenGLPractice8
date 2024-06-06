//
// Created by msullivan on 6/4/24.
//

#include "window.h"

#include <iostream>

GLWindow::GLWindow() : m_BufferWidth(800), m_BufferHeight(600), m_Keys()
{}

GLWindow::GLWindow(int width, int height) : m_BufferWidth(width), m_BufferHeight(height), m_Keys()
{}

GLWindow::~GLWindow()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

int GLWindow::init()
{
    m_Window = glfwCreateWindow((int) m_BufferWidth, (int) m_BufferHeight, "OpenGL Practice", nullptr, nullptr);

    // Return if the main GLFW window cannot be created
    if (m_Window == nullptr)
    {
        std::cout << "Could not create main GLFW window\n";
        glfwTerminate();
        return 1;
    }

    // Setup GLFW window properties
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Core profile = no backwards compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);

    // Get buffer size information
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(m_Window, &bufferWidth, &bufferHeight);

    // Set context for GLEW to use
    glfwMakeContextCurrent(m_Window);

    // Handle key and mouse input
    createCallbacks();
    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Used to prevent sides from being rendered incorrectly
    glEnable(GL_DEPTH_TEST);

    // Create viewport
    glViewport(0, 0, m_BufferWidth, m_BufferHeight);

    glfwSetWindowUserPointer(m_Window, this);

    return 0;
}

void GLWindow::createCallbacks()
{
    glfwSetKeyCallback(m_Window, handleKeys);
    glfwSetCursorPosCallback(m_Window, handleMouse);
}

void GLWindow::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
    // Grabs GLWindow instance
    auto* theWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            theWindow->m_Keys[key] = true;
            printf("Pressed %d\n", key);
        }
        else if (action == GLFW_RELEASE)
        {
            theWindow->m_Keys[key] = false;
            printf("Released %d\n", key);
        }
    }
}

void GLWindow::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
    auto* theWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));

    if (theWindow->m_MouseFirstMoved)
    {
        theWindow->m_LastX = (float) xPos;
        theWindow->m_LastY = (float) yPos;
        theWindow->m_MouseFirstMoved = false;
    }

    theWindow->m_ChangeX = (float) xPos - theWindow->m_LastX;
    theWindow->m_ChangeY = (float) yPos - theWindow->m_LastY;

    theWindow->m_LastX = (float) xPos;
    theWindow->m_LastY = (float) yPos;

    printf("x: %.6f, y: %.6f\n", xPos, yPos);
}