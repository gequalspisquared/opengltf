#pragma once

#include <glad/glad.h>

class Texture
{
public:
    Texture(
        const char* path,
        GLint min_filter = GL_LINEAR_MIPMAP_LINEAR,
        GLint mag_filter = GL_LINEAR,
        GLint wrap_s = GL_REPEAT,
        GLint wrap_t = GL_REPEAT
    );
    ~Texture();

    void bind() const;
    void unbind() const;

private:
    unsigned int m_id = 0;
};
