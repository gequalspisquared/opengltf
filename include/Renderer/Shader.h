#pragma once

#include <glm/glm.hpp>

#include <string_view>

class Shader
{
public:
    Shader(const char* vert_path, const char* frag_path);
    ~Shader();

    void use() const;

    // Uniform setting functions
    void setBool(std::string_view name, bool value) const;
    void setInt(std::string_view name, int value) const;
    void setFloat(std::string_view name, float value) const;
    void setVec2(std::string_view name, const glm::vec2& value) const;
    void setVec3(std::string_view name, const glm::vec3& value) const;
    void setVec4(std::string_view name, const glm::vec4& value) const;
    void setMat2(std::string_view name, const glm::mat2& value) const;
    void setMat3(std::string_view name, const glm::mat3& value) const;
    void setMat4(std::string_view name, const glm::mat4& value) const;

private:
    unsigned int m_id = 0;
};
