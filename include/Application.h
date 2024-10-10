#pragma once

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

private:
    struct GLFWwindow* m_window = nullptr;

};
