#include "Renderer/VertexBuffer.h"

#include <glad/glad.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &m_id);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_id);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
