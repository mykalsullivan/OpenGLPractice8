//
// Created by msullivan on 6/5/24.
//

#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    Camera() = default;
    Camera(glm::vec3 startPosition,
           glm::vec3 startUp,
           float startYaw,
           float startPitch,
           float startMoveSpeed,
           float startTurnSpeed);
    ~Camera() = default;
private:
    glm::vec3 m_Position;
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    glm::vec3 m_WorldUp;    /* Where the sky is */

    float m_Yaw;            /* yaw = left/right */
    float m_Pitch;          /* pitch = up/down */
    float m_MoveSpeed;
    float m_TurnSpeed;
public:
    void update();
    void keyControl(const bool* keys, float deltaTime);
    void mouseControl(float changeX, float changeY);
    glm::mat4 calculateViewMatrix();
};