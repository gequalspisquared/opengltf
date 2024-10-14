#pragma once

#include <glad/glad.h>

#include <cstdint>
#include <vector>

struct VertexBufferAttributeElement {
    GLuint count;
    GLenum type;
    GLboolean normalized;
};

class VertexBufferLayout
{
public:
    VertexBufferLayout();
    ~VertexBufferLayout();

    uint32_t getStride() const;
    const std::vector<VertexBufferAttributeElement>& getElements() const;

    void push(
        GLuint count,
        GLenum type,
        GLboolean normalized = false
    );

private:
    std::vector<VertexBufferAttributeElement> m_elements;
    uint32_t m_index = 0;
    uint32_t m_stride = 0;
};
