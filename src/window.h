//
// Created by msullivan on 6/4/24.
//

#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLWindow
{
public:
    GLWindow();
    GLWindow(int width, int height);
    ~GLWindow();
private:
    GLFWwindow* m_Window = nullptr;
    int m_BufferWidth, m_BufferHeight;

    bool m_Keys[1024];

    float m_LastX, m_LastY;
    float m_ChangeX, m_ChangeY;
    bool m_MouseFirstMoved = true;
public:
    constexpr int getBufferWidth() const { return m_BufferWidth; }
    constexpr int getBufferHeight() const { return m_BufferHeight; }

    int init();
    bool shouldClose() { return glfwWindowShouldClose(m_Window); }
    void swapBuffers() { return glfwSwapBuffers(m_Window); }

    void createCallbacks();
    static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
    static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};