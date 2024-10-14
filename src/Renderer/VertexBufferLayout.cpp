#include "Renderer/VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout()
{

}

VertexBufferLayout::~VertexBufferLayout()
{
}

uint32_t VertexBufferLayout::getStride() const
{
    return m_stride;
}

const std::vector<VertexBufferAttributeElement>& 
VertexBufferLayout::getElements() const
{
    return m_elements;
}

void VertexBufferLayout::push(
    GLuint count,
    GLenum type,
    GLboolean normalized /* = false */
)
{
    m_elements.push_back({count, type, normalized});

    m_stride += count * sizeof(type);
}
