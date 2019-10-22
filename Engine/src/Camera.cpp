#include "Engine/Camera.h"
#include <iostream>

namespace Engine {
    Camera::Camera(glm::vec3 position, glm::vec3 worldUp)
    : m_position(position), m_worldUp(worldUp), m_front(glm::vec3(0.0f, 0.0f, -1.0f))
    {
        updateVectors();
    }

    glm::mat4 Camera::getViewMatrix() const {
        return glm::lookAt(m_position, m_position + m_front, m_worldUp);
    }

    void Camera::processKeyboard(Direction dir, float deltatime) {
        float velocity = m_speed * deltatime;
        if(dir == Direction::FORWARD)
            m_position += m_front * velocity;
        if(dir == Direction::BACKWARD)
            m_position -= m_front * velocity;
        if(dir == Direction::RIGHT)
            m_position += m_right * velocity;
        if(dir == Direction::LEFT)
            m_position -= m_right * velocity;
    }

    void Camera::processMouseMovement(float xOffset, float yOffset) {
        xOffset *= m_sens;
        yOffset *= m_sens;

        m_yaw += xOffset;
        m_pitch += yOffset;

        if(m_pitch > 89.0f)
            m_pitch = 89.0f;
        if(m_pitch < -89.0f)
            m_pitch = -89.0f;

        updateVectors();
    }

    void Camera::processMouseScroll(float yOffset) {
        if(m_zoom >= 1.0f && m_zoom <= 45.0f)
            m_zoom -= yOffset;
        if(m_zoom < 1.0f)
            m_zoom = 1.0f;
        if(m_zoom > 45.0f)
            m_zoom = 45.0f;
    }

    float Camera::getZoom() const {
        return m_zoom;
    }

    void Camera::updateVectors() {
        glm::vec3 front;
        front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        front.y = sin(glm::radians(m_pitch));
        front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front = glm::normalize(front);

        m_right = glm::normalize(glm::cross(m_front, m_worldUp));
        m_up = glm::normalize(glm::cross(m_right, m_front));
    }
}