#pragma once

#include <glm/glm.hpp>

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

namespace camera_defaults
{

const float yaw         = -90.0f;
const float pitch       = 0.0f;
const float speed       = 2.5f;
const float sensitivity = 0.1f;
const float zoom        = 45.0f;

};

class Camera
{
public:
    Camera(
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up       = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw          = camera_defaults::yaw,
        float pitch        = camera_defaults::pitch
    );
    ~Camera();

    glm::mat4 getViewMatrix() const;
    glm::mat4 getPerspectiveProjection(int width, int height) const;

    void move(CameraMovement direction, float delta_time);
    void processMouse(
        float offset_x,
        float offset_y,
        bool constrain_pitch = true
    );
    void processScroll(float offset_y);

private:
    glm::vec3 m_position = {};
    glm::vec3 m_front    = {};
    glm::vec3 m_up       = {};
    glm::vec3 m_right    = {};
    glm::vec3 m_world_up = {};
    float m_yaw          = camera_defaults::yaw;
    float m_pitch        = camera_defaults::pitch;
    float m_speed        = camera_defaults::speed;
    float m_sensitivity  = camera_defaults::sensitivity;
    float m_zoom         = camera_defaults::zoom;

    void updateVectors();
};
