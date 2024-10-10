#pragma once

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

private:
    unsigned int m_id = 0;
};
