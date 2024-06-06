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

    float m_LastX = 0.0f, m_LastY = 0.0f;
    float m_ChangeX = 0.0f, m_ChangeY = 0.0f;
    bool m_MouseFirstMoved = true;
public:
    constexpr int getBufferWidth() const { return m_BufferWidth; }
    constexpr int getBufferHeight() const { return m_BufferHeight; }
    bool* getKeys() { return m_Keys; }
    float getChangeX();
    float getChangeY();

    int init();
    bool shouldClose() { return glfwWindowShouldClose(m_Window); }
    void swapBuffers() { return glfwSwapBuffers(m_Window); }

    void createCallbacks();
    static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
    static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};