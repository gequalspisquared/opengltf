#include "Application.h"

#include "Renderer/Camera.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexArray.h"
#include "fmt/base.h"

#include <fmt/core.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdint>

// Callbacks
static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
static void keyCallback(
    GLFWwindow* window,
    int key,
    int scancode,
    int action,
    int mods
);
static void mouseCallback(GLFWwindow* window, double pos_x, double pos_y);
static void scrollCallback(
    GLFWwindow* window,
    double offset_x,
    double offset_y
);
static void processInput(GLFWwindow* window);

// Default variables
static const uint32_t DEFAULT_WINDOW_WIDTH  = 1600;
static const uint32_t DEFAULT_WINDOW_HEIGHT = 900;
static const char*    DEFAULT_WINDOW_TITLE  = "OpenGLTF";

Application::Application()
    : m_camera(glm::vec3(0.0f, 0.0f, 3.0f))
{
    // Initialize GLFW
    if (glfwInit() != GLFW_TRUE) {
        fmt::println("ERROR: Failed to initialize GLFW!");
        return;
    }

    // Create window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_window = glfwCreateWindow(
        DEFAULT_WINDOW_WIDTH,
        DEFAULT_WINDOW_HEIGHT,
        DEFAULT_WINDOW_TITLE,
        nullptr,
        nullptr
    );
    if (!m_window) {
        fmt::println("ERROR: Failed to create a GLFW window!");
        return;
    }
    glfwMakeContextCurrent(m_window);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fmt::println("ERROR: Failed to initialize glad!");
        return;
    }

    // Set callbacks
    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
    glfwSetKeyCallback(m_window, keyCallback);
    glfwSetCursorPosCallback(m_window, mouseCallback);
    glfwSetScrollCallback(m_window, scrollCallback);
}

Application::~Application()
{
    if (m_window) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }

    glfwTerminate();
}

