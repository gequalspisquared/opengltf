#include "Renderer/VertexArray.h"
#include "Renderer/VertexBufferLayout.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_id);
}

void VertexArray::addBuffer(
    const VertexBuffer& vb,
    const VertexBufferLayout& layout
) const
{
    bind();
    vb.bind();

    const uint32_t stride = layout.getStride();
    const auto& elements = layout.getElements();
    uint32_t offset = 0;

    for (uint32_t i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(
            i,
            element.count,
            element.type,
            element.normalized,
            stride,
            reinterpret_cast<const void*>(offset)
        );

        offset += element.count * sizeof(element.type);
    }
}

void VertexArray::bind() const
{
    glBindVertexArray(m_id);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}
