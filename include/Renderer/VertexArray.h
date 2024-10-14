#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void addBuffer(
        const VertexBuffer& vb,
        const VertexBufferLayout& layout
    ) const;

    void bind() const;
    void unbind() const;

    // void addLayout() const;

private:
    unsigned int m_id = 0;
};
