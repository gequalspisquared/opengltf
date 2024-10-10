#pragma once

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind();

private:
    unsigned int m_id = 0;
};
