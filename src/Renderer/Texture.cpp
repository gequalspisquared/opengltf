#include "Renderer/Texture.h"
#include "fmt/base.h"

#include <fmt/core.h>
#include <stb/stb_image.h>

Texture::Texture(
    const char* path,
    GLint min_filter, /* = GL_LINEAR_MIPMAP_LINEAR */
    GLint mag_filter, /* = GL_LINEAR */
    GLint wrap_s, /* = GL_REPEAT */
    GLint wrap_t /* = GL_REPEAT */
)
{
    glGenTextures(1, &m_id);
    bind();

    // Set texture filtering/ wrappng options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);

    // Load and generate the texture
    int width = 0;
    int height = 0;
    int num_channels = 0;

    unsigned char* data = stbi_load(path, &width, &height, &num_channels, 0);
    if (data) {
        GLint format;
        switch (num_channels) {
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            fmt::println("ERROR: Unrecognixed texture format!");
            break;
        }

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            format,
            width,
            height,
            0,
            format,
            GL_UNSIGNED_BYTE,
            data
        );
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        fmt::println("ERROR: Failed to load texture ({})!", path);
    }
    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