void Application::run()
{
    // float vertices[] = {
    //      0.5f,  0.5f, 0.0f,  // top right
    //      0.5f, -0.5f, 0.0f,  // bottom right
    //     -0.5f, -0.5f, 0.0f,  // bottom left
    //     -0.5f,  0.5f, 0.0f   // top left 
    // };

    // float vertices[] = {
    //     // positions         // colors
    //      0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    //     -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
    //      0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    // };

    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // Buffer creation
    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.push(3, GL_FLOAT); // position
    layout.push(3, GL_FLOAT); // color
    layout.push(2, GL_FLOAT); // texture coords
    va.addBuffer(vb, layout);
    IndexBuffer ib(indices, sizeof(indices));
    Texture texture(RESOURCES_PATH "textures/container.jpg");

    Shader shader_program(SHADER_PATH "shader.vs", SHADER_PATH "shader.fs");

    // Enable depth testing and back face culling
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    float current_time = glfwGetTime();
    float last_frame_time = current_time;
    float delta_time = 0.0f;
    while (!glfwWindowShouldClose(m_window)) {
        // Update time
        current_time = glfwGetTime();
        delta_time = current_time - last_frame_time;
        last_frame_time = current_time;

        // Update MVP matrices
        int screen_width;
        int screen_height;
        glfwGetWindowSize(m_window, &screen_width, &screen_height);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = m_camera.getViewMatrix();
        glm::mat4 proj = m_camera.getPerspectiveProjection(
            screen_width,
            screen_height
        );

        processInput(m_window);
        moveCamera(delta_time);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader_program.use();
        // Set uniforms
        shader_program.setMat4("model", model);
        shader_program.setMat4("view", view);
        shader_program.setMat4("proj", proj);

        texture.bind();
        va.bind();
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void Application::_framebufferSizeCallback(int width, int height)
{
    glViewport(0, 0, width, height);
}

void Application::_keyCallback(int key, int scancode, int action, int mods)
{
    static bool wireframe_enabled = false;
    if (key == GLFW_KEY_T && action == GLFW_PRESS) {
        wireframe_enabled = !wireframe_enabled;
        glPolygonMode(GL_FRONT_AND_BACK, wireframe_enabled ? GL_LINE :
                                                             GL_FILL);
    }

    if (key == GLFW_KEY_W) {
        if (action == GLFW_PRESS) {
            m_moving_forward = true;
        } else if (action == GLFW_RELEASE) {
            m_moving_forward = false;
        }
    }

    if (key == GLFW_KEY_S) {
        if (action == GLFW_PRESS) {
            m_moving_backward = true;
        } else if (action == GLFW_RELEASE) {
            m_moving_backward = false;
        }
    }

    if (key == GLFW_KEY_A) {
        if (action == GLFW_PRESS) {
            m_moving_left = true;
        } else if (action == GLFW_RELEASE) {
            m_moving_left = false;
        }
    }

    if (key == GLFW_KEY_D) {
        if (action == GLFW_PRESS) {
            m_moving_right = true;
        } else if (action == GLFW_RELEASE) {
            m_moving_right = false;
        }
    }

    if (key == GLFW_KEY_SPACE) {
        if (action == GLFW_PRESS) {
            m_moving_up = true;
        } else if (action == GLFW_RELEASE) {
            m_moving_up = false;
        }
    }

    if (key == GLFW_KEY_LEFT_CONTROL) {
        if (action == GLFW_PRESS) {
            m_moving_down = true;
        } else if (action == GLFW_RELEASE) {
            m_moving_down = false;
        }
    }
}

void Application::_mouseCallback(double pos_x, double pos_y)
{
    static double pos_last_x = DEFAULT_WINDOW_WIDTH / 2.0;
    static double pos_last_y = DEFAULT_WINDOW_HEIGHT / 2.0;
    static bool first_mouse  = true;

    if (first_mouse) {
        pos_last_x  = pos_x;
        pos_last_y  = pos_y;
        first_mouse = false;
    }

    float offset_x = pos_x - pos_last_x;
    float offset_y = pos_last_y - pos_y;
    pos_last_x = pos_x;
    pos_last_y = pos_y;

    m_camera.processMouse(offset_x, offset_y);
}

void Application::_scrollCallback(double offset_x, double offset_y)
{
    m_camera.processScroll(offset_y);
}

void Application::moveCamera(float delta_time)
{
    if (m_moving_forward) {
        m_camera.move(CameraMovement::FORWARD, delta_time);
    }

    if (m_moving_backward) {
        m_camera.move(CameraMovement::BACKWARD, delta_time);
    }

    if (m_moving_left) {
        m_camera.move(CameraMovement::LEFT, delta_time);
    }

    if (m_moving_right) {
        m_camera.move(CameraMovement::RIGHT, delta_time);
    }

    if (m_moving_up) {
        m_camera.move(CameraMovement::UP, delta_time);
    }

    if (m_moving_down) {
        m_camera.move(CameraMovement::DOWN, delta_time);
    }
}

static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    Application* app =
        static_cast<Application*>(glfwGetWindowUserPointer(window));
    app->_framebufferSizeCallback(width, height);
}

static void keyCallback(
    GLFWwindow* window,
    int key,
    int scancode,
    int action,
    int mods
)
{
    Application* app =
        static_cast<Application*>(glfwGetWindowUserPointer(window));
    app->_keyCallback(key, scancode, action, mods);
}

static void mouseCallback(GLFWwindow* window, double pos_x, double pos_y)
{
    Application* app =
        static_cast<Application*>(glfwGetWindowUserPointer(window));
    app->_mouseCallback(pos_x, pos_y);
}

static void scrollCallback(
    GLFWwindow* window,
    double offset_x,
    double offset_y
)
{
    Application* app =
        static_cast<Application*>(glfwGetWindowUserPointer(window));
    app->_scrollCallback(offset_x, offset_y);
}

static void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
