#include "Renderer/Shader.h"

#include <glad/glad.h>
#include <fmt/core.h>

#include <string>
#include <fstream>

static GLuint createShader(const char* shader_path, GLenum shader_type);

Shader::Shader(const char* vert_path, const char* frag_path)
{
    // Load vertex shader
    GLuint vert_shader = createShader(vert_path, GL_VERTEX_SHADER);
    if (vert_shader == 0) {
        fmt::println("ERROR: Failed to create vertex shader ({})", vert_path);
        return;
    }

    // Load fragment shader
    GLuint frag_shader = createShader(frag_path, GL_FRAGMENT_SHADER);
    if (vert_shader == 0) {
        fmt::println("ERROR: Failed to create vertex shader ({})", vert_path);
        return;
    }

    // Link shaders into program
    int success;
    char info_log[512];
    m_id = glCreateProgram();
    glAttachShader(m_id, vert_shader);
    glAttachShader(m_id, frag_shader);
    glLinkProgram(m_id);
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_id, 512, nullptr, info_log);
        fmt::println("ERROR: Failed to link program!");
        fmt::println("Info: {}", info_log);

        m_id = 0;
        return;
    }

    // Cleanup compiled shaders
    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);
}

Shader::~Shader()
{
    glDeleteProgram(m_id);
}

void Shader::use() const
{
    glUseProgram(m_id);
}

void Shader::setBool(std::string_view name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.data()), 
                static_cast<int>(value)
    );
}

void Shader::setInt(std::string_view name, int value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.data()), value);
}

void Shader::setFloat(std::string_view name, float value) const
{
    glUniform1f(glGetUniformLocation(m_id, name.data()), value);
}


static GLuint createShader(const char* shader_path, GLenum shader_type)
{
    // Open file
    std::ifstream file(shader_path);
    std::string code;

    // Reserve enough space in string
    file.seekg(0, std::ios::end);
    code.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    // Read data in
    code.assign((std::istreambuf_iterator<char>(file)),
                 std::istreambuf_iterator<char>());
    const char* code_c = code.c_str();

    // Compile shader
    int success;
    char info_log[512];
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &code_c, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, info_log);
        fmt::println("ERROR: Failed to compile shader!");
        fmt::println("Info: {}", info_log);

        return 0;
    }

    return shader;
}
