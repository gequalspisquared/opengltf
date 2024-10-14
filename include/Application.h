#pragma once

#include "Renderer/Camera.h"

class Application
{
public:
    Application();
    ~Application();

    void run();

    // Callbacks
    // These are public so the callbacks can be set from
    // external static functions, DO NOT USE
    void _framebufferSizeCallback(int width, int height);
    void _keyCallback(int key, int scancode, int action, int mods);
    void _mouseCallback(double pos_x, double pos_y);
    void _scrollCallback(double offset_x, double offset_y);

private:
    struct GLFWwindow* m_window = nullptr;
    Camera m_camera;

    bool m_moving_forward  = false;
    bool m_moving_backward = false;
    bool m_moving_left     = false;
    bool m_moving_right    = false;
    bool m_moving_up       = false;
    bool m_moving_down     = false;

    void moveCamera(float delta_time);
};
