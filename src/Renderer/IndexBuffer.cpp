#include "Renderer/IndexBuffer.h"

#include <glad/glad.h>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
{
    glGenBuffers(1, &m_id);
    bind();
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        count * sizeof(unsigned int),
        data,
        GL_STATIC_DRAW
    );
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_id);
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::getCount() const
{
    return m_count;
}
