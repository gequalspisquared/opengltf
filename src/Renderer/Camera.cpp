#include "Renderer/Camera.h"
#include "glm/ext/matrix_clip_space.hpp"

#include <glm/ext/matrix_transform.hpp>

Camera::Camera(
    glm::vec3 position, /* = glm::vec3(0.0f, 0.0f, 0.0f) */
    glm::vec3 up,       /* = glm::vec3(0.0f, 1.0f, 0.0f) */
    float yaw,          /* = camera_defaults::yaw */
    float pitch         /* = camera_defaults::pitch */
)
{
    m_position = position;
    m_world_up = up;
    m_yaw      = yaw;
    m_pitch    = pitch;

    updateVectors();
}

Camera::~Camera()
{
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::getPerspectiveProjection(int width, int height) const
{
    float aspect = (float)width / (float)height;
    return glm::perspective(glm::radians(m_zoom), aspect, 0.1f, 100.0f);
}

void Camera::move(CameraMovement direction, float delta_time)
{
    float velocity = m_speed * delta_time;

    if (direction == CameraMovement::FORWARD) {
        m_position += m_front * velocity;
    }

    if (direction == CameraMovement::BACKWARD) {
        m_position -= m_front * velocity;
    }

    if (direction == CameraMovement::LEFT) {
        m_position -= m_right * velocity;
    }

    if (direction == CameraMovement::RIGHT) {
        m_position += m_right * velocity;
    }

    if (direction == CameraMovement::UP) {
        m_position += m_world_up * velocity;
    }

    if (direction == CameraMovement::DOWN) {
        m_position -= m_world_up * velocity;
    }
}

void Camera::processMouse(
    float offset_x,
    float offset_y,
    bool constrain_pitch /* = true */
)
{
    offset_x *= m_sensitivity;
    offset_y *= m_sensitivity;

    m_yaw   += offset_x;
    m_pitch += offset_y;

    // Make sure that pitch doesn't exceed +/- 90 degrees
    if (constrain_pitch) {
        if (m_pitch > 89.0f) {
            m_pitch = 89.0f;
        } else if (m_pitch < -89.0f) {
            m_pitch = -89.0f;
        }
    }

    updateVectors();
}

void Camera::processScroll(float offset_y)
{
    m_zoom -= offset_y;

    if (m_zoom < 1.0f) {
        m_zoom = 1.0f;
    } else if (m_zoom > 45.0f) {
        m_zoom = 45.0f;
    }
}

void Camera::updateVectors()
{
    // Calculate new front vector
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);

    // Recalculate right and up vectors
    m_right = glm::normalize(glm::cross(m_front, m_world_up));
    m_up    = glm::normalize(glm::cross(m_right, m_front));
}
