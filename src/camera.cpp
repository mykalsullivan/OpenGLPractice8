//
// Created by msullivan on 6/5/24.
//

#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

Camera::Camera(glm::vec3 startPosition,
               glm::vec3 startUp,
               float startYaw,
               float startPitch,
               float startMoveSpeed,
               float startTurnSpeed)
        : m_Position(startPosition),
          m_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
          m_WorldUp(startUp),
          m_Yaw(startYaw),
          m_Pitch(startPitch),
          m_MoveSpeed(startMoveSpeed),
          m_TurnSpeed(startTurnSpeed)
{
    update();
}

void Camera::update()
{
    m_Front.x = (float) cos(glm::radians(m_Yaw) * cos(glm::radians(m_Pitch)));
    m_Front.y = (float) sin(glm::radians(m_Pitch));
    m_Front.z = (float) sin(glm::radians(m_Yaw) * cos(glm::radians(m_Pitch)));

    // Normalize the front
    m_Front = glm::normalize(m_Front);

    // Normalize the right
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));

    // Normalize the up
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

void Camera::keyControl(const bool* keys, float deltaTime)
{
    float velocity = m_MoveSpeed * deltaTime;
    
    if (keys[GLFW_KEY_W])
    {
        m_Position += m_Front * velocity;
    }

    if (keys[GLFW_KEY_A])
    {
        m_Position -= m_Right * velocity;
    }

    if (keys[GLFW_KEY_S])
    {
        m_Position -= m_Front * velocity;
    }

    if (keys[GLFW_KEY_D])
    {
        m_Position += m_Right * velocity;
    }
}

void Camera::mouseControl(float changeX, float changeY)
{
    changeX *= m_TurnSpeed;
    changeY *= m_TurnSpeed;

    m_Yaw += changeX;
    m_Pitch -= changeY;

    // Keeps your neck from snapping
    if (m_Pitch > 89.0f) m_Pitch = 89.0f;

    // Keeps you from looking like an idiot
    if (m_Pitch < -89.0f) m_Pitch = -89.0f;

    update();
}

glm::mat4 Camera::calculateViewMatrix()
{
    return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}