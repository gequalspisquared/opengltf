#include "Application.h"

#include "Renderer/Shader.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexBuffer.h"

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
static void processInput(GLFWwindow* window);

// Default variables
static const uint32_t DEFAULT_WINDOW_WIDTH  = 1600;
static const uint32_t DEFAULT_WINDOW_HEIGHT = 900;
static const char*    DEFAULT_WINDOW_TITLE  = "OpenGLTF";

// TODO: Remove
// Default shaders
const char *vertex_shader_source = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragment_shader_source = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

Application::Application()
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

    // Initialize glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fmt::println("ERROR: Failed to initialize glad!");
        return;
    }

    // Set callbacks
    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
    glfwSetKeyCallback(m_window, keyCallback);
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
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // Buffer creation
    unsigned int va;
    glGenVertexArrays(1, &va);
    glBindVertexArray(va);
    VertexBuffer vb(vertices, sizeof(vertices));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    IndexBuffer ib(indices, sizeof(indices));

    Shader shader_program(SHADER_PATH "shader.vs", SHADER_PATH "shader.fs");

    while (!glfwWindowShouldClose(m_window)) {
        processInput(m_window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glUseProgram(shader_program);
        shader_program.use();
        glBindVertexArray(va);
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

static void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
